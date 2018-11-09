//
// Created by oaugusto on 08/11/18.
//

#ifndef DOMINATINGSET_ALGORITHMS_H
#define DOMINATINGSET_ALGORITHMS_H

#include "Graph.h"
#include "Types.h"
#include "VertexSet.h"
#include "Neighborhood.h"
#include "TabuList.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <random>
#include <cstdlib>
#include <chrono>

using std::greater;
using std::pair;
using std::sort;
using std::shuffle;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::find;
using std::iter_swap;
using std::rand;

/**
 *
 * @param graph
 * @param source
 * @return
 */
v_T degree(Graph* graph, v_T source);

/**
 *
 * @param graph
 * @return
 */
int naive_algorithm(Graph* graph);

/**
 *
 * @param graph
 * @return
 */
VertexSet greedy_classical(Graph* graph);

/**
 *
 * @param graph
 * @return
 */
int greedy_reverse(Graph* graph);

/**
 *
 * @param graph
 * @return
 */
int greedy_ran(Graph* graph);

/**
 *
 * @param graph
 * @return
 */
unsigned long greedy_vote(Graph* graph);

/**
 *
 * @param graph
 * @return
 */
unsigned long greedy_vote_gr(Graph* graph);

/**
 *
 * @param graph
 * @param vs
 * @return
 */
Neighborhood getNeighbors(Graph* graph, VertexSet& vs);

/**
 *
 * @param graph
 * @param vs
 * @return
 */
VertexSet localSearch(Graph* graph, VertexSet& vs);

/**
 *
 * @param graph
 * @param alpha
 * @return
 */
VertexSet greedyRandomizedConstruction(Graph *graph, float alpha);

/**
 *
 * @param graph
 * @param maxIterations
 * @return
 */
VertexSet greedyRandomizedAdaptativeSearchTSP(Graph* graph, int maxIterations);

#endif //DOMINATINGSET_ALGORITHMS_H
