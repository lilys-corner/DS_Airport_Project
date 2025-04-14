#include <iostream>
using namespace std;

/*
1 (LILY):
    Create weighted directed graph G from the provided .csv file
        Can turn this into .txt if it won't accept .csv
        Two weights for each length, Distance and Cost

2 (LILY):
    Find shortest path between origin airport and destination airport
        Provide message if no path

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

8 (HAYLEY):
    Create a Minimal Spanning Tree (MST) w/ Kruskal's algorithm on G_u
        Output content of MST and total cost (see sample output)
        If G_u is disconnected, algorithm provides minimum spanning forest
        consisting of a minimum spanning tree for each connected component
*/

// i like how we don't know what we're doing
// me too

int main() {



    return 0;
}