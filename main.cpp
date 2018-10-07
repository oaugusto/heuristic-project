#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "include/Graph.h"
#include "include/algorithms.h"

using namespace std;

int main(int argc, char* argv[]) {

    clock_t begin, end;

    // Check the number of parameters
    if (argc < 3) {
        // Tell the user how to run the program
        cerr << "Usage: " << argv[0] << " <in file> <algorithm_number>" << endl;
        return 1;
    }

    // input file
    ifstream in(argv[1]);

    if (!in.is_open()) {
        cerr << "error while opening file" << argv[1] << endl;
        return 1;
    }

    //create a graph from file
    Graph* graph = Graph::creatSimpleGraph(in);
    //graph->print_graph(); //just for debug

    //*******************************************************************
    begin = clock();
    //*******************************************************************

    switch (stoi(argv[2])) {
        case 1:
            cout << "naive: "
                 << naive_algorithm(graph) << endl;
            break;

        case 2:
            cout << "classical greedy: "
                 << greedy_classical(graph) << endl;
            break;

        case 3:
            cout << "reverse greedy: "
                 << greedy_reverse(graph) << endl;
            break;

        case 4:
            cout << "random greedy: "
                 << greedy_ran(graph) << endl;
            break;

        case 5:
            cout << "greedy vote: "
                 << greedy_vote(graph) << endl;
            break;

        case 6:
            cout << "greedy vote sr: "
                 << greedy_vote_gr(graph) << endl;
            break;

        default:
            cout << "invalid number(range 1..6)" << endl;
    }

    //*******************************************************************
    //close timer
    end = clock();
    double elapsed_secs = double(end - begin);
    cout << "Time: "
         << elapsed_secs
         << " "
         << elapsed_secs*1.0/CLOCKS_PER_SEC << endl;
    //*******************************************************************

    delete(graph);

    in.close();

    return 0;
}
