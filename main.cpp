#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Vertex.h"
#include "Graph.cpp"

#include <cstring>
using namespace std;

// Open in.txt file to read from
ifstream infile("airports.txt");


/*
1 (LILY):
    Create weighted directed graph G from the provided .csv file
        Can turn this into .txt if it won't accept .csv
        Two weights for each length, Distance and Cost
DONE!

2 (LILY):
    Find shortest path between origin airport and destination airport
        Provide message if no path
DONE!

3 (HAILEY):
    Find all shortest paths between origin airports and all airports in the destination state
        Provide message if no path


4 (HAILEY):
    Find shortest path between origin airport and destination with stops
        Provide message if no path
        3 stops = Source -> stop 1 -> stop 2 -> stop 3 -> Destination

5 (LILY):
    Direct flight connections
        Total = inbound + outbound
        Direct meaning there is only one direct edge between them
            Tampa -edge-> New York: Tampa has 1 outbound edge there, NY has one inbound

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
DONE!

8 (HAYLEY):
    Create a Minimal Spanning Tree (MST) w/ Kruskal's algorithm on G_u
        Output content of MST and total cost (see sample output)
        If G_u is disconnected, algorithm provides minimum spanning forest
        consisting of a minimum spanning tree for each connected component

    


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

        /*
        cout << "line! " << i << endl;
        i++;*/
        G.insert_vertex(v1);

        G.insert_vertex(v2);

        G.add_edge(v1, v2, stoi(distance), stoi(cost));
    }

    //G.print();

    Vertex<string> start (G.airport_to_vector("ACT"));
    Vertex<string> end(G.airport_to_vector("MIA"));
    string stateName = "TX";
    vector<Vertex<string>> state_airports = (G.state_to_vector(stateName));
    //for (auto i : state_airports)
     //   cout << i.getData() << " ";


    //cout << G.dijkstra_shortest_path(start, end);
    G.dijkstra_shortest_path(start, end, state_airports, stateName, 1);
    G.dijkstra_shortest_path(start, end,state_airports, stateName, 2);
    /*for (const Vertex<std::string>& airport : state_airports) {
        G.dijkstra_shortest_path(start, airport,state_airports, 2); // Use mode 2
        std::cout << "\n"; // Separate output between paths
    }*/

    //Graph<string> G_u = Graph(G);
    //G_u.print();

    //apply prims algorithm to the unsorted G_u and displays the entire mst
    //Graph<string> MST = G_u.primMST();


    //Close the file
    infile.close();
    return 0;
}
