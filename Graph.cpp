#include "Graph.h"
#include "MinHeap.h"
#include "MinHeap.cpp"
#include "Edge.h"
#include "Vertex.h"
#include <vector>
#include <queue>
#include <iomanip> //ill ask about it in class
#include <string>
using namespace std;

#include <iostream>
#define INT_MAX 10000

template <typename T>
Graph<T>::Graph(const Graph& other) {
    // Create new graph
    Graph<T> G_u;

    // Copy vertices
    for (int k = 0; k < other.vertices.size(); k++) {
        // Insert the current vertex
        Vertex<T> v1 = other.vertices[k];
        insert_vertex(v1);

        // For each edge, execute
        for (int j = 0; j < other.edges[k].size(); j++) {

            // Insert other vertex based on the edge
            Vertex<T> v2 = other.vertices[other.edges[k][j].dest];
            insert_vertex(v2);

            // Add edges for both
            add_edge(v1, v2, other.edges[k][j].weight, other.edges[k][j].cost);
            add_edge(v2, v1, other.edges[k][j].weight, other.edges[k][j].cost);
        }
    }
}

 //So like i can run my thingie
// yee no problem
template <typename T>
void Graph<T>::insert_vertex(const Vertex<T>& ver) {
    if (get_vertex_index(ver) == -1) {
        vertices.push_back(ver); //insert the vertex to the array of vertices
        std::vector<Edge> tmp;
        edges.push_back(tmp); //insert empty vector to the edges
    }
}

template <typename T>
Vertex<T> Graph<T> :: airport_to_vector(const T& airportName) {
    for (const Vertex<T>& vertex : vertices) {
        if (vertex.getData() == airportName) {
            // Match airport name
           // std::cout << "Found vertex!" << std::endl;
            return vertex;
        }
    }
}
template <typename T>
vector<Vertex<T>> Graph<T> :: state_to_vector(const T& stateName) {
    vector<Vertex<T>> airports_of_state;
    for (const Vertex<T>& vertex : vertices){
        if (vertex.getState() == stateName) {
            // Match airport name
            airports_of_state.push_back(vertex);
            //std::cout << "Added in " << vertex.getData() << std::endl;
            //return vertex;
        }
    }
    return airports_of_state;
}

template <typename T>
int Graph<T>::if_exists(const Vertex<T>& ver) {
    return get_vertex_index(ver);
}

template <typename T>
int Graph<T>::get_vertex_index(const Vertex<T>& ver) {
    for(int i = 0; i < vertices.size(); i++) {
        if (vertices[i].getData() == ver.getData()) {
            return i;
        }
    }

    return -1;
}

template <typename T>
void Graph<T>::add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int weight, int cost) {
    int i1 = get_vertex_index(ver1);
    int i2 = get_vertex_index(ver2);
    if (i1 == -1 || i2 == -1) {
        throw std::string("Add_edge: incorrect vertices");
    }
    Edge v(i1, i2, weight, cost);
    edges[i1].push_back(v);
}

template <typename T>
void Graph<T>::print() const {
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << "{ " << vertices[i].getData() << ": ";
        for(int j = 0; j < edges[i].size(); j++) {
            std::cout << '{' << vertices[edges[i][j].dest].getData() << ", ";
            //std::cout << vertices[edges[i][j].dest].getState() << ", ";
            //std::cout << edges[i][j].weight << ", ";
            //std::cout << edges[i][j].cost << "} ";
            std::cout << edges[i][j].weight << "} ";
        }
        std::cout << " }\n";
    }
}

template <typename T>
void Graph<T>::DFS(Vertex<T>& ver) {
    clean_visited();
    DFS_helper(ver);
    clean_visited();
}

template <typename T>
void Graph<T>::clean_visited() {
    for(Vertex<T>& v : vertices) {
        v.setVisited(false);
    }
}

