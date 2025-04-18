#include "Graph.h"
#include "MinHeap.h"
#include "MinHeap.cpp"
#include "Edge.h"
#include "Vertex.h"
#include <vector>
#include <queue>
#include <iomanip> //ill ask about it in class
#include <string>
#include <algorithm>
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
        int m = get_vertex_index(v1);

        // For each edge, execute
        for (int j = 0; j < other.edges[k].size(); j++) {

            // Insert other vertex based on the edge
            Vertex<T> v2 = other.vertices[other.edges[k][j].dest];
            insert_vertex(v2);
            int n = get_vertex_index(v2);

            // Add edges for both
            add_edge(v1, v2, other.edges[k][j].weight, other.edges[k][j].cost);
            add_edge(v2, v1, other.edges[k][j].weight, other.edges[k][j].cost);
        }
    }
    fix(other);
}

template <typename T>
void Graph<T>::fix(const Graph& other) {
    for (int k = 0; k < vertices.size(); k++) {
        Vertex<T> v1 = vertices[k];
        int m = get_vertex_index(v1);

        for (int j = 0; j < edges[k].size(); j++) {
            Vertex<T> v2 = vertices[edges[k][j].dest];
            int n = get_vertex_index(v2);

            for (int i = 0; i < edges[n].size(); i++) {
                if (edges[n][i].dest == m) {

                    if (!other.edges[n].empty() && (other.edges[n][i].cost < edges[k][j].cost) && other.edges[n][i].cost > 0) {
                        edges[n][i].weight = other.edges[n][i].weight;
                        edges[k][j].weight = other.edges[n][i].weight;
                        edges[n][i].cost = other.edges[n][i].cost;
                        edges[k][j].cost = other.edges[n][i].cost;
                    }
                }
            }
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
/*
template <typename T>
void Graph<T>::primMST(int V) {
//creates a MST using Prim's algorithm given an unsorted Graph
    bool inMST [INT_MAX] = {false};
    int total_weight = 0;

    // priority queue (min-heap): {weight, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
*/

    /*code from class
// adjacency list: each element is {neighbor, weight}
vector<pair<int, int>> adj[MAX_VERTICES];

void primMST(int V) {
    bool inMST[MAX_VERTICES] = {false};
    int total_weight = 0;

    // priority queue (min-heap): {weight, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Start from vertex 0
    pq.push({0, 0});

    cout << "Edges in MST:\n";

    while (!pq.empty()) {
        int u = pq.top().second;
        int wt = pq.top().first;
        pq.pop();

        // Skip if already included in MST
        if (inMST[u])
            continue;

        inMST[u] = true;
        total_weight += wt;

        // Don't print the starting node (0) with weight 0
        if (wt != 0)
            cout << "Added vertex " << u << " with edge weight " << wt << endl;

        // Go through all neighbors
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;
            if (!inMST[v])
                pq.push({weight, v});
        }
    }

    cout << "Total weight of MST: " << total_weight << endl;
}

     */
//}

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

template <typename T>
void Graph<T>::shortest_path_stops(const Vertex<T>& src, const Vertex<T>& dest, int stops) {
    // path = stops + 2
    int i_src = get_vertex_index(src);
    int i_dest = get_vertex_index(dest);

    if (i_src == -1 || i_dest == -1) {
        throw std::string("Shortest path: incorrect vertices");
    }

    if (stops < 0) {
        cout << "Error: There cannot be negative stops" << endl;
        return;
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
    costs[i_src] = 0;

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

                // disregard distance if not stops

                // Calculate the new distance from the source to the adjacent vertex through the current vertex
                int dist_from_source = distances[i] + edges[i][j].weight;
                int new_cost = costs[i] + edges[i][j].cost;

                // If this new distance is shorter than the previously known distance to the adjacent vertex, update it
                if (dist_from_source < distances[i_adjacent_ver]) {

                    // Update the shortest distance to the adjacent vertex
                    distances[i_adjacent_ver] = dist_from_source;
                    costs[i_adjacent_ver] = new_cost;
                    predecessors[i_adjacent_ver] = i;
                }
            }
        }
        if (heap.is_empty()) { // Check if heap is empty before deleting min

            break; // Exit loop gracefully
        }
        // After exploring all neighbors, get the edge with the smallest weight from the heap
        Edge e = heap.delete_min();

        cur_ver = e.dest;

        // Mark the current vertex as visited
        vertices[i].setVisited(true);

        // Increment the count of visited vertices
        vertices_visited++;
    }

}

//implementation for prims algorithm mst
//takes an unsorted graph and returns a mst
template<typename T>
Graph<T> Graph<T>::primMST() {
    Graph<T> mst;

    int n = vertices.size();
    if (n == 0) {
        cout << "Graph is empty, MST can not be formed.\n";
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

    cout << "Minimal Spanning Tree (Prim's algorithm):\n";
    cout << left << setw(20) << "Edge" << "Weight\n";

    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            const Vertex<T>& from = vertices[parent[i]];
            const Vertex<T>& to = vertices[i];
            int cost = key[i];

            mst.add_edge(from, to, 0, cost);  // Undirected
            mst.add_edge(to, from, 0, cost);

            string edgeLabel = from.getData() + " - " + to.getData();
            cout << left << setw(20) << edgeLabel << cost << "\n";

            total_cost += cost;
        }
    }

    cout << "\nTotal Cost of MST: " << total_cost << "\n";

    // Check if graph is disconnected and notify that mst is incomplete
    bool disconnected = false;
    for (int i = 0; i < n; i++) {
        if (!inMST[i]) {
            disconnected = true;
            break;
        }
    }

    if (disconnected) {
        cout << "\nNote: The graph is disconnected. MST could not include all vertices.\n";
    }

    // Free memory
    delete[] key;
    delete[] inMST;
    delete[] parent;

    return mst;
}

