#include "oriented_graph.hpp"

#include "generators/generators_base.hpp"

#include <stdexcept>

OrientedGraph::OrientedGraph(void)
{
}

void OrientedGraph::build_graph(const std::string &filename)
{
    std::ifstream file(filename);
    std::string reader;
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

        _origin = get_vertex("A");

        //std::cout << "\nVertexes: " << _vertexes.size() << std::endl;

        file.close();
    }
    else
    {
        throw std::runtime_error("Couldn't read file " + filename);
    }
}

GraphVertex_ptr OrientedGraph::get_vertex(const std::string &name)
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

        LabelMap label_map;

        build_label_map(_origin,label_map);

        print_labels(outfile,label_map);

        print_edges(outfile,label_map);

        outfile << "}\n";
        outfile.close();

        std::cout << "\nGraphviz file generated!\n"
                  << "Run:\n   dot " << filename << " -Tpng -o graph_img.png && display graph_img.png"
                  << "\nTo generate and see the graph's png image!\n" << std::endl;
    }
    else
    {
        throw std::runtime_error("Couldn't write output file " + filename);
    }
}

// void OrientedGraph::print_paths_graph(const std::string &filename)
// {
//     _paths = generate_paths_graph(_origin);

//     std::ofstream outfile(filename);

//     if(outfile.is_open())
//     {
//         outfile << "digraph G {\n";

//         LabelMap label_map;

//         build_label_map(_paths,label_map);

//         print_labels(outfile,label_map);

//         print_edges(outfile,label_map);

//         outfile << "}\n";
//         outfile.close();

//         std::cout << "\nGraphviz file generated!\n"
//                   << "Run:\n   dot " << filename << " -Tpng -o graph_img.png | display graph_img.png"
//                   << "\nTo generate and see the graph's png image!\n" << std::endl;
//     }
//     else
//     {
//         throw std::runtime_error("Couldn't write output file " + filename);
//     }
// }

void OrientedGraph::print_paths_graph(const std::string &filename)
{
    _paths = generate_paths_graph(_origin);

    std::ofstream outfile(filename);

    if(outfile.is_open())
    {
        outfile << "digraph G {\n";

        _tmp_label_vector.clear();

        GraphVertex_ptr paths = generate_paths_graph(_origin);

        print_paths_graph(outfile,paths);

        outfile << "}\n";
        outfile.close();

        std::cout << "\nGraphviz file generated!\n"
                  << "Run:\n   dot " << filename << " -Tpng -o graph_img.png && display graph_img.png"
                  << "\nTo generate and see the graph's png image!\n" << std::endl;
    }
    else
    {
        throw std::runtime_error("Couldn't write output file " + filename);
    }
}

void OrientedGraph::print_paths_graph(std::ofstream &outfile,GraphVertex_ptr vertex,Cost cost)
{
    print_label(outfile,vertex);

    unsigned int destination_vertex;
    unsigned int current_vertex = get_label(vertex);

    if(vertex->get_edges().size() > 0)
    {
        for(const auto &edge : vertex->get_edges())
        {
            // std::cout   << vertex->get_name() << " -> "
            //             << edge.first->get_name() << "  "
            //             << edge.second << std::endl;
            print_paths_graph(outfile,edge.first,cost + edge.second);
            unsigned int destination_vertex = get_label(edge.first);
            print_connection(outfile,current_vertex,destination_vertex);
        }
    }
    else
    {
        std::string cost_str;
        GraphVertex_ptr cost_vertex;

        //std::cout << "Cost: " << cost << std::endl;

        cost_vertex.reset(new GraphVertex);
        
        gen::long_to_string(cost_str,cost);
        cost_vertex->set_name(cost_str);

        print_label(outfile,cost_vertex);
        destination_vertex = get_label(cost_vertex);
        print_connection(outfile,current_vertex,destination_vertex);
    }
}

