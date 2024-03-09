#include"graph.hpp"

Edge::Edge(int destInd, int distance, int direction, point boundaryStart, int width) : destInd(destInd), distance(distance), direction(direction), boundaryStart(boundaryStart), width(width) {}

Vertex::Vertex(point start, int xlength, int ylength) : start(start), xlength(xlength), ylength(ylength) {}
void Vertex::addEdge(int destInd, int distance, int direction, point boundaryStart, int width) {
    edges.push_back(Edge(destInd, distance, direction, boundaryStart, width));
}