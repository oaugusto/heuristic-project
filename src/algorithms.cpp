//
// Created by WorkSpace on 10/1/2018.
//

#include "../include/algorithms.h"

v_T degree(Graph* graph, v_T source) {
    v_T i = 0;

    for (auto it = graph->begin(source); it != graph->end(source); (it)++) {
        i++;
    }

    return i;
}

bool isDominatingSet(Graph* graph, vector<v_T>* ds) {
    for (auto i = 0; i < graph->get_num_v(); i++) {
        if (find(ds->begin(), ds->end(), i) == ds->end()) {
            bool covered = false;
            for (auto it = graph->begin(i); it != graph->end(i); it++) {
                if (find(ds->begin(), ds->end(), (*it).get_dest() ) != ds->end()) {
                    covered = true;
                }
            }
            if (!covered) {
                return false;
            }
        }
    }
    return true;
}

/************************************************************************************************/

int naive_algorithm(Graph* graph) {
    return 0;
}

/************************************************************************************************/
namespace classical {

    struct vertex {
        v_T id;
        w_T weight;

        vertex(v_T id): id(id) {}

        vertex(v_T id, w_T w) : id(id), weight(w) {}

        bool operator>(const struct vertex v) const {
            return weight > v.weight;
        }

        bool operator==(const vertex& p) const {
            return p.id == id;
        }
    };

    v_T chooseVertex(vector<vertex>* weight) {

        if (weight->empty()) {
            return -1;
        }

        sort(weight->begin(), weight->end(), greater<vertex>());

        auto it = weight->begin();
        for (; it != weight->end(); (it)++) {
            if ((*it).weight < (*weight)[0].weight) {
                break;
            }
        }

        auto rng = default_random_engine{};
        shuffle(weight->begin(), it - 1, rng);

        return (*weight)[0].id;
    }

    void adjustWeights(Graph *graph, vector<vertex> *weight, v_T v) {

        //erase the chosen vertex
        auto element = find(weight->begin(), weight->end(), vertex(v));
        if (element != weight->end()) {
            weight->erase(element);
        }

        //update neighbor
        for (auto it = graph->begin(v); it != graph->end(v); (it)++) {
            auto element = find(weight->begin(), weight->end(), vertex((*it).get_dest()));
            if (element != weight->end()) {
                (*element).weight--;
                if ((*element).weight == 0) {
                    weight->erase(element);
                }
            }
        }
    }
}

unsigned long greedy_classical(Graph *graph) {

    vector<v_T> D;
    vector<classical::vertex> weight;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        weight.push_back(classical::vertex(i, degree(graph, i)));
    }

    v_T vtx = 0;

    while ((vtx = classical::chooseVertex(&weight)) != -1) {
        D.push_back(vtx);
        classical::adjustWeights(graph, &weight, vtx);
    }

    if (isDominatingSet(graph, &D)) {
        cout << "dominanting set" << endl;
    } else {
        cout << "wrong set" << endl;
    }

    return D.size();
}

/************************************************************************************************/
namespace reverse {

    struct vertex {
        v_T id;
        w_T degree;
        bool covered;

        vertex(v_T id): id(id) {}

        vertex(v_T id, w_T w, bool c) : id(id), degree(w), covered(c) {}

        bool operator>(const struct vertex v) const {
            return degree > v.degree;
        }

        bool operator<(const struct vertex v) const {
            return degree < v.degree;
        }

        bool operator==(const vertex& p) const {
            return p.id == id;
        }
    };

    v_T chooseVertex(Graph* graph, vector<vertex>* dg, v_T* start) {

        vector<v_T> set;

        bool first = false;
        for (;*start < graph->get_num_v(); (*start)++) {
            for (auto it = graph-> begin((*dg)[*start].id); it != graph-> end((*dg)[*start].id); (it)++) {
                auto e = find(dg->begin(), dg->end(), vertex((*it).get_dest()));
                if (e != dg->end()) {
                    if (((*e).covered) || ((*e).degree) > 1) {
                        set.push_back((*e).id);
                        first = true;
                    }
                }
            }
            if (first) break;
        }

        for (auto i = (*start)+1; i < graph->get_num_v(); i++) {
            for (auto it = graph-> begin((*dg)[i].id); it != graph-> end((*dg)[i].id); (it)++) {
                auto e = find(dg->begin(), dg->end(), vertex((*it).get_dest()));
                if (e != dg->end()) {
                    if ( (degree(graph, set[0]) == degree(graph, (*e).id)) && (((*e).covered) || ((*e).degree) > 1)) {
                        set.push_back((*e).id);
                    }
                }
            }
        }

        if (set.empty()) {
            return -1;
        } else {
            auto rng = default_random_engine{};
            shuffle(set.begin(), set.end(), rng);

            auto e = find(dg->begin(), dg->end(), vertex(set[0]));
            if (e != dg->end()) {
                iter_swap(e, dg->begin() + (*start));
            }

            (*start)++;

            return set[0];
        }
    }

