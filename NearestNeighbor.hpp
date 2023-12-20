#include "Node.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <limits>

// Forward declaration
std::vector<Node> readData(const std::string& filename);

void nearestNeighbor(const std::string& filename) {
    auto nodes = readData(filename);
    int n = nodes.size();
    std::vector<bool> visited(n, false);
    std::vector<int> path;
    double totalDistance = 0.0;
    int current = 0;
    path.push_back(nodes[current].getId());
    visited[current] = true;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < n; ++i) {
        int nearest = -1;
        double minDist = std::numeric_limits<double>::max();

        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                double dist = Node::distance(nodes[current], nodes[j]);
                if (dist < minDist) {
                    nearest = j;
                    minDist = dist;
                }
            }
        }

        visited[nearest] = true;
        totalDistance += minDist;
        path.push_back(nodes[nearest].getId());
        current = nearest;
    }

    totalDistance += Node::distance(nodes[current], nodes[0]); // Distance back to the starting node
    path.push_back(nodes[0].getId());

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

std::vector<Node> readData(const std::string& filename) {
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

    // std::cout << "Number of nodes read: " << nodes.size() << std::endl; // Tested to see if all nodes were visited
    return nodes;
}
