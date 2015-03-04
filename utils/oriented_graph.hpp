#ifndef ORIENTED_GRAPH_H
#define ORIENTED_GRAPH_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include "graph_vertex.hpp"

class OrientedGraph
{
    public:
        OrientedGraph(void);
        void build_graph(const std::string &filename);
        void print_graph(const std::string &filename);
    private:
        GraphVertex_ptr _origin;
        std::map<char,GraphVertex_ptr> _vertexes;
        std::map<GraphVertex *,char> _label_map;

        GraphVertex_ptr get_vertex(char name);
        void build_label_map(GraphVertex_ptr vertex);
        void insert_on_label_map(GraphVertex_ptr vertex);
        void print_labels(std::ofstream &outfile);
        int get_vertex_number(GraphVertex_ptr vertex);
        void print_edges(std::ofstream &outfile);
};

#endif
