#include <vector>

#include "defs.h"
#include "common.h"

struct Edge
{
    int destInd; // 目的点的索引
    int distance; 
    int direction; // 方向
    point boundaryStart; // 边界起点，按靠右行出去的边界
    point boundaryEnd; // 边界终点
    int width; // 宽度
    //bool locked; // 是否被锁定
    Edge(int destInd, int distance, int direction, point boundaryStart, point boundaryEnd , int width);

};


class Vertex {
public:
    std::vector<Edge> edges; // Vector to store edges connected to this vertex
    point start; // 起点
    int xlength; // x length of the rectangle
    int ylength; // y length of the rectangle
public:
    Vertex(point start, int xlength, int ylength);
    void addEdge(int destInd, int distance, int direction, point boundaryStart, point boundaryEnd);
};

class Graph {
private:
    int indexMap[MAP_SIZE_X][MAP_SIZE_Y];// 用于索引坐标对应的顶点
    std::vector<Vertex> vertices; // Vector to store vertices
public:
    int getVertexIndex(point p);
    int addVertex(point start, int xlength, int ylength);
    int cutRectangle();
};