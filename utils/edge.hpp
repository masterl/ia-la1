#ifndef EDGE_H
#define EDGE_H

typedef unsigned int Cost;

class Edge
{
    public:
        Edge(char origin,char destination,Cost cost);
        void set_origin(char origin);
        char get_origin(void) const;
        void set_destination(char destination);
        char get_destination(void) const;
        void set_cost(Cost cost);
        Cost get_cost(void) const;
    private:
        char _origin;
        char _destination;
        Cost _cost;
};

#endif
