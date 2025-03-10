#pragma once
#include "Misc/PathfindingDetails.hpp"

enum onList {			// On open/closed list?
    onOpen, onClosed, onNone
};

struct Node {
    Node* parent;			// Parent
    GridPos gridPos;		// Node¡¯s location
    float finalCost;		// Final cost f(x)
    float givenCost;		// Given cost g(x)
    onList onlist;
    Node() :parent(nullptr), gridPos(GridPos(0, 0)), finalCost(0), givenCost(0), onlist(onNone) {}
};

class AStarPather
{
public:
    AStarPather();
    /* ************************************************** */
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    PathResult compute_path(PathRequest &request);
    /* ************************************************** */
    // Euclidean, Octile, Chebyshev, Inconsistent, and Manhattan
    float euclidian(GridPos a, GridPos b);
    float octile(GridPos a, GridPos b);
    float chebyshev(GridPos a, GridPos b);
    float inconsistent(GridPos a, GridPos b);
    float manhattan(GridPos a, GridPos b);

    float calculateCost(Heuristic h, GridPos a, GridPos b);
    void setChild(Node* child, PathRequest& request, Node* parent, GridPos goal);
    bool checkRubberBanding(GridPos a, GridPos b);
    Node supportPoint(Node* n1, Node* n2);
    Node* popSmallest();

private:
    Node map[40][40];
    std::vector<Node*> openlist;
};

