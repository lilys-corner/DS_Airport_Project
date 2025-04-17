#ifndef VERTEX_H
#define VERTEX_H

template <typename T>
class Vertex {
public:
    Vertex(const T& d = T(), const T& s = T()) : data(d), state(s), visited(false) {};
    const T& getData() const {return data; }
    const T& getState() const {return state; }
    bool getVisited() const {return visited; }
    void setVisited(bool v) { visited = v; }

private:
    T data;
    T state;
    bool visited;
};

#endif