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

struct CMP {
    bool operator()(const Node* a, const Node* b) const {
        return a->finalCost > b->finalCost;
    }
};

class AStarPather
{
public:
    /* 
        The class should be default constructible, so you might need to define a constructor.
        If needed, you can modify the framework where the class is constructed in the
        initialize functions of ProjectTwo and ProjectThree.
    */
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
    /*
        You should create whatever functions, variables, or classes you need.
        It doesn't all need to be in this header and cpp, structure it whatever way
        makes sense to you.
    */
private:
    Node map[40][40];
    std::priority_queue<Node*, std::vector<Node*>, CMP> openlist;
};

