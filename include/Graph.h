//
// Created by WorkSpace on 4/14/2018.
//

#ifndef ASSIGNMENT_GRAPH_H
#define ASSIGNMENT_GRAPH_H

#include <vector>
#include <list>
#include <algorithm>
#include <limits>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include "Types.h"
#include "Edge.h"

using std::list;
using std::vector;
using std::numeric_limits;
using std::string;
using std::istringstream;
using std::cout;
using std::endl;

class Graph {
public:
    //constructor
    /**
     *
     * @param n
     */
    explicit Graph(v_T n) : num_v(n) { edges.resize(n); }

    //destructor
    ~Graph() {}

    /**
     *
     * @return
     */
    v_T get_num_v() const { return num_v; }

    /**
     *
     * @param edge
     */
    void insert(const Edge& edge);

    /**
     *
     * @param source
     * @param destination
     * @return
     */
    bool is_edge(v_T source, v_T destination) const;

    /**
     *
     * @param source
     * @param destination
     * @return
     */
    Edge get_edge(v_T source, v_T destination) const ;

    /**
     *
     * @param source
     * @param destination
     */
    void remove_edge(v_T source, v_T destination);

    /**
     *
     * @param edge
     */
    void remove_edge(const Edge& edge);

    /**
     *
     * @param source
     */
    void remove_edges(v_T source);

    /**
     *
     * @param source
     * @return
     */
    list<Edge>::iterator begin(v_T source);

    /**
     *
     * @param source
     * @return
     */
    list<Edge>::iterator end(v_T source);

    /**
     *
     */
    void print_graph();

    /**
     *
     * @param in
     * @param type
     * @return
     */
    static Graph* creatGraph(std::istream& in);

    /**
     *
     * @param in
     * @param type
     * @return
     */
    static Graph* creatSimpleGraph(std::istream& in);

private:
    //the number of nodes of the graph
    v_T num_v;

    /**
     *
     */
    vector<list<Edge>> edges;

};


#endif //ASSIGNMENT_GRAPH_H
