#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <limits>
#include "Node.hpp"  

/**
 * @param filename The path to the input file containing node data.
 * @return A vector of Node objects read from the file.
 * @post If the file is read successfully, returns a vector of Nodes; otherwise, returns an empty vector.
 */
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
            continue; // Skip lines that cannot be parsed
        }
        nodes.emplace_back(id, x, y);
    }

    return nodes;
}

/** 
 * @param filename The path to the input file containing node data.
 * @post Outputs the path taken, total distance, and time taken to the console.
 */
void nearestNeighbor(const std::string &filename) {
    auto nodes = readData(filename); // Load nodes from file
    std::vector<bool> visited(nodes.size(), false); // Track visited nodes
    std::vector<int> path; // Store the path taken
    double totalDistance = 0.0; // Total distance of the path
    auto current = nodes.begin(); // Start with the first node
    path.push_back(current->getId()); // Add the first node to the path
    visited[current - nodes.begin()] = true; // Mark it as visited

    auto startTime = std::chrono::high_resolution_clock::now(); // Start timing

    // Visit each node exactly once
    for (size_t i = 1; i < nodes.size(); ++i) {
        auto nearest = nodes.end();
        double minDist = std::numeric_limits<double>::max();

        // Find the nearest unvisited node
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            if (!visited[it - nodes.begin()]) {
                double dist = Node::distance(*current, *it);
                if (dist < minDist) {
                    nearest = it;
                    minDist = dist;
                }
            }
        }

        // Visit the nearest node found
        visited[nearest - nodes.begin()] = true;
        totalDistance += minDist;
        path.push_back(nearest->getId());
        current = nearest;
    }

    // Return to the starting node
    totalDistance += Node::distance(*current, nodes.front());
    path.push_back(nodes.front().getId());

    auto endTime = std::chrono::high_resolution_clock::now(); // End timing
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Output the path, total distance, and time taken
    for (int id : path) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
    std::cout << "Total Distance: " << totalDistance << std::endl;
    std::cout << "Time in ms: " << duration.count() << std::endl;
}
