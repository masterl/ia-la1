#include "oriented_graph.hpp"

#include <stdexcept>

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

        _origin = get_vertex('A');

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
    if(_vertexes.count(name) != 1)
    {
        //std::cout << "creating " << name << std::endl;
        _vertexes[name].reset(new GraphVertex);

        _vertexes[name]->set_name(name);
    }

    return _vertexes[name];
}

void OrientedGraph::print_graph(const std::string &filename)
{
    std::ofstream outfile(filename);

    if(outfile.is_open())
    {
        outfile << "digraph G {\n";

        build_label_map(_origin);

        print_labels(outfile);

        print_edges(outfile);

        outfile << "}\n";
        outfile.close();

        std::cout << "\nGraphviz file generated!\n"
                  << "Run:\n   dot " << filename << " -Tpng -o graph_img.png | display graph_img.png"
                  << "\nTo generate and see the graph's png image!\n" << std::endl;
    }
    else
    {
        throw std::runtime_error("Couldn't write output file " + filename);
    }
}

void OrientedGraph::build_label_map(GraphVertex_ptr vertex)
{
    insert_on_label_map(vertex);

    for(Edge edge : vertex->get_edges())
    {
        insert_on_label_map(edge.first);
    }

    for(Edge edge : vertex->get_edges())
    {
        build_label_map(edge.first);
    }
}

void OrientedGraph::insert_on_label_map(GraphVertex_ptr vertex)
{
    std::map<GraphVertex *,char>::iterator it;

    //std::cout << "insert_on_label_map " << vertex.get() << std::endl;

    it = _label_map.find(vertex.get());

    if(it == _label_map.end())
    {
        _label_map[vertex.get()] = vertex->get_name();
    }
}

void OrientedGraph::print_labels(std::ofstream &outfile)
{
    unsigned int number = 0;

    for(const auto& kv : _label_map)
    {
        outfile << "   " << number << "[label=\"" << kv.second << "\"];\n";
        ++number;
    }
}

int OrientedGraph::get_vertex_number(GraphVertex_ptr vertex)
{
    int number = 0;

    for(const auto &kv : _label_map)
    {
        if(kv.first == vertex.get())
        {
            return number;
        }
        ++number;
    }

    return -1;
}

void OrientedGraph::print_edges(std::ofstream &outfile)
{
    int current, destination;

    for(const auto &kv : _vertexes)
    {
        current = get_vertex_number(kv.second);

        for(Edge edge : kv.second->get_edges())
        {
            destination = get_vertex_number(edge.first);

            outfile << "   " << current << "->" << destination << " ;\n";
        }
    }
}
