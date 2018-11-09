//
// Created by oaugusto on 08/11/18.
//

#include "../include/Algorithms.h"

v_T degree(Graph* graph, v_T source) {
    v_T i = 0;

    for (auto it = graph->begin(source); it != graph->end(source); (it)++) {
        i++;
    }

    return i;
}


struct vertex {
    v_T id;
    w_T weight;
    bool covered;

    vertex(v_T id): id(id) {}

    vertex(v_T id, w_T w) : id(id), weight(w) {}

    vertex(v_T id, w_T w, bool cvd) : id(id), weight(w), covered(cvd) {}

    bool operator>(const struct vertex v) const {
        return weight > v.weight;
    }

    bool operator==(const vertex& p) const {
        return p.id == id;
    }
};


v_T chooseVertex(vector<vertex>& weight) {

    sort(weight.begin(), weight.end(), greater<vertex>());

    if ((weight[0]).weight == 0) {
        return -1;
    }

    return (weight[0]).id;
}


void adjustWeights(Graph *graph, vector<vertex>& weight, v_T v) {

    //erase the chosen vertex
    auto v_i = find(weight.begin(), weight.end(), vertex(v));
    if (v_i != weight.end()) {
        v_i->weight = 0;
    }

    //update neighbor
    for (auto j = graph->begin(v); j != graph->end(v); (j)++) {
        auto v_j = find(weight.begin(), weight.end(), vertex((*j).get_dest()));
        if (v_j != weight.end()) {
            if ((*v_j).weight > 0) {
                if (!(*v_i).covered) {
                    (*v_j).weight--;
                }

                if (!(*v_j).covered) {
                    (*v_j).covered = true;
                    (*v_j).weight--;

                    for (auto k = graph->begin(v); k != graph->end(v); (k)++) {
                        auto v_k = find(weight.begin(), weight.end(), vertex((*k).get_dest()));
                        if (v_k != weight.end()) {
                            if ((*v_k).weight > 0) { (*v_k).weight--; }
                        }
                    }
                }
            }
        }
    }

    (*v_i).covered = true;
}


VertexSet greedy_classical(Graph *graph) {

    VertexSet D(graph);
    vector<vertex> weight;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        weight.push_back(vertex(i, degree(graph, i) + 1, false));
    }

    v_T vtx = 0;

    while ((vtx = chooseVertex(weight)) != -1) {
        D.setVertexDominating(vtx);
        adjustWeights(graph, weight, vtx);
    }

    return D;
}


v_T chooseVertexRandomly(vector<vertex>& weight, float alpha) {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();

    sort(weight.begin(), weight.end(), greater<vertex>());

    if ((weight[0]).weight == 0) {
        return -1;
    }

    int count = 0;
    for (; count < weight.size(); count++) {
        if (weight[count].weight == 0) {
            break;
        }
    }

    int max_weigth = weight[0].weight;
    int min_weigth = weight[count-1].weight;

    for (auto it = weight.begin(); it != weight.end(); it++) {
        if ((*it).weight < max_weigth - alpha*(max_weigth - min_weigth)) {
            shuffle (weight.begin(), it-1, std::default_random_engine(seed));
            break;
        }
    }

    return (weight[0]).id;
}


