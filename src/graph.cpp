#include"graph.hpp"

Edge::Edge(int destInd, int distance, int direction, point boundaryStart, point boundaryEnd, int width) : destInd(destInd), distance(distance), direction(direction), boundaryStart(boundaryStart), boundaryEnd(boundaryEnd), width(width) {}

Vertex::Vertex(point start, int xlength, int ylength) : start(start), xlength(xlength), ylength(ylength) {}

void Vertex::addEdge(int destInd, int distance, int direction, point boundaryStart, point boundaryEnd) {
    edges.push_back(Edge(destInd, distance, direction, boundaryStart, boundaryEnd, boundaryStart.getDistance(boundaryEnd)));
}


int Graph::getVertexIndex(point p) {
    return indexMap[p.x][p.y];
}

int Graph::addVertex(point start, int xlength, int ylength) {
    int index = vertices.size();
    vertices.push_back(Vertex(start, xlength, ylength));
    for (int i = start.x; i < start.x + xlength; i++) {
        for (int j = start.y; j < start.y + ylength; j++) {
            indexMap[i][j] = index;
        }
    }
    return index;
}