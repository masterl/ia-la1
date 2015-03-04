#include "edge.hpp"

Edge::Edge(char origin,char destination,Cost cost):
    _origin(origin),
    _destination(destination),
    _cost(cost)
{
}

void Edge::set_origin(char origin)
{
    _origin = origin;
}

char Edge::get_origin(void) const
{
    return _origin;
}

void Edge::set_destination(char destination)
{
    _destination = destination;
}

char Edge::get_destination(void) const
{
    return _destination;
}

void Edge::set_cost(Cost cost)
{
    _cost = cost;
}

Cost Edge::get_cost(void) const
{
    return _cost;
}