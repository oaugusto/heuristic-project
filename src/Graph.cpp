//
// Created by WorkSpace on 4/14/2018.
//

#include "../include/Graph.h"


bool Graph::is_edge(v_T source, v_T destination) const {
    auto it = find(edges[source].cbegin(), edges[source].cend(), Edge(source, destination));

    return it != edges[source].end();
}

Edge Graph::get_edge(v_T source, v_T destination) const {
    auto it = find(edges[source].cbegin(), edges[source].cend(), Edge(source, destination));

    if (it != edges[source].end()) {
        return *it;
    } else {
        Edge(source, destination, numeric_limits<w_T>::max());
    }
}

void Graph::insert(const Edge& edge) {
    edges[edge.get_source()].push_back(edge);
}

list<Edge>::iterator Graph::begin(v_T source) {
    return edges[source].begin();
}


list<Edge>::iterator Graph::end(v_T source) {
    return edges[source].end();
}


void Graph::remove_edge(v_T source, v_T destination) {
    auto it = find(edges[source].begin(), edges[source].end(), Edge(source, destination));

    if (it !=  edges[source].end()) {
        edges[source].remove(*it);
    }
}

void Graph::remove_edge(const Edge& edge) {
    auto it = find(edges[edge.get_source()].begin(),
                                              edges[edge.get_source()].end(),
                                              Edge(edge.get_source(), edge.get_dest()));

    if (it !=  edges[edge.get_source()].end()) {
        edges[edge.get_source()].remove(*it);
    }
}

void Graph::remove_edges(v_T source) {
    edges[source].clear();
}

void Graph::print_graph() {
    for (int i = 0; i < num_v; i++) {
        for (auto it = edges[i].begin(); it != edges[i].end(); it++) {
            cout << (*it).to_string() << endl;
        }
    }
}

Graph* Graph::creatGraph(std::istream &in) {
    v_T nv; //number of vertex
    v_T ne; //number of edges

    string first_line;
    //get the first line to parse the graph
    getline(in, first_line);

    istringstream head(first_line);
    head >> nv;
    head >> ne;

    //construct new graph
    auto graph = new Graph(nv);

    for (v_T i = 1; i <= ne; i++){
        string line;
        getline(in, line);
        istringstream ed(line);

        v_T v1; //first vertex
        v_T v2; //second vertex
        w_T w;  //weight

        ed >> v1;
        ed >> v2;
        ed >> w;

        graph->insert(Edge(v1 - 1, v2 - 1, w, i));
    }

    return graph;
}


Graph* Graph::creatSimpleGraph(std::istream &in) {
    v_T nv; //number of vertex
    v_T ne; //number of edges

    string first_line;
    //get the first line to parse the graph
    getline(in, first_line);

    istringstream head(first_line);
    head >> nv;
    head >> ne;

    //construct new graph
    auto graph = new Graph(nv);

    for (v_T i = 1; i <= ne; i++){
        string line;
        getline(in, line);
        istringstream ed(line);

        v_T v1; //first vertex
        v_T v2; //second vertex
        w_T w = 1;  //weight

        ed >> v1;
        ed >> v2;

        graph->insert(Edge(v1 - 1, v2 - 1, w, i));
    }

    return graph;
}