    void adjust(Graph *graph, vector<vertex> *dg, v_T v) {
        auto e = find(dg->begin(), dg->end(), vertex(v));
        if (e != dg->end()) {
            (*e).covered = false;
        }

        for (auto it = graph->begin(v); it != graph->end(v); (it)++) {
            auto element = find(dg->begin(), dg->end(), vertex((*it).get_dest()));
            if (element != dg->end()) {
                (*element).degree--;
            }
        }
    }
}

unsigned long greedy_reverse(Graph* graph) {

    vector<v_T> D;
    vector<reverse::vertex> dg;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        D.push_back(i);
        dg.push_back(reverse::vertex(i, degree(graph, i), true));
    }

    sort(dg.begin(), dg.end());
    v_T start = 0;
    v_T vtx;

    while ((vtx = reverse::chooseVertex(graph,&dg, &start)) != -1) {
        auto element = find(D.begin(), D.end(),vtx);
        if (element != D.end()) {
            D.erase(element);
        }
        reverse::adjust(graph, &dg,vtx);
    }

    if (isDominatingSet(graph, &D)) {
        cout << "dominanting set" << endl;
    } else {
        cout << "wrong set" << endl;
    }

    return D.size();
}

/************************************************************************************************/

namespace rnd {

    struct vertex {
        v_T id;
        w_T weight;
        float prob;

        vertex(v_T id): id(id) {}

        vertex(v_T id, w_T w, float p) : id(id), weight(w), prob(p) {}

        bool operator>(const struct vertex v) const {
            return weight > v.weight;
        }

        bool operator==(const vertex& p) const {
            return p.id == id;
        }
    };

    v_T chooseVertex(vector<vertex>* weight) {

        if (weight->empty()) {
            return -1;
        }

        std::default_random_engine generator;
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        uniform_real_distribution<double> unif(0, 1);
        float dice_roll = unif(generator);

        float total = 0;

        for (vertex v : (*weight)) {
            total += v.prob;
            if (dice_roll < total) {
                return v.id;
            }
        }

        auto last = (*weight).size() - 1;
        return (*weight)[last].id;
    }

    void adjustWeights(Graph *graph, vector<vertex> *weight, v_T v) {

        //erase the chosen vertex
        auto element = find(weight->begin(), weight->end(), vertex(v));
        if (element != weight->end()) {
            weight->erase(element);
        }

        //update neighbor
        for (auto it = graph->begin(v); it != graph->end(v); (it)++) {
            auto element = find(weight->begin(), weight->end(), vertex((*it).get_dest()));
            if (element != weight->end()) {
                (*element).weight--;
                if ((*element).weight == 0) {
                    weight->erase(element);
                }
            }
        }

        auto total = 0;
        for (vertex v : (*weight)) {
            total += degree(graph, v.id);
        }

        for (vertex v : (*weight)) {
            v.prob = ((float) v.weight)/total;
        }
    }
}

unsigned long greedy_ran(Graph* graph) {
    vector<v_T> D;
    vector<rnd::vertex> weight;

    auto total = 0;
    for (v_T i = 0; i < graph->get_num_v(); i++) {
        total += degree(graph, i);
    }

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        weight.push_back(rnd::vertex(i, degree(graph, i), ((float)degree(graph, i))/total));
    }

    v_T vtx = 0;

    while ((vtx = rnd::chooseVertex(&weight)) != -1) {
        D.push_back(vtx);
        rnd::adjustWeights(graph, &weight, vtx);
    }

    if (isDominatingSet(graph, &D)) {
        cout << "dominanting set" << endl;
    } else {
        cout << "wrong set" << endl;
    }

    return D.size();
}

/************************************************************************************************/

namespace vote {

    struct vertex {
        v_T id;
        float weight;
        float vote;

        vertex(v_T id): id(id) {}

        vertex(v_T id, float v) : id(id), vote(v) {}

        bool operator>(const struct vertex v) const {
            return weight > v.weight;
        }

