#include "edge.hpp"

Edge::Edge(char origin,char destination,Cost cost):
    _origin(origin),
    _destination(destination),
    _cost(cost)
{
}

char Edge::get_origin(void) const
{
    return _origin;
}

char Edge::get_destination(void) const
{
    return _destination;
}

Cost Edge::get_cost(void) const
{
    return _cost;
}