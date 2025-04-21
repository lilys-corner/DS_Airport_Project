#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Vertex.h"
#include "Graph.cpp"
using namespace std;

// Open in.txt file to read from
ifstream infile("airports.txt");

int main() {
    if (infile.is_open() == false) {
        cout << "Error: Unable to open airports.txt" << endl;
        return 1;
    }

    // EACH LINE:
    // Origin_airport, Destination_airport, Origin_city, Destination_city, Distance, Cost
    string origin_airport, destination_airport, origin_city, destination_city, distance, cost;
    Graph<string> G;
    string throw_string;

    // Skip the first line altogether
    getline(infile, throw_string);
    int i = 1;

    // Now, the rest is just the data!
    while (getline(infile, origin_airport, ',')) {
        // There is content in here. Put it in the weighted graph
        getline(infile, destination_airport, ',');

        // skip name of city, only take state name
        getline(infile, throw_string, ' ');
        //now do ACTUAL origin_city
        getline(infile, origin_city, '"');

        // skip name of destination city, only take state name
        getline(infile, throw_string, ' ');
        // now do ACTUAL destination_city
        getline(infile, destination_city, '"');

        // read until numbers
        getline(infile, throw_string, ',');

        // read integers
        getline(infile, distance, ',');
        getline(infile, cost);

        Vertex<string> v1(origin_airport, origin_city);
        Vertex<string> v2(destination_airport, destination_city);

        G.insert_vertex(v1);

        G.insert_vertex(v2);

        G.add_edge(v1, v2, stoi(distance), stoi(cost));
    }

    G.print();

    // Prints the shortest path between two airports
    G.dijkstra_shortest_path(G.airport_to_vector("IAD"), G.airport_to_vector("MIA"), G.state_to_vector("FL"), "FL", 1);
    G.dijkstra_shortest_path(G.airport_to_vector("SPS"), G.airport_to_vector("MIA"), G.state_to_vector("FL"), "FL", 1);
    G.dijkstra_shortest_path(G.airport_to_vector("TYS"), G.airport_to_vector("SPS"), G.state_to_vector("FL"), "FL", 1);

    // Prints the shortest path from an origin airport to state airports
    G.dijkstra_shortest_path(G.airport_to_vector("IAD"), G.airport_to_vector("MIA"),G.state_to_vector("FL"), "FL", 2);
    G.dijkstra_shortest_path(G.airport_to_vector("IAD"), G.airport_to_vector("MIA"),G.state_to_vector("TX"), "TX", 2);
    G.dijkstra_shortest_path(G.airport_to_vector("RFD"), G.airport_to_vector("MIA"),G.state_to_vector("VA"),"VA", 2);

    G.shortest_path_stops(G.airport_to_vector("IAD"), G.airport_to_vector("MIA"), 3);
    G.shortest_path_stops(G.airport_to_vector("PIT"), G.airport_to_vector("ACT"), 2);

    // Prints all connecting flights to each airport
    G.count_direct_flights();

    Graph<string> G_u = Graph(G);
    G_u.print();

    //apply algorithms to the unsorted G_u and displays the entire mst

    Graph<string> MST = G_u.primMST();

    Graph<string> kruskalTree = G_u.kruskalMST();

    //Close the file
    infile.close();
    return 0;
}
