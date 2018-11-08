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

bool isDominatingSet(Graph* graph, vector<v_T>* ds) {
    for (auto i = 0; i < graph->get_num_v(); i++) {
        if (find(ds->begin(), ds->end(), i) == ds->end()) {
            bool covered = false;
            for (auto it = graph->begin(i); it != graph->end(i); it++) {
                if (find(ds->begin(), ds->end(), (*it).get_dest() ) != ds->end()) {
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

    vertex(v_T id): id(id) {}

    vertex(v_T id, w_T w) : id(id), weight(w) {}

    bool operator>(const struct vertex v) const {
        return weight > v.weight;
    }

    bool operator==(const vertex& p) const {
        return p.id == id;
    }
};

v_T chooseVertex(vector<vertex>* weight) {

    if (weight->empty()) {
        return -1;
    }

    sort(weight->begin(), weight->end(), greater<vertex>());

    auto it = weight->begin();
    for (; it != weight->end(); (it)++) {
        if ((*it).weight < (*weight)[0].weight) {
            break;
        }
    }

    auto rng = default_random_engine{};
    shuffle(weight->begin(), it - 1, rng);

    return (*weight)[0].id;
}

void adjustWeights(Graph *graph, vector<vertex> *weight, v_T v) {

    //erase the chosen vertex
    auto element = find(weight->begin(), weight->end(), vertex(v));
    if (element != weight->end()) {
        weight->erase(element);
    }

    //update neighbor
    for (auto it = graph->begin(v); it != graph->end(v); (it)++) {
        auto element = find(weight->begin(), weight->end(), vertex((*it).get_dest()));
        if (element != weight->end()) {
            (*element).weight--;
            if ((*element).weight == 0) {
                weight->erase(element);
            }
        }
    }
}

unsigned long greedy_classical(Graph *graph) {

    vector<v_T> D;
    vector<vertex> weight;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        weight.push_back(vertex(i, degree(graph, i)));
    }

    v_T vtx = 0;

    while ((vtx = chooseVertex(&weight)) != -1) {
        D.push_back(vtx);
        adjustWeights(graph, &weight, vtx);
    }

    if (isDominatingSet(graph, &D)) {
        cout << "dominanting set" << endl;
    } else {
        cout << "wrong set" << endl;
    }

    return D.size();
}