Neighborhood getNeighbors(Graph* graph, VertexSet& vs) {
    Neighborhood nb;
    vector<vertex> coveredby;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        coveredby.push_back(vertex(i, 0, false));
    }

    for (int i = 0; i < vs.getSetSize(); i++) {
        if (vs.isDominatingVertex(i)) {
            coveredby[i].weight++;
            coveredby[i].covered = true;
            for (auto j = graph->begin(i); j != graph->end(i); j++) {
                auto v_j = find(coveredby.begin(), coveredby.end(), vertex((*j).get_dest()));
                if (v_j != coveredby.end()) {
                    (*v_j).weight++;
                }
            }
        }
    }

    for (int i = 0; i < vs.getSetSize() - 1; i++) {
        for (int j = i + 1; j < vs.getSetSize(); j++) {
            if (coveredby[i].covered && coveredby[j].covered) {
                vector<vertex> U;
                for (vertex v_k : coveredby) {
                    int covby = v_k.weight;
                    if (graph->is_edge(v_k.id, coveredby[i].id) || (v_k.id == coveredby[i].id)) {
                        covby--;
                    }
                    if (graph->is_edge(v_k.id, coveredby[j].id) || (v_k.id == coveredby[j].id)) {
                        covby--;
                    }
                    if (covby == 0) {
                        U.push_back(v_k);
                    }
                }

                if (U.empty()) {
                    VertexSet vts(graph, vs.getVertexSet());
                    vts.unsetVertexDominating(i);
                    vts.unsetVertexDominating(j);
                    nb.addNeighbor(vts);
                } else {
                    for (vertex v_k : coveredby) {
                       if (v_k.id != i && v_k.id != j) {
                           bool coverall = true;
                           for (vertex v_x : U) {
                               if (!graph->is_edge(v_k.id, v_x.id)) {
                                   coverall = false;
                               }
                           }
                           if (coverall) {
                               VertexSet vts(graph, vs.getVertexSet());
                               vts.unsetVertexDominating(i);
                               vts.unsetVertexDominating(j);
                               vts.setVertexDominating(v_k.id);
                               nb.addNeighbor(vts);
                           }
                       }
                    }
                }
            }
        }
    }

    return nb;
}


VertexSet localSearch(Graph* graph, VertexSet& vs) {
    VertexSet sBest = vs;
    Neighborhood neighborhood = getNeighbors(graph, sBest);

    while (!neighborhood.isEmpty()) {
        VertexSet aux = neighborhood.getNeigbor(0);

        for (int i = 1; i < neighborhood.getSize(); i++) {
            if (neighborhood.getNeigbor(i).getDominatingSize() < aux.getDominatingSize())
                aux = neighborhood.getNeigbor(i);
        }

        // Change neighborhood
        if (aux.getDominatingSize() < sBest.getDominatingSize()) {
            sBest = aux;
            neighborhood = getNeighbors(graph, sBest);
        } else {
            break;
        }
    }

    return sBest;
}


VertexSet greedyRandomizedConstruction(Graph *graph, float alpha) {

    VertexSet D(graph);
    vector<vertex> weight;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        weight.push_back(vertex(i, degree(graph, i) + 1, false));
    }

    v_T vtx = 0;

    while ((vtx = chooseVertexRandomly(weight, alpha)) != -1) {
        D.setVertexDominating(vtx);
        adjustWeights(graph, weight, vtx);
    }

    return D;
}


VertexSet greedyRandomizedAdaptativeSearchTSP(Graph* graph, int maxIterations) {
    VertexSet sBest = greedy_classical(graph);

    while (maxIterations--) {
        VertexSet candidate = greedyRandomizedConstruction(graph, 0.4);
        candidate = localSearch(graph, candidate);

        if (candidate.getDominatingSize() < sBest.getDominatingSize()) {
            sBest = candidate;
        }
    }

    return sBest;
}

Neighborhood getAllNeighborsNotTabu(Graph* graph, VertexSet& v, TabuList& tabuList) {

}


VertexSet tabuSearchTSP(Graph* graph, VertexSet x, int maxTabuSize, int maxIterations) {

    VertexSet sBest = x;
    VertexSet bestCandidate = x;
    VertexSet oldBestCandidate = x;
    TabuList tabuList(graph->get_num_v());

    while(maxIterations--) {
        Neighborhood neighborhood = getAllNeighborsNotTabu(graph, bestCandidate, tabuList);
        bestCandidate = neighborhood.getNeigbor(0);
        oldBestCandidate = bestCandidate;

        for (int i = 0; i < neighborhood.getSize(); i++) {
            if (neighborhood.getNeigbor(i).getDominatingSize() < bestCandidate.getDominatingSize()) {
                bestCandidate = neighborhood.getNeigbor(i);
            }
        }

        if (bestCandidate.getDominatingSize() < sBest.getDominatingSize()) {
            sBest = bestCandidate;
        }

        //set tabu

        tabuList.decrement();
    }

    return sBest;

}