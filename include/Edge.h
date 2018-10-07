//
// Created by WorkSpace on 4/30/2018.
//

#ifndef ASSIGNMENT_EDGE_H
#define ASSIGNMENT_EDGE_H

#include <string>
#include "Types.h"

class Edge {

public:
    Edge(v_T source, v_T dest, w_T weight, e_T label)
            : source(source), dest(dest), weight(weight), label(label) {}

    Edge(v_T source, v_T dest) : source(source), dest(dest) {}

    Edge(v_T source, v_T dest, w_T weight)
            : source(source), dest(dest), weight(weight) {}

    Edge(const Edge& edge)
            : source(edge.source), dest(edge.dest),
              weight(edge.weight), label(edge.label) {}

    void set_dest(v_T d) { dest = d;}

    void set_source(v_T s) { source = s; }

    void set_weight(w_T w) { weight = w; }

    void set_label(e_T l) {label = l; }

    v_T get_dest() const { return  dest; }

    v_T get_source() const { return source; }

    w_T  get_weigth() const { return weight; }

    e_T get_label() const { return label; }

    bool operator==(const Edge& other) const {
        return (other.source == source) && (other.dest == dest);
    }

    //to string format < s, d> (w) : l
    std::string to_string() {
        return "< " + std::to_string(source) + ", " +
                std::to_string(dest) + " > (" + std::to_string(weight) +
                ") : " + std::to_string(label);
    }

private:
    v_T source;
    v_T dest;
    w_T weight;
    e_T label;
};

#endif //ASSIGNMENT_EDGE_H
