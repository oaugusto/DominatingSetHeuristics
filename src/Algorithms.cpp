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

bool isDominatingSet(Graph* graph, vector<int>* ds) {
    for (int i = 0; i < graph->get_num_v(); i++) {
        if (ds->at(i) == 0) {
            bool covered = false;
            for (auto it = graph->begin(i); it != graph->end(i); it++) {
                if (ds->at((*it).get_dest()) != 0) {
                    covered = true;
                }
            }
            if (!covered) {
                return false;
            }
        }
    }
    return true;
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

int greedy_classical(Graph *graph) {

    vector<int> D(graph->get_num_v(), 0);
    vector<vertex> weight;
    int size = 0;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        weight.push_back(vertex(i, degree(graph, i) + 1, false));
    }

    v_T vtx = 0;

    while ((vtx = chooseVertex(&weight)) != -1) {
        D[vtx] = 1;
        adjustWeights(graph, &weight, vtx);
        size++;
    }

    if (isDominatingSet(graph, &D)) {
        cout << "dominanting set" << endl;
    } else {
        cout << "wrong set" << endl;
    }

    return size;
}