        bool operator==(const vertex& p) const {
            return p.id == id;
        }

        void setWeight(float w) {
            weight = w;
        }
    };

    v_T chooseVertex(vector<vertex>* weight) {

        if (weight->empty()) {
            return -1;
        }

        sort(weight->begin(), weight->end(), greater<vertex>());

        auto it = weight->begin();
        for (; it != weight->end(); (it)++) {
            if ((*it).weight < (*weight)[0].weight) {
                break;
            }
        }

        auto rng = default_random_engine{};
        shuffle(weight->begin(), it - 1, rng);

        return (*weight)[0].id;
    }

    void adjustWeights(Graph *graph, vector<vertex> *weight, v_T v) {

        //erase the chosen vertex
        auto v_ds = find(weight->begin(), weight->end(), vertex(v));
        if (v_ds != weight->end()) {

            //update neighbor
            for (auto it1 = graph->begin(v); it1 != graph->end(v); (it1)++) {
                auto e1 = find(weight->begin(), weight->end(), vertex((*it1).get_dest()));
                if (e1 != weight->end()) {
                    (*e1).weight -= (*v_ds).vote;
                    if ((*e1).weight <= 0) {
                        for (auto it2 = graph->begin((*e1).id); it2 != graph->end((*e1).id); it2++) {
                            auto e2 = find(weight->begin(), weight->end(), vertex((*it2).get_dest()));
                            if (e2 != weight->end()) {
                                if ((*e2).weight > 0)
                                    (*e2).weight -= (*e1).vote;
                            }
                        }
                        weight->erase(e1);
                    }
                }
            }

            weight->erase(v_ds);
        }
    }
}

unsigned long greedy_vote(Graph* graph) {

    vector<v_T> D;
    vector<vote::vertex> weight;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        auto vote = 1 / (float) (1 + degree(graph, i));
        weight.push_back(vote::vertex(i, vote));
    }

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        float v_total = 0;
        for (auto it = graph->begin(i); it != graph->end(i); it++) {
            auto e = find(weight.begin(), weight.end(), vote::vertex((*it).get_dest()));
            if (e != weight.end()) {
                v_total += (*e).vote;
            }
        }

        auto e = find(weight.begin(), weight.end(), vote::vertex(i));
        if (e != weight.end()) {
            (*e).setWeight(v_total + (*e).vote);
        }
    }

    v_T vtx = 0;

    while ((vtx = vote::chooseVertex(&weight)) != -1) {
        D.push_back(vtx);
        vote::adjustWeights(graph, &weight, vtx);
    }

    if (isDominatingSet(graph, &D)) {
        cout << "dominanting set" << endl;
    } else {
        cout << "wrong set" << endl;
    }

    return D.size();
}

/************************************************************************************************/

namespace gr {

    struct vertex {
        v_T id;
        float weight;
        float vote;
        w_T w;

        vertex(v_T id): id(id) {}

        vertex(v_T id, float v, w_T s) : id(id), vote(v), w(s) {}

        bool operator>(const struct vertex v) const {
            return weight > v.weight;
        }

        bool operator==(const vertex& p) const {
            return p.id == id;
        }

        void setWeight(float w) {
            weight = w;
        }
    };

    v_T chooseVertex(vector<vertex>* weight) {

        if (weight->empty()) {
            return -1;
        }

        sort(weight->begin(), weight->end(), greater<vertex>());

        auto it = weight->begin();
        for (; it != weight->end(); (it)++) {
            if ((*it).weight < (*weight)[0].weight) {
                break;
            }
        }

        auto rng = default_random_engine{};
        shuffle(weight->begin(), it - 1, rng);

        return (*weight)[0].id;
    }

    void adjustWeights(Graph *graph, vector<vertex> *weight, v_T v) {

        //erase the chosen vertex
        auto v_ds = find(weight->begin(), weight->end(), vertex(v));
        if (v_ds != weight->end()) {

            //update neighbor
            for (auto it1 = graph->begin(v); it1 != graph->end(v); (it1)++) {
                auto e1 = find(weight->begin(), weight->end(), vertex((*it1).get_dest()));
                if (e1 != weight->end()) {
                    (*e1).weight -= (*v_ds).vote;
                    if ((*e1).weight <= 0) {
                        for (auto it2 = graph->begin((*e1).id); it2 != graph->end((*e1).id); it2++) {
                            auto e2 = find(weight->begin(), weight->end(), vertex((*it2).get_dest()));
                            if (e2 != weight->end()) {
                                if ((*e2).weight > 0)
                                    (*e2).weight -= (*e1).vote;
                            }
                        }
                        weight->erase(e1);
                    }
                }
            }

            weight->erase(v_ds);
        }
    }

