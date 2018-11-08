//
// Created by oaugusto on 08/11/18.
//

#include "../include/Neighborhood.h"


void Neighborhood::addNeighbor(VertexSet& r) {
    neighbors.push_back(r);
}

void Neighborhood::addNeighbors(const vector<VertexSet>& list) {
    neighbors = list;
}

void Neighborhood::clear() { neighbors.clear(); }

VertexSet Neighborhood::getNeigbor(int i) const { return neighbors[i]; }

unsigned int Neighborhood::getSize() const { return neighbors.size(); }

bool Neighborhood::isEmpty() const { return neighbors.empty(); }

