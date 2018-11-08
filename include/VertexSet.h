//
// Created by oaugusto on 08/11/18.
//

#ifndef DOMINATINGSET_VERTEXSET_H
#define DOMINATINGSET_VERTEXSET_H

#include "Graph.h"
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

class VertexSet {
public:

    VertexSet() {}

    VertexSet(Graph* g) {
        graph = g;
        set.resize(graph->get_num_v(), 0);
    }

    VertexSet(Graph* g, vector<int> list) {
        graph = g;
        set = list;
        calcSize();
    }

    ~VertexSet() { }

    double getSize() const;

    void setSize(int s);

    void setVertexSet(vector<int> r);

    vector<int> getVertexSet();

    void calcSize();

    Graph* getGraph();

    void setGraph(Graph* g);

    bool isDominatingSet();

    bool isDominatingVertex(int v) const;

    void setVertexDominating(int v);

    void printSet();

private:
    vector<int> set;
    Graph* graph = nullptr;
    double size = 0;
};

#endif //DOMINATINGSET_VERTEXSET_H
