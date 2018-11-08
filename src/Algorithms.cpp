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

v_T chooseVertex(vector<vertex>* weight) {

    sort(weight->begin(), weight->end(), greater<vertex>());

    if ((*weight)[0].weight == 0) {
        return -1;
    }

    return (*weight)[0].id;
}

void adjustWeights(Graph *graph, vector<vertex> *weight, v_T v) {

    //erase the chosen vertex
    auto v_i = find(weight->begin(), weight->end(), vertex(v));
    if (v_i != weight->end()) {
        v_i->weight = 0;
    }

    //update neighbor
    for (auto j = graph->begin(v); j != graph->end(v); (j)++) {
        auto v_j = find(weight->begin(), weight->end(), vertex((*j).get_dest()));
        if (v_j != weight->end()) {
            if ((*v_j).weight > 0) {
                if (!(*v_i).covered) {
                    (*v_j).weight--;
                }

                if (!(*v_j).covered) {
                    (*v_j).covered = true;
                    (*v_j).weight--;

                    for (auto k = graph->begin(v); k != graph->end(v); (k)++) {
                        auto v_k = find(weight->begin(), weight->end(), vertex((*k).get_dest()));
                        if (v_k != weight->end()) {
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

    while ((vtx = chooseVertex(&weight)) != -1) {
        D.setVertexDominating(vtx);
        adjustWeights(graph, &weight, vtx);
    }

    if (D.isDominatingSet()) {
        cout << "dominanting set" << endl;
    } else {
        cout << "wrong set" << endl;
    }

    return D;
}

