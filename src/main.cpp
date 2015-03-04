#include <iostream>
#include <exception>

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

        graph.print_graph("vertexes.dot");

        cout << "Closing program..." << endl;
    }
    catch(std::exception &e)
    {
        cerr << "\nError!\nMsg: " << e.what() << endl;
    }

    return 0;
}