#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <limits>
#include <cmath>

class Node {
public:
    Node(int id, double x, double y) : id_(id), x_(x), y_(y) {}

    int getId() const { return id_; }
    double getX() const { return x_; }
    double getY() const { return y_; }

    static double distance(const Node& a, const Node& b) {
        double dx = a.x_ - b.x_;
        double dy = a.y_ - b.y_;
        return sqrt(dx * dx + dy * dy);
    }

private:
    int id_;
    double x_;
    double y_;
};

std::vector<Node> readData(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return {};
    }

    std::vector<Node> nodes;
    std::string line;
    int id;
    double x, y;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss >> id >> x >> y)) {
            continue; // skip lines that cannot be parsed
        }
        nodes.emplace_back(id, x, y);
    }

    return nodes;
}

void nearestNeighbor(const std::string &filename) {
    auto nodes = readData(filename);
    std::vector<bool> visited(nodes.size(), false);
    std::vector<int> path;
    double totalDistance = 0.0;
    auto current = nodes.begin();
    path.push_back(current->getId());
    visited[current - nodes.begin()] = true;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (size_t i = 1; i < nodes.size(); ++i) {
        auto nearest = nodes.end();
        double minDist = std::numeric_limits<double>::max();

        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            if (!visited[it - nodes.begin()]) {
                double dist = Node::distance(*current, *it);
                if (dist < minDist) {
                    nearest = it;
                    minDist = dist;
                }
            }
        }

        visited[nearest - nodes.begin()] = true;
        totalDistance += minDist;
        path.push_back(nearest->getId());
        current = nearest;
    }

    totalDistance += Node::distance(*current, nodes.front()); // Distance back to the starting node
    path.push_back(nodes.front().getId());

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Output the path, total distance, and time taken
    for (int id : path) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
    std::cout << "Total Distance: " << totalDistance << std::endl;
    std::cout << "Time in ms: " << duration.count() << std::endl;
}
