//
// Created by oaugusto on 09/11/18.
//

#ifndef DOMINATINGSET_TABULIST_H
#define DOMINATINGSET_TABULIST_H

#include "VertexSet.h"
#include <vector>

using std::vector;

class TabuList {

public:
    TabuList() {}

    ~TabuList() { }

    void setTabu(VertexSet v);

    void removeFirst();

    bool isTabu(VertexSet& v);

    long size() const;

private:
    vector<VertexSet> tabu;
};

#endif //DOMINATINGSET_TABULIST_H
