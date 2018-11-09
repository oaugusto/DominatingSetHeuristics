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

    TabuList(int size) {
        tabu.resize(size);
        for (int i = 0; i < tabu.size(); i++) {
            tabu[i].resize(size, 0);
        }
    }

    ~TabuList() { }

    void setTabu(vector<int> tb, int time);

    void decrement();

    bool isTabu(int a, int b);

    int size() const;

private:
    vector<vector<int>> tabu;
};

#endif //DOMINATINGSET_TABULIST_H
