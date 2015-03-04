#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H

#include <utility>
#include <list>
#include <memory>

typedef unsigned int Cost; // Cost of a trip between vertexes

class GraphVertex; // Stating that this class will be declared later

typedef std::shared_ptr<GraphVertex> GraphVertex_ptr;

typedef std::pair<GraphVertex_ptr,Cost> Edge;

class GraphVertex
{
    public:
        GraphVertex(char name = '\0');
        void set_name(char name);
        char get_name(void) const;
        void add_edge(GraphVertex_ptr vertex,Cost cost);
    private:
        char _name;
        std::list<Edge> _connections;
};

#endif
