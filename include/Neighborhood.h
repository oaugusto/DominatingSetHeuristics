//
// Created by oaugusto on 08/11/18.
//

#ifndef DOMINATINGSET_NEIGHBORHOOD_H
#define DOMINATINGSET_NEIGHBORHOOD_H

#include "VertexSet.h"
#include <vector>

using std::vector;

class Neighborhood {

public:
    Neighborhood() {}

    Neighborhood(const vector<VertexSet>& list) { neighbors = list; }

    ~Neighborhood() { }

    void addNeighbor(VertexSet& r);

    void addNeighbors(const vector<VertexSet>& list);

    void clear();

    VertexSet getNeigbor(int i) const;

    unsigned int getSize() const;

    bool isEmpty() const;

private:
    vector<VertexSet> neighbors;
};


#endif //DOMINATINGSET_NEIGHBORHOOD_H
