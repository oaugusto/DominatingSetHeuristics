//
// Created by oaugusto on 09/11/18.
//

#include "../include/TabuList.h"

void TabuList::setTabu(VertexSet v) {
    tabu.push_back(v);
}

void TabuList::removeFirst() {
    tabu.erase(tabu.begin());
}

bool TabuList::isTabu(VertexSet& v) {
    bool isTabu = false;

    for (VertexSet k : tabu) {
        bool isEqual = true;

        for (int i = 0; i < v.getSetSize(); i++) {
            if (v.isDominatingVertex(i) != k.isDominatingVertex(i)) {
                isEqual = false;
                break;
            }
        }

        if (isEqual) {
            isTabu = true;
        }
    }

    return isTabu;
}

long TabuList::size() const { return tabu.size(); }