#include <cmath>

class Node
{
public:
    /**
     * @param: id The integer identifier of the node.
     * @param: x The x-coordinate of the node.
     * @param: y The y-coordinate of the node.
     * @post:  A Node object is created with the given ID and coordinates.
     */
    Node(int id, double x, double y) : id(id), x(x), y(y) {}

    /**
     * @return: The integer ID of the node.
     */
    int getId() const { return id; }

    /**
     * @return The x-coordinate of the node.
     */
    double getX() const { return x; }

    /**
     * @return The y-coordinate of the node.
     */
    double getY() const { return y; }

    /**
     * @param a The first Node object.
     * @param b The second Node object.
     * @return The Euclidean distance between nodes a and b.
     */
    static double distance(const Node &a, const Node &b){
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }

private:
    int id;   // The identifier of the node
    double x; // The x-coordinate of the node
    double y; // The y-coordinate of the node
    Node* edge1 = nullptr;
    Node* edge2 = nullptr;
};
