#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    Edge(int src = 0, int dest = 0, int weight = 0) :
        src(src), dest(dest), weight(weight) {}

    bool operator<(const Edge& other) const {
        if(this->weight < other.weight) {
            return true;
        }

        return false;
    }

    int src;
    int dest;
    int weight;
};

#endif