unsigned int OrientedGraph::get_label(GraphVertex_ptr vertex)
{
    unsigned int label_number;

    for(label_number = 0; label_number < _tmp_label_vector.size(); ++label_number)
    {
        if(_tmp_label_vector[label_number].get() == vertex.get())
        {
            return label_number;
        }
    }
}

void OrientedGraph::print_label(std::ofstream &outfile,GraphVertex_ptr vertex)
{
    bool found = false;
    unsigned int label_number;

    //std::cout << "insert_on_label_vector " << vertex.get() << std::endl;

    for(label_number = 0; label_number < _tmp_label_vector.size(); ++label_number)
    {
        if(_tmp_label_vector[label_number].get() == vertex.get())
        {
            found = true;
            break;
        }
    }

    if(!found)
    {
        _tmp_label_vector.push_back(vertex);
        print_label(outfile,label_number,vertex->get_name());
    }
}

void OrientedGraph::print_label(std::ofstream &outfile,unsigned int label_number,const std::string &label)
{
    outfile << "   " << label_number << "[label=\"" << label << "\"];\n";
}

void OrientedGraph::print_connection(std::ofstream &outfile,unsigned int origin,unsigned int destination,const std::string &label)
{
    outfile << "   " << origin << "->" << destination << " [label=\"" << label << "\"] ;\n";
}

GraphVertex_ptr OrientedGraph::generate_paths_graph(GraphVertex_ptr vertex)
{
    GraphVertex_ptr graph;
    GraphVertex_ptr subgraph;

    graph.reset(new GraphVertex);
    graph->set_name(vertex->get_name());

    for(const auto &edge : vertex->get_edges())
    {
        subgraph = generate_paths_graph(edge.first);
        graph->add_edge(subgraph,edge.second);
    }

    return graph;
}

// void OrientedGraph::generate_paths_graph(void)
// {
//     _paths.reset(new GraphVertex);
//     _paths->set_name(_origin->get_name());

//     walk_graph(_origin);
// }

// void OrientedGraph::walk_graph(GraphVertex_ptr vertex)
// {
//     if(_paths == NULL)
//     {
//         _paths.reset(new GraphVertex);
//         _paths->set_name(vertex->get_name());
//     }
// }

void OrientedGraph::build_label_map(GraphVertex_ptr vertex,LabelMap &label_map)
{
    insert_on_label_map(label_map,vertex);

    for(Edge edge : vertex->get_edges())
    {
        insert_on_label_map(label_map,edge.first);
    }

    for(Edge edge : vertex->get_edges())
    {
        build_label_map(edge.first,label_map);
    }
}

void OrientedGraph::insert_on_label_map(LabelMap &label_map,GraphVertex_ptr vertex)
{
    std::map<GraphVertex *,std::string>::iterator it;

    //std::cout << "insert_on_label_map " << vertex.get() << std::endl;

    it = label_map.find(vertex.get());

    if(it == label_map.end())
    {
        label_map[vertex.get()] = vertex->get_name();
    }
}

void OrientedGraph::print_labels(std::ofstream &outfile,const LabelMap &label_map)
{
    unsigned int number = 0;

    for(const auto& kv : label_map)
    {
        outfile << "   " << number << "[label=\"" << kv.second << "\"];\n";
        ++number;
    }
}

int OrientedGraph::get_vertex_number(GraphVertex_ptr vertex,const LabelMap &label_map)
{
    int number = 0;

    for(const auto &kv : label_map)
    {
        if(kv.first == vertex.get())
        {
            return number;
        }
        ++number;
    }

    return -1;
}

void OrientedGraph::print_edges(std::ofstream &outfile,const LabelMap &label_map)
{
    int current, destination;
    std::string cost_str;

    for(const auto &kv : _vertexes)
    {
        current = get_vertex_number(kv.second,label_map);

        for(Edge edge : kv.second->get_edges())
        {
            destination = get_vertex_number(edge.first,label_map);
            cost_str.clear();
            gen::long_to_string(cost_str,edge.second);

            print_connection(outfile,current,destination,cost_str);
        }
    }
}
