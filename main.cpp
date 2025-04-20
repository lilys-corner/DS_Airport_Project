#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Vertex.h"
#include "Graph.cpp"
using namespace std;

// Open in.txt file to read from
ifstream infile("airports.txt");


/*
1 (HAILEY):
    Create weighted directed graph G from the provided .csv file
        Can turn this into .txt if it won't accept .csv
        Two weights for each length, Distance and Cost
DONE!

2 (LILY):
    Find shortest path between origin airport and destination airport
        Provide message if no path
DONE!

3 (LILY):
    Find all shortest paths between a given origin airport and all airports in the destination state
        Provide message if no path
DONE!

4 (HAILEY):
    Find shortest path between origin airport and destination with stops
        Provide message if no path
        3 stops = Source -> stop 1 -> stop 2 -> stop 3 -> Destination

5 (LILY):
    Direct flight connections
        Total = inbound + outbound
        Direct meaning there is only one direct edge between them
            Tampa -edge-> New York: Tampa has 1 outbound edge there, NY has one inbound
DONE!

6 (HAILEY):
    Create undirected graph G_u from G
        Only one directed edge (between u and v) case:
            Ignore Distance, Cost is an undirected weight edge
        Two directed edges (between u and v) case:
            Keep edge with minimum Cost value
            Ignore distance, Cost is an undirected weight edge

7 (HAYLEY):
    Create a Minimal Spanning Tree (MST) w/ Prim's algorithm on G_u
        Output content of MST and total cost (see sample output)
        If G_u is disconnected, provide message it cannot be formed

    //the basics of the algorithm
Done!

8 (HAYLEY):
    Create a Minimal Spanning Tree (MST) w/ Kruskal's algorithm on G_u
        Output content of MST and total cost (see sample output)
        If G_u is disconnected, algorithm provides minimum spanning forest
        consisting of a minimum spanning tree for each connected component

    //the basics of the algorithm cause idk what i'm doing
        greedy approach - each iteration it finds an edge which has least
        weight and adds it ot the growing spanning tree
Done!

*/

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

    //G.print();

    Vertex<string> start (G.airport_to_vector("ATL"));
    Vertex<string> end(G.airport_to_vector("MIA"));
    string stateName = "FL";
    vector<Vertex<string>> state_airports = (G.state_to_vector(stateName));

    // Prints the shortest path between two airports
    G.dijkstra_shortest_path(start, end, state_airports, stateName, 1);
    // Prints the shortest path from an origin airport to state airports
    G.dijkstra_shortest_path(start, end,state_airports, stateName, 2);

    G.shortest_path_stops(G.airport_to_vector("IAD"), G.airport_to_vector("MIA"), 3);
    G.shortest_path_stops(G.airport_to_vector("PIT"), G.airport_to_vector("ACT"), 2);

    G.count_direct_flights();

    Graph<string> G_u = Graph(G);
    G_u.print();

    //apply algorithms to the unsorted G_u and displays the entire mst

    //Graph<string> MST = G_u.primMST();

    //Graph<string> kruskalTree = G_u.kruskalMST();

    //Close the file
    infile.close();
    return 0;
}
