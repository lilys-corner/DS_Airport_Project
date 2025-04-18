#ifndef GRAPH_H
#define GRAPH_H
#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include <string>
template <typename T>
class Graph {
public:
    Graph() {}
    Graph(const Graph& other);

    void insert_vertex(const Vertex<T>& ver);
    void add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int weight, int cost); //connect ver1 with ver2

    void primMST(int V); //creates a MST using Prim's algorithm given an unsorted GU

    void print() const;

    void DFS(Vertex<T>& ver);
    int dijkstra_shortest_path(const Vertex<T>& src, const Vertex<T>& dest, const std::vector<Vertex<T>>& state_airport, const std::string& stateName, const int& print_mode);

    int if_exists(const Vertex<T>& ver);
    Vertex<T> airport_to_vector(const T& airportName);
    std::vector<Vertex<T>> state_to_vector(const T& stateName);

private:
    std::vector<Vertex<T>> vertices; //nodes
    std::vector<std::vector<Edge>> edges; //connections

    void clean_visited();

    void DFS_helper(Vertex<T>& ver);
    int get_vertex_index(const Vertex<T>& ver);
};

#endif
