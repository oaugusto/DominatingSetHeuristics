//
// Created by oaugusto on 08/11/18.
//

#include "../include/VertexSet.h"

int VertexSet::getSetSize() const { return set.size(); }

long VertexSet::getDominatingSize() const { return size; }

void VertexSet::setDominatingSize(int s) { size = s; };

void VertexSet::setVertexSet(vector<int> r) { set = r; }

vector<int> VertexSet::getVertexSet() { return set; }

void VertexSet::calcSize() {
    size = 0;
    for (auto it = set.begin(); it != set.end(); it++) {
        if ((*it) == 1) {
            size++;
        }
    }
}

Graph* VertexSet::getGraph() { return graph; }

void VertexSet::setGraph(Graph* g) { graph = g; }

bool VertexSet::isDominatingSet() {
    for (int i = 0; i < graph->get_num_v(); i++) {
        if (set[i] == 0) {
            bool covered = false;
            for (auto it = graph->begin(i); it != graph->end(i); it++) {
                if (set[(*it).get_dest()] != 0) {
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

bool VertexSet::isDominatingVertex(int v) const {
    return set[v] != 0;
}

void VertexSet::setVertexDominating(int v) {
    set[v] = 1;
    size++;
}

void VertexSet::unsetVertexDominating(int v) {
    set[v] = 0;
    size--;
}

void VertexSet::printSet() {}
