#include <iostream>
#include <list>

using namespace std;

class Graph {
private:
    int vertices; 
    list<int>* adjList; 

public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int v) {
        vertices = v;
        adjList = new list<int>[v]; // Create an array of lists
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add edge to the adjacency list
        adjList[v].push_back(u); // For undirected graph, add edge in both directions
    }

    void display() {
        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i << ": ";
            for (int v : adjList[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    ~Graph() {
        delete[] adjList; // Clean up memory
    }

};

int main() {
    Graph g(5); // Create a graph with 5 vertices
    
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    cout << "Adjacency List of the Graph:" << endl;
    g.display(); // Display the adjacency list

    return 0;
}   