template <typename T>
void Graph<T>::DFS_helper(Vertex<T>& ver) {
    int i = get_vertex_index(ver);
    if (i == -1) {
        throw std::string("DFS: Vertex is not in the graph");
    }
    vertices[i].setVisited(true); //visit the current vertex
    std::cout << vertices[i].getData() << ' '; //print the data of the current vertex
    for(int j = 0; j < edges[i].size(); j++) {
        Vertex<int> adjacent_ver = vertices[edges[i][j].dest];
        if (adjacent_ver.getVisited() == false) {
            DFS_helper(adjacent_ver);
        }
    }
}

template<typename T>
int Graph<T>::dijkstra_shortest_path(const Vertex<T>& src, const Vertex<T>& dest, const vector<Vertex<T>>& state_airport, const std::string& stateName, const int& print_mode) {
    int i_src = get_vertex_index(src);
    int i_dest = get_vertex_index(dest);

    if (i_src == -1 || i_dest == -1) {
        throw std::string("Shortest path: incorrect vertices");
    }

    clean_visited();
    std::vector<int> distances(vertices.size()); //represents the distances from source to all other vertices

    //set initial distances: 0 for source, very high for everything else initially
    for(int i = 0; i < distances.size(); i++) {
        distances[i] = (i == i_src) ? 0 : INT_MAX;
    }

    // start at source, no visited
    MinHeap<Edge> heap;
    int vertices_visited = 0;
    int cur_ver = i_src;
    std::vector<int> predecessors(vertices.size(),-1);
    std::vector<int> costs(vertices.size(),  INT_MAX);
    costs[i_src] =0;
    //cout << vertices.size() << " " << distances.size() << endl;
    // Continue until all vertices have been visited
    while (vertices_visited < vertices.size()) {
        // Set current vertex to cur_ver (current vertex being processed)
        int i = cur_ver;

        // Iterate through all neighbors (edges) of the current vertex
        for (int j = 0; j < edges[i].size(); j++) {
            // Get the destination vertex of the current edge
            if (edges[i][j].dest == NULL)
                continue;

            int i_adjacent_ver = edges[i][j].dest;

            // Check if the adjacent vertex has not been visited yet
            if (vertices[i_adjacent_ver].getVisited() == false) {
                // Insert the edge into the min-heap (for processing later in Dijkstra's algorithm)
                heap.insert(edges[i][j]);

                // Calculate the new distance from the source to the adjacent vertex through the current vertex
                int dist_from_source = distances[i] + edges[i][j].weight;
                int new_cost = costs[i] + edges[i][j].cost;
                // If this new distance is shorter than the previously known distance to the adjacent vertex, update it
                if (dist_from_source < distances[i_adjacent_ver]) {
                    // Update the shortest distance to the adjacent vertex
                    distances[i_adjacent_ver] = dist_from_source;
                    costs[i_adjacent_ver] = new_cost;
                    predecessors[i_adjacent_ver] = i;
                    // Optional debugging: print all the distances at each step to track the changes
                    /*for (int i : distances) {
                        std::cout << i << ' ';
                    }
                    std::cout << '\n';*/
                }
            }
        }
        if (heap.is_empty()) { // Check if heap is empty before deleting min

            break; // Exit loop gracefully
        }
        // After exploring all neighbors, get the edge with the smallest weight from the heap
        Edge e = heap.delete_min();
        /* std::cout << "Processing edge: " << vertices[e.src].getData() << " -> "
              << vertices[e.dest].getData() << " (Weight: " << e.weight << ")" << std::endl;
        // Update the current vertex to the destination of the edge with the smallest weight
        */cur_ver = e.dest;

        // Mark the current vertex as visited
        vertices[i].setVisited(true);

        // Increment the count of visited vertices
        vertices_visited++;
    }
    if (print_mode == 1) {
        std::cout << "Shortest route from " << src.getData() <<" -> " <<dest.getData()  << ": ";
        if (distances[i_dest] == INT_MAX) {
            std::cout << "None" << endl;
            return 0;
        }
        std::vector<int> path;
        for (int at = i_dest; at != -1; at = predecessors[at]) {
            path.insert(path.begin(), at);
        }
        //std::cout<<"Shortest Path Cost: " << costs[i_dest] << std::endl;
        //std::cout << "Shortest Path: ";
        for (int v : path) {
            std::cout << vertices[v].getData() << " -> ";
        }
        std::cout << "\b\b\b\b. The length is " << distances[i_dest] <<". The cost is " << costs[i_dest] << ".\n";
    }
    else if (print_mode == 2) {
        std::cout << "Shortest paths from " << src.getData() << " to " << stateName << " state airports are:\n\n";
        std::cout << setw(20) << std::left<< "Path"  << setw(10) << "Length" << "Cost\n";

        for (const Vertex<T>& airport : state_airport) {
            int i_dest = get_vertex_index(airport);
            if (i_dest == -1 || distances[i_dest] == INT_MAX) continue; // Skip unreachable airports

            std::vector<int> path;
            for (int at = i_dest; at != -1; at = predecessors[at]) {
                path.insert(path.begin(), at);
            }
            std::string path_str = src.getData() + " -> ";
            //std::cout << std::setw(30) << std::left << src.getData();
            for (int i = 1; i<path.size(); i++) {
                path_str += vertices[path[i]].getData();
                    if (i <path.size()-1) {
                        path_str+= " -> ";
                    }
            }

            std::cout <<std:: left<< std::setw(20) << path_str
                << std::setw(10) << distances[i_dest]
                      << std::setw(10) << costs[i_dest] << std::endl;}
    }
    clean_visited();

    return distances[i_dest];
}


