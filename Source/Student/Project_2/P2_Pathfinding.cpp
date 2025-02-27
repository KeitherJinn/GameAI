#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"

#pragma region Extra Credit 
bool ProjectTwo::implemented_floyd_warshall()
{
    return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
    return false;
}
#pragma endregion

AStarPather::AStarPather() {
    while (!openlist.empty()) {
        openlist.pop();
    }
    std::cout << "    Initializing pather..." << std::endl;
}

bool AStarPather::initialize()
{
    // handle any one-time setup requirements you have
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            map[i][j].gridPos = GridPos(i, j);
            map[i][j].onlist = onNone;
        }
    }
    while (!openlist.empty()) {
        openlist.pop();
    }
    /*
        If you want to do any map-preprocessing, you'll need to listen
        for the map change message.  It'll look something like this:

        Callback cb = std::bind(&AStarPather::your_function_name, this);
        Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

        There are other alternatives to using std::bind, so feel free to mix it up.
        Callback is just a typedef for std::function<void(void)>, so any std::invoke'able
        object that std::function can wrap will suffice.
    */
    //Callback cb = std::bind(&AStarPather::your_function_name, this);
    //Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

    return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */
}

PathResult AStarPather::compute_path(PathRequest &request)
{
    /*
        This is where you handle pathing requests, each request has several fields:

        start/goal - start and goal world positions
        path - where you will build the path upon completion, path should be
            start to goal, not goal to start
        heuristic - which heuristic calculation to use
        weight - the heuristic weight to be applied
        newRequest - whether this is the first request for this path, should generally
            be true, unless single step is on

        smoothing - whether to apply smoothing to the path
        rubberBanding - whether to apply rubber banding
        singleStep - whether to perform only a single A* step
        debugColoring - whether to color the grid based on the A* state:
            closed list nodes - yellow
            open list nodes - blue

            use terrain->set_color(row, col, Colors::YourColor);
            also it can be helpful to temporarily use other colors for specific states
            when you are testing your algorithms

        method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
            will be A* generally, unless you implement extra credit features

        The return values are:
            PROCESSING - a path hasn't been found yet, should only be returned in
                single step mode until a path is found
            COMPLETE - a path to the goal was found and has been built in request.path
            IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path
    */

    // WRITE YOUR CODE HERE
    //While(Open List is not empty) {
    //    parentNode = Pop cheapest node off Open List.
    //        If parentNode is the Goal Node, then path found(return PathResult::COMPLETE).
    //        Place parentNode on the Closed List.
    //        For(all neighboring child nodes of parentNode) {
    //        Compute its cost, f(x) = g(x) + h(x)
    //            If child node isn¡¯t on Open or Closed list, put it on Open List.
    //            Else if child node is on Open or Closed List, AND this new one is cheaper,
    //            then take the old expensive one off both lists and put this new
    //            cheaper one on the Open List.
    //    }
    //    If taken too much time this frame(or if request.settings.singleStep == true),
    //        abort search for now and resume next frame(return PathResult::PROCESSING).
    //}
    //Open List empty, thus no path possible(return PathResult::IMPOSSIBLE).

    GridPos start = terrain->get_grid_position(request.start);
    GridPos goal = terrain->get_grid_position(request.goal);
    GridPos g1, g2, g3, g4, g5, g6, g7, g8;
    float diffCol, diffRow;
    Node* parent;
    Node* temp;
    Node* tempParent = nullptr;
    Node* tempParentParent = nullptr;
    Node* child;
    bool sign = true;
    std::vector<Vec3> list;
    list.clear();
    // Just sample code, safe to delete
    if (request.newRequest) {
        initialize();
        map[start.row][start.col].givenCost = 0;
        map[start.row][start.col].finalCost = request.settings.weight * calculateCost(request.settings.heuristic, start, goal);
        map[start.row][start.col].onlist = onOpen;
        openlist.push(&map[start.row][start.col]);
    }
    while (!openlist.empty()) {
        parent = openlist.top();
        openlist.pop();
        if (parent->gridPos == goal) {
            temp = parent;
            if (request.settings.rubberBanding) {
                while (temp->gridPos != start) {
                    tempParent = temp->parent;
                    if (tempParent != nullptr && tempParent->gridPos != start) {
                        tempParentParent = tempParent->parent;
                        if (tempParentParent->gridPos != start) {
                            if (checkRubberBanding(temp->gridPos, tempParentParent->gridPos)) {
                                temp->parent = tempParent->parent;
                            }
                            else {
                                request.path.push_front(terrain->get_world_position(temp->gridPos));
                                temp = temp->parent;
                            }
                        }
                        else {
                            request.path.push_front(terrain->get_world_position(temp->gridPos));
                            temp = temp->parent;
                        }
                    }
                    else {
                        request.path.push_front(terrain->get_world_position(temp->gridPos));
                        temp = temp->parent;
                    }
                    tempParent == nullptr;
                }
            }
            if (request.settings.smoothing) {
                Node* n1 = parent;
                Node* n2 = parent;
                Node* n3 = parent;
                Node* n4 = parent;
                bool move1 = false;
                bool move2 = false;
                bool move3 = false;
                bool move4 = false;
                temp = parent;
                request.path.clear();
                request.path.push_front(request.goal);
                while (temp->gridPos != start) {
                    temp = temp->parent;
                    Vec3 point1 = XMVectorCatmullRom(terrain->get_world_position(n1->gridPos), terrain->get_world_position(n2->gridPos), terrain->get_world_position(n3->gridPos), terrain->get_world_position(n4->gridPos), 0.25);
                    Vec3 point2 = XMVectorCatmullRom(terrain->get_world_position(n1->gridPos), terrain->get_world_position(n2->gridPos), terrain->get_world_position(n3->gridPos), terrain->get_world_position(n4->gridPos), 0.5);
                    Vec3 point3 = XMVectorCatmullRom(terrain->get_world_position(n1->gridPos), terrain->get_world_position(n2->gridPos), terrain->get_world_position(n3->gridPos), terrain->get_world_position(n4->gridPos), 0.75);
                    request.path.push_front(point3);
                    request.path.push_front(point2);
                    request.path.push_front(point1);

                    if (move1 && n1->gridPos != start) {
                        n1 = n1->parent;
                        if (move2 && n2->gridPos != start) {
                            n2 = n2->parent;
                            if (move3 && n3->gridPos != start) {
                                n3 = n3->parent;
                                if (move4 && n4->gridPos != start) {
                                    n4 = n4->parent;
                                }
                                else {
                                    n4 = n4->parent;
                                    move4 = true;
                                }
                            }
                            else {
                                n3 = n3->parent;
                                move3 = true;
                            }
                        }
                        else {
                            n2 = n2->parent;
                            move2 = true;
                        }
                    }
                    else {
                        n1 = n1->parent;
                        move1 = true;
                    }
                    
                }
                request.path.push_front(request.start);
            }
            else {
                while (temp->gridPos != start) {
                    request.path.push_front(terrain->get_world_position(temp->gridPos));
                    temp = temp->parent;
                }
                request.path.push_front(request.start);
            }
            return PathResult::COMPLETE;
        }
        parent->onlist = onClosed;
        if (request.settings.debugColoring) terrain->set_color(parent->gridPos, Colors::Yellow);

        g1 = GridPos(parent->gridPos.row, parent->gridPos.col + 1);
        g2 = GridPos(parent->gridPos.row, parent->gridPos.col - 1);
        g3 = GridPos(parent->gridPos.row + 1, parent->gridPos.col + 1);
        g4 = GridPos(parent->gridPos.row - 1, parent->gridPos.col + 1);
        g5 = GridPos(parent->gridPos.row + 1, parent->gridPos.col - 1);
        g6 = GridPos(parent->gridPos.row - 1, parent->gridPos.col - 1);
        g7 = GridPos(parent->gridPos.row + 1, parent->gridPos.col);
        g8 = GridPos(parent->gridPos.row - 1, parent->gridPos.col);

        if (terrain->is_valid_grid_position(g1)) {
            child = &map[parent->gridPos.row][parent->gridPos.col + 1];
            if (!terrain->is_wall(child->gridPos) &&
                terrain->is_valid_grid_position(child->gridPos)) {
                if (child->onlist == onNone) {
                    child->onlist = onOpen;
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    diffCol = abs(parent->gridPos.row - child->gridPos.row);
                    diffRow = abs(parent->gridPos.col - child->gridPos.col);
                    child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    openlist.push(child);
                    child->parent = parent;
                }
                else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
                    child->onlist = onOpen;
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    openlist.push(child);
                    child->parent = parent;
                }
            }
        }
        if (terrain->is_valid_grid_position(g2)) {
            child = &map[parent->gridPos.row][parent->gridPos.col - 1];
            if (!terrain->is_wall(child->gridPos) &&
                terrain->is_valid_grid_position(child->gridPos)) {
                if (child->onlist == onNone) {
                    child->onlist = onOpen;
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    diffCol = abs(parent->gridPos.row - child->gridPos.row);
                    diffRow = abs(parent->gridPos.col - child->gridPos.col);
                    child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    openlist.push(child);
                    child->parent = parent;
                }
                else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
                    child->onlist = onOpen;
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    openlist.push(child);
                    child->parent = parent;
                }
            }
        }
        if (terrain->is_valid_grid_position(g3) && !terrain->is_wall(g1) && !terrain->is_wall(g7)) {
            child = &map[parent->gridPos.row + 1][parent->gridPos.col + 1];
            if (!terrain->is_wall(child->gridPos) &&
                terrain->is_valid_grid_position(child->gridPos)) {
                if (child->onlist == onNone) {
                    child->onlist = onOpen;
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    diffCol = abs(parent->gridPos.row - child->gridPos.row);
                    diffRow = abs(parent->gridPos.col - child->gridPos.col);
                    child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    openlist.push(child);
                    child->parent = parent;
                }
                else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
                    child->onlist = onOpen;
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    openlist.push(child);
                    child->parent = parent;
                }
            }
        }
        if (terrain->is_valid_grid_position(g4) && !terrain->is_wall(g1) && !terrain->is_wall(g8)) {
            child = &map[parent->gridPos.row - 1][parent->gridPos.col + 1];
            if (!terrain->is_wall(child->gridPos) &&
                terrain->is_valid_grid_position(child->gridPos)) {
                if (child->onlist == onNone) {
                    child->onlist = onOpen;
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    diffCol = abs(parent->gridPos.row - child->gridPos.row);
                    diffRow = abs(parent->gridPos.col - child->gridPos.col);
                    child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    openlist.push(child);
                    child->parent = parent;
                }
                else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
                    child->onlist = onOpen;
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    openlist.push(child);
                    child->parent = parent;
                }
            }
        }
        if (terrain->is_valid_grid_position(g5) && !terrain->is_wall(g2) && !terrain->is_wall(g7)) {
            child = &map[parent->gridPos.row + 1][parent->gridPos.col - 1];
            if (!terrain->is_wall(child->gridPos) &&
                terrain->is_valid_grid_position(child->gridPos)) {
                if (child->onlist == onNone) {
                    child->onlist = onOpen;
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    diffCol = abs(parent->gridPos.row - child->gridPos.row);
                    diffRow = abs(parent->gridPos.col - child->gridPos.col);
                    child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    openlist.push(child);
                    child->parent = parent;
                }
                else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
                    child->onlist = onOpen;
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    openlist.push(child);
                    child->parent = parent;
                }
            }
        }
        if (terrain->is_valid_grid_position(g6) && !terrain->is_wall(g2) && !terrain->is_wall(g8)) {
            child = &map[parent->gridPos.row - 1][parent->gridPos.col - 1];
            if (!terrain->is_wall(child->gridPos) &&
                terrain->is_valid_grid_position(child->gridPos)) {
                if (child->onlist == onNone) {
                    child->onlist = onOpen;
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    diffCol = abs(parent->gridPos.row - child->gridPos.row);
                    diffRow = abs(parent->gridPos.col - child->gridPos.col);
                    child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    openlist.push(child);
                    child->parent = parent;
                }
                else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
                    child->onlist = onOpen;
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    openlist.push(child);
                    child->parent = parent;
                }
            }
        }
        if (terrain->is_valid_grid_position(g7)) {
            child = &map[parent->gridPos.row + 1][parent->gridPos.col];
            if (!terrain->is_wall(child->gridPos) &&
                terrain->is_valid_grid_position(child->gridPos)) {
                if (child->onlist == onNone) {
                    child->onlist = onOpen;
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    diffCol = abs(parent->gridPos.row - child->gridPos.row);
                    diffRow = abs(parent->gridPos.col - child->gridPos.col);
                    child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    openlist.push(child);
                    child->parent = parent;
                }
                else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
                    child->onlist = onOpen;
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    openlist.push(child);
                    child->parent = parent;
                }
            }
        }
        if (terrain->is_valid_grid_position(g8)) {
            child = &map[parent->gridPos.row - 1][parent->gridPos.col];
            if (!terrain->is_wall(child->gridPos) &&
                terrain->is_valid_grid_position(child->gridPos)) {
                if (child->onlist == onNone) {
                    child->onlist = onOpen;
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    diffCol = abs(parent->gridPos.row - child->gridPos.row);
                    diffRow = abs(parent->gridPos.col - child->gridPos.col);
                    child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    openlist.push(child);
                    child->parent = parent;
                }
                else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
                    child->onlist = onOpen;
                    child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
                    if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
                    openlist.push(child);
                    child->parent = parent;
                }
            }
        }

        if (request.settings.singleStep == true) {
            return PathResult::PROCESSING;
        }
    }
    return PathResult::IMPOSSIBLE;
}