template <typename T>
void Graph<T>::count_direct_flights() {
    std::vector<int> inbound(vertices.size(), 0);
    std::vector<int> outbound(vertices.size(), 0);

    int max_connections = 0;

    // Count inbound and outbound flights
    for (int i = 0; i < vertices.size(); i++) {
        outbound[i] = edges[i].size();
        for (const Edge& edge : edges[i]) {
            inbound[edge.dest]++;
        }
        max_connections = std::max(max_connections, inbound[i] + outbound[i]); // Track highest count
    }

    std::cout << std::setw(20) << std::left << "Airport"
              << std::setw(10) << "Connections\n";

    // Iteratively print airports with decreasing total connections
    for (int total = max_connections; total >= 0; total--) {
        for (int i = 0; i < vertices.size(); i++) {
            if (inbound[i] + outbound[i] == total) {
                std::cout << std::setw(20) << std::left << vertices[i].getData()
                          << std::setw(10) << total << std::endl;
            }
        }
    }
}

//takes an unsorted graph and returns either a mst or a minimum spanning forest if graph is disconnected
template <typename T>
Graph<T> Graph<T>::kruskalMST() {
    Graph<T> mst;

    int n = vertices.size();
    if (n == 0) {
        std::cout << "Graph is empty. No MST can be formed.\n";
        return mst;
    }

    // Disjoint-set (Union-Find)
    int* parent = new int[n];
    for (int i = 0; i < n; i++) parent[i] = i;

    auto find = [&](int x) {
        while (x != parent[x]) x = parent[x];
        return x;
    };

    auto union_sets = [&](int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x != root_y) parent[root_y] = root_x;
    };

    // Step 1: collect all unique edges
    vector<Edge> all_edges;
    for (int i = 0; i < n; i++) {
        for (const Edge& e : edges[i]) {
            if (i < e.dest) {
                all_edges.push_back(e);
            }
        }
    }

    // Step 2: sort edges by cost (selection sort)
    for (int i = 0; i < all_edges.size() - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < all_edges.size(); j++) {
            if (all_edges[j].cost < all_edges[min_idx].cost) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Edge temp = all_edges[i];
            all_edges[i] = all_edges[min_idx];
            all_edges[min_idx] = temp;
        }
    }

    // Step 3: add all vertices to MST
    for (int i = 0; i < n; i++) {
        mst.insert_vertex(vertices[i]);
    }

    // Group MST edges by root
    vector<vector<Edge>> forest(n);  // forest[root] holds that component's edges
    int total_cost = 0;

    for (const Edge& e : all_edges) {
        int u = e.src;
        int v = e.dest;
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            union_sets(u, v);
            int root = find(u);

            // Add to forest and MST
            forest[root].push_back(e);
            mst.add_edge(vertices[u], vertices[v], 0, e.cost);
            mst.add_edge(vertices[v], vertices[u], 0, e.cost);
            total_cost += e.cost;
        }
    }

    // Display the forest (multiple trees)
    std::cout << "Minimum Spanning Forest:\n";
    std::cout << std::left << std::setw(20) << "Edge" << "Weight\n";

    bool printed[n]; // avoid printing the same component twice
    for (int i = 0; i < n; i++) printed[i] = false;

    for (int i = 0; i < n; i++) {
        int root = find(i);
        if (!printed[root] && !forest[root].empty()) {
            printed[root] = true;

            for (const Edge& e : forest[root]) {
                std::string edgeLabel = vertices[e.src].getData() + " - " + vertices[e.dest].getData();
                std::cout << std::left << std::setw(20) << edgeLabel << e.cost << "\n";
            }

            std::cout << "------------------------\n";
        }
    }

    std::cout << "Total Cost of MST: " << total_cost << "\n";

    delete[] parent;
    return mst;
}
