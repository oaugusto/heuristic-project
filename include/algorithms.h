//
// Created by WorkSpace on 10/1/2018.
//

#ifndef ASSIGNMENT_SOLUTION_H
#define ASSIGNMENT_SOLUTION_H

#include "Graph.h"
#include "Types.h"
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
unsigned long greedy_classical(Graph* graph);

/**
 *
 * @param graph
 * @return
 */
unsigned long greedy_reverse(Graph* graph);

/**
 *
 * @param graph
 * @return
 */
unsigned long greedy_ran(Graph* graph);

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


#endif //ASSIGNMENT_SOLUTION_H
