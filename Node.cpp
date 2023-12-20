#include "Node.hpp"

Node::Node(int id, double x, double y) : id(id), x(x), y(y) {}

double Node::distanceTo(const Node& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}
