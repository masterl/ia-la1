#include <iostream>

#include "../utils/oriented_graph.hpp"

using std::cerr;
using std::cout;
using std::endl;

int main(void)
{
    try
    {
        OrientedGraph graph;

        graph.build_graph("graph.txt");

        cout << "Closing program..." << endl;
    }
    catch(std::exception &e)
    {
        cerr << "\nError!\nMsg: " << e.what() << endl;
    }

    return 0;
}