    vector<v_T>* local(Graph* graph, vector<v_T>* D) {
        vector<gr::vertex> coveredBy;

        for (v_T i = 0; i < graph->get_num_v(); i++) {
            coveredBy.push_back(gr::vertex(i, 0, 0));
        }

        for (v_T i : (*D)) {
            auto e = find(coveredBy.begin(), coveredBy.end(), vertex(i));
            if (e != coveredBy.end()) {
                (*e).w++;
                for (auto it = graph->begin((*e).id); it != graph->end((*e).id); it++) {
                    auto e1 = find(coveredBy.begin(), coveredBy.end(), gr::vertex((*it).get_dest()));
                    if (e1 != coveredBy.end()) {
                        (*e1).w++;
                    }
                }
            }
        }

        for (v_T i_d : (*D)) {
            for (v_T j_d : (*D)) {
                if (i_d != j_d) {
                    auto e1 = find(coveredBy.begin(), coveredBy.end(), gr::vertex(i_d));
                    auto e2 = find(coveredBy.begin(), coveredBy.end(), gr::vertex(j_d));
                    if ( (e1 != coveredBy.end()) && (e2 != coveredBy.end())) {
                        vector<v_T> U;
                        for (v_T k = 0; k < graph->get_num_v(); k++) {
                            auto k_v = find(coveredBy.begin(), coveredBy.end(), gr::vertex(k));
                            if (k_v != coveredBy.end()) {
                                v_T covby = (*k_v).w;
                                if (graph->is_edge((*k_v).id, (*e1).id)) {
                                    covby--;
                                }
                                if (graph->is_edge((*k_v).id, (*e2).id)) {
                                    covby--;
                                }
                                if (covby == 0) {
                                    U.push_back(k);
                                }
                            }
                        }
                        if (U.empty()) {
                            auto v1 = find((*D).begin(), (*D).end(), (*e1).id);
                            if (v1 != (*D).end()) {
                                (*D).erase(v1);
                            }
                            auto v2 = find((*D).begin(), (*D).end(), (*e2).id);
                            if (v2 != (*D).end()) {
                                (*D).erase(v2);
                            }
                            return local(graph, D);
                        } else {
                            for (v_T k = 0; k < graph->get_num_v(); k++) {
                                auto k_v = find(coveredBy.begin(), coveredBy.end(), gr::vertex(k));
                                if (k_v != coveredBy.end()) {
                                    bool cover_all = true;
                                    for (v_T l : U) {
                                        if (!graph->is_edge(l, k)) {
                                            cover_all = false;
                                        }
                                    }
                                    if (cover_all) {
                                        auto v1 = find((*D).begin(), (*D).end(), (*e1).id);
                                        if (v1 != (*D).end()) {
                                            (*D).erase(v1);
                                        }
                                        auto v2 = find((*D).begin(), (*D).end(), (*e2).id);
                                        if (v2 != (*D).end()) {
                                            (*D).erase(v2);
                                        }
                                        (*D).push_back(k);
                                        return local(graph, D);
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
        return  D;
    }
}

unsigned long greedy_vote_gr(Graph* graph) {

    vector<v_T> D;
    vector<gr::vertex> weight;

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        auto vote = 1 / (float) (1 + degree(graph, i));
        weight.push_back(gr::vertex(i, vote, 0));
    }

    for (v_T i = 0; i < graph->get_num_v(); i++) {
        float v_total = 0;
        for (auto it = graph->begin(i); it != graph->end(i); it++) {
            auto e = find(weight.begin(), weight.end(), gr::vertex((*it).get_dest()));
            if (e != weight.end()) {
                v_total += (*e).vote;
            }
        }

        auto e = find(weight.begin(), weight.end(), gr::vertex(i));
        if (e != weight.end()) {
            (*e).setWeight(v_total + + (*e).vote);
        }
    }

    v_T vtx = 0;

    while ((vtx = gr::chooseVertex(&weight)) != -1) {
        D.push_back(vtx);
        gr::adjustWeights(graph, &weight, vtx);
    }

    gr::local(graph, &D);

    if (isDominatingSet(graph, &D)) {
        cout << "dominanting set" << endl;
    } else {
        cout << "wrong set" << endl;
    }

    return D.size();
}

/************************************************************************************************/
