#ifndef EDGE_H
#define EDGE_H

typedef unsigned int Cost;

class Edge
{
    public:
        Edge(char origin,char destination,Cost cost);
        char get_origin(void) const;
        char get_destination(void) const;
        Cost get_cost(void) const;
    private:
        const char _origin;
        const char _destination;
        const Cost _cost;
};

#endif
