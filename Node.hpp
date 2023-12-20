#include <cmath>

#ifndef NODE_HPP
#define NODE_HPP

class Node {
public:
    int id;
    double x, y;

    Node(int id, double x, double y);
    double distanceTo(const Node& other) const;
};

#endif // NODE_HPP
