#include "oriented_graph.hpp"

OrientedGraph::OrientedGraph(void)
{
}

void OrientedGraph::build_graph(const std::string &filename)
{
    std::ifstream file(filename);
    char reader;
    bool edge_origin = true;
    GraphVertex_ptr origin;
    GraphVertex_ptr destination;
    Cost cost;

    if(file.is_open())
    {
        while(file.tellg() >= 0)
        {
            file >> reader;
            //std::cout << "\nReader: " << reader << std::endl;
            if(file.good())
            {
                if(edge_origin)
                {
                    //std::cout << "Origin" << std::endl;
                    origin = get_vertex(reader);
                }
                else
                {
                    //std::cout << "Destination" << std::endl;
                    destination = get_vertex(reader);
                    file >> cost;
                    origin->add_edge(destination,cost);
                }
                edge_origin = !edge_origin;
            }
        }

        //std::cout << "\nVertexes: " << _vertexes.size() << std::endl;

        file.close();
    }
    else
    {
        throw std::runtime_error("Couldn't read file " + filename);
    }
}

GraphVertex_ptr OrientedGraph::get_vertex(char name)
{
    GraphVertex_ptr vertex;

    vertex = _vertexes[name];

    if(vertex == NULL)
    {
        vertex.reset(new GraphVertex);
        vertex->set_name(name);
    }

    return vertex;
}