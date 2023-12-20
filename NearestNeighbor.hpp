#include <vector>
#include <limits>
#include <iostream>
#include <chrono>
#include "Node.hpp"

void nearestNeighbor(const std::vector<Node>& nodes) {
    std::vector<bool> visited(nodes.size(), false);
    std::vector<int> tour;
    tour.reserve(nodes.size() + 1);
    int current = 0;
    double totalDistance = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    tour.push_back(nodes[current].id);
    visited[current] = true;

    for (size_t i = 1; i < nodes.size(); ++i) {
        double nearestDistance = std::numeric_limits<double>::max();
        int nearestNode = -1;

        for (size_t j = 0; j < nodes.size(); ++j) {
            if (!visited[j]) {
                double distance = nodes[current].distanceTo(nodes[j]);
                if (distance < nearestDistance) {
                    nearestDistance = distance;
                    nearestNode = j;
                }
            }
        }

        visited[nearestNode] = true;
        tour.push_back(nodes[nearestNode].id);
        totalDistance += nearestDistance;
        current = nearestNode;
    }

    // Return to the starting node
    totalDistance += nodes[current].distanceTo(nodes[0]);
    tour.push_back(nodes[0].id);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // Print the result
    for (int id : tour) {
        std::cout << id << " ";
    }
    std::cout << "\nTotal Distance: " << totalDistance << "\nTime in ms: " << duration << std::endl;
}
