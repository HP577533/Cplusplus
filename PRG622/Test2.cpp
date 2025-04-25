#include <iostream>
#include <map>
#include <vector>

int main() {
    // Adjacency list where each node (int) maps to a list of neighbors
    std::map<int, std::vector<int>> adjList;

    // Adding edges (undirected graph)
    adjList[0].push_back(1);
    adjList[0].push_back(2);
    adjList[1].push_back(0);
    adjList[1].push_back(3);
    adjList[2].push_back(0);
    adjList[3].push_back(1);

    // Print the adjacency list
    for (const auto& pair : adjList) {
        std::cout << "Node " << pair.first << " is connected to: ";
        for (int neighbor : pair.second) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
