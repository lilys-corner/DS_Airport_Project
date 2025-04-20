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
    void fix(const Graph& other);

    void insert_vertex(const Vertex<T>& ver);
    void add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int weight, int cost); //connect ver1 with ver2

    Graph<T> primMST(); //creates a MST using Prim's algorithm given an unsorted GU
    Graph<T> kruskalMST(); //create a MST using kruskal's algorithm


    void print() const;

    //Finds the shortest path either from one airport to another,
    // or from an airport to the destination state airports
    int dijkstra_shortest_path(const Vertex<T>& src, const Vertex<T>& dest, const std::vector<Vertex<T>>& state_airport, const std::string& stateName, const int& print_mode);

    void shortest_path_stops(const Vertex<T>& src, const Vertex<T>& dest, int stops);


    void count_direct_flights();
    int if_exists(const Vertex<T>& ver);
    Vertex<T> airport_to_vector(const T& airportName);
    std::vector<Vertex<T>> state_to_vector(const T& stateName);

private:
    std::vector<Vertex<T>> vertices; //nodes
    std::vector<std::vector<Edge>> edges; //connections

    void clean_visited();

    int get_vertex_index(const Vertex<T>& ver);
};

#endif