//implementation for prims algorithm mst
//takes an unsorted graph and returns a mst
template<typename T>
Graph<T> Graph<T>::primMST() {
    Graph<T> mst;

    int n = vertices.size();
    if (n == 0) {
        std::cout << "Graph is empty, MST can not be formed.\n";
        return mst;
    }

    int* key = new int[n];       // Minimum cost to reach each vertex
    bool* inMST = new bool[n];   // Visited flag
    int* parent = new int[n];    // To reconstruct MST edges

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        // Find the vertex with the minimum key not in MST
        int minKey = INT_MAX;
        int u = -1;

        for (int v = 0; v < n; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break; // Graph might be disconnected

        inMST[u] = true;

        // Update keys for neighbors of u
        for (int i = 0; i < edges[u].size(); i++) {
            int v = edges[u][i].dest;
            int cost = edges[u][i].cost;

            if (!inMST[v] && cost < key[v]) {
                key[v] = cost;
                parent[v] = u;
            }
        }
    }

    // Build MST graph
    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        mst.insert_vertex(vertices[i]);
    }

    std::cout << "Minimal Spanning Tree (Prim's algorithm):\n";
    std::cout << std::left << std::setw(20) << "Edge" << "Weight\n";

    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            const Vertex<T>& from = vertices[parent[i]];
            const Vertex<T>& to = vertices[i];
            int cost = key[i];

            mst.add_edge(from, to, 0, cost);  // Undirected
            mst.add_edge(to, from, 0, cost);

            std::string edgeLabel = from.getData() + " - " + to.getData();
            std::cout << std::left << std::setw(20) << edgeLabel << cost << "\n";

            total_cost += cost;
        }
    }

    std::cout << "\nTotal Cost of MST: " << total_cost << "\n";

    // Check if graph is disconnected and notify that mst is incomplete
    bool disconnected = false;
    for (int i = 0; i < n; i++) {
        if (!inMST[i]) {
            disconnected = true;
            break;
        }
    }

    if (disconnected) {
        std::cout << "\nNote: The graph is disconnected. MST could not include all vertices.\n";
    }

    // Free memory
    delete[] key;
    delete[] inMST;
    delete[] parent;

    return mst;
}
