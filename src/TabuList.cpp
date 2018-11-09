//
// Created by oaugusto on 09/11/18.
//

#include "../include/TabuList.h"

void TabuList::setTabu(vector<int> tb, int time) {
    for (int i = 0; i < tb.size(); i++) {
        if (tb[i] != 0) {

        }
    }
}

void TabuList::decrement() {
    unsigned long int size = tabu.size();
    for (long int i = 0; i < size; i++) {
        for (long int j = 0; j < size; j++) {
            if (tabu[i][j] != 0) {
                tabu[i][j]--;
            }
        }
    }
}

bool TabuList::isTabu(int a, int b) {
    return (tabu[a][b] != 0);
}

int TabuList::size() const { return tabu.size(); }