bool AStarPather::checkRubberBanding(GridPos a, GridPos b) {
    for (int i = std::min(a.row, b.row); i <= std::max(a.row, b.row); i++) {
        for (int j = std::min(a.col, b.col); j <= std::max(a.col, b.col); j++) {
            if (terrain->is_wall(map[i][j].gridPos)) {
                return false;
            }
        }
    }
    return true;
}

float AStarPather::calculateCost(Heuristic h, GridPos a, GridPos b) {
    if (h == Heuristic::OCTILE) {
        return octile(a, b);
    }
    else if (h == Heuristic::CHEBYSHEV) {
        return chebyshev(a, b);
    }
    else if (h == Heuristic::MANHATTAN) {
        return manhattan(a, b);
    }
    else if (h == Heuristic::EUCLIDEAN) {
        return euclidian(a, b);
    }
    else {
        return inconsistent(a, b);
    }
}

void AStarPather::setChild(Node* child, PathRequest& request, Node* parent, GridPos goal) {
    if (!terrain->is_wall(child->gridPos) &&
        terrain->is_valid_grid_position(child->gridPos)) {
        if (child->onlist == onNone) {
            child->onlist = onOpen;
            if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
            float diffCol = abs(parent->gridPos.row - child->gridPos.row);
            float diffRow = abs(parent->gridPos.col - child->gridPos.col);
            child->givenCost = parent->givenCost + sqrt(diffRow * diffRow + diffCol * diffCol);
            child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
            openlist.push(child);
            child->parent = parent;
        }
        else if ((child->onlist == onOpen || child->onlist == onClosed) && child->finalCost > child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal)) {
            child->onlist = onOpen;
            child->finalCost = child->givenCost + request.settings.weight * calculateCost(request.settings.heuristic, child->gridPos, goal);
            if (request.settings.debugColoring) terrain->set_color(child->gridPos, Colors::Blue);
            openlist.push(child);
            child->parent = parent;
        }
    }
}

float AStarPather::euclidian(GridPos a, GridPos b) {
    float diffCol = abs(a.col - b.col);
    float diffRow = abs(a.row - b.row);
    return sqrt(diffCol * diffCol + diffRow * diffRow);
}

float AStarPather::octile(GridPos a, GridPos b) {
    return fmin(abs(a.col - b.col), abs(a.row - b.row)) * 0.41 + fmax(abs(a.col - b.col), abs(a.row - b.row));
}

float AStarPather::chebyshev(GridPos a, GridPos b) {
    return fmax(abs(a.col - b.col), abs(a.row - b.row));
}

float AStarPather::inconsistent(GridPos a, GridPos b) {
    if ((a.row + a.col) % 2 > 0) {
        return euclidian(a, b);
    }
    return 0;
}

float AStarPather::manhattan(GridPos a, GridPos b) {
    return abs(a.col - b.col) + abs(a.row - b.row);
}
