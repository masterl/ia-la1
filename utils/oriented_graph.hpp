#ifndef ORIENTED_GRAPH_H
#define ORIENTED_GRAPH_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <tuple>

#include "graph_vertex.hpp"

typedef std::map<GraphVertex *,std::string> LabelMap;
// typedef std::vector<std::pair<GraphVertex *,unsigned int> > LabelVector;
typedef std::vector<GraphVertex_ptr> LabelVector;
typedef std::list<std::tuple<unsigned int,unsigned int,std::string> > ConnectionList;

class OrientedGraph
{
    public:
        OrientedGraph(void);
        void build_graph(const std::string &filename);
        void print_graph(const std::string &filename);
        void print_paths_graph(const std::string &filename);
    private:
        GraphVertex_ptr _origin;
        GraphVertex_ptr _paths;
        std::map<std::string,GraphVertex_ptr> _vertexes;
        LabelVector _tmp_label_vector;
        ConnectionList _tmp_connection_list;

        unsigned int _costs_index;

        std::vector<std::tuple<double, double> > _costs;

        void plot_costs(void);

        void write_cost_csv(void);

        GraphVertex_ptr get_vertex(const std::string &name);

        GraphVertex_ptr generate_paths_graph(GraphVertex_ptr vertex);
        // void generate_paths_graph(void);
        // void walk_graph(GraphVertex_ptr vertex);
        unsigned int get_label(GraphVertex_ptr vertex);
        void print_label(std::ofstream &outfile,GraphVertex_ptr vertex);
        void print_label(std::ofstream &outfile,unsigned int label_number,const std::string &label);
        void print_connection(std::ofstream &outfile,unsigned int origin,unsigned int destination,const std::string &label = "");
        void build_label_map(GraphVertex_ptr vertex,LabelMap &label_map);
        void insert_on_label_map(LabelMap &label_map,GraphVertex_ptr vertex);
        void print_labels(std::ofstream &outfile,const LabelMap &label_map);
        int get_vertex_number(GraphVertex_ptr vertex,const LabelMap &label_map);
        void print_edges(std::ofstream &outfile,const LabelMap &label_map);
        void print_paths_graph(std::ofstream &outfile,GraphVertex_ptr vertex,Cost cost = 0);
};

#endif
