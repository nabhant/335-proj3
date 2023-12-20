// Node.hpp

#ifndef NODE_HPP
#define NODE_HPP

#include <cmath>

class Node {
public:
    Node(int id, double x, double y) : id(id), x(x), y(y) {}

    int getId() const { return id; }
    double getX() const { return x; }
    double getY() const { return y; }

    static double distance(const Node& a, const Node& b) {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }

private:
    int id;
    double x, y;
};

#endif // NODE_HPP
