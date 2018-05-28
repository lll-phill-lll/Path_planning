#ifndef NODE_H
#define NODE_H

//That's the data structure for storing a single search node.
//Although one might realize A* pathfinder relying only on g-value,
//it's a good idea to store f- and h-values explicitly for the sake of simplicity
//(and either h- or f-value is definetely needed for realizing different tie-breaking strategies).
//Backpointer is obligatory for any-angle algorithms, e.g. Theta*, and it makes sense to utilize it
//in A*-like algorithms as well for reconstructing path (after the main search phase is finished).

//So, in the end of the day, we have a sort of "universal" search-node structure
//compatable with various types of grid pathfinders (Dijkstra, A*, Jump Point Search, Theta* etc.)
//which means - that's all you need for that project.

struct Node
{
    int     i, j; //grid cell coordinates
    double  F = 0, g = 0, H = 0; //f-, g- and h-values of the search node
    int parent;
    bool break_ties = false;
    // Node    *parent = nullptr; //backpointer to the predecessor node (e.g. the node which g-value was used to set the g-velue of the current node)

    bool operator == (const Node &other) const {
        return i == other.i && j == other.j;
    }
    bool operator < (const Node & other) const {
        if (F >= other.F) {
            if (F == other.F) {
                if (break_ties == CN_SP_BT_GMAX && other.g >= g ||
                        break_ties == CN_SP_BT_GMIN && other.g <= g) {
                    return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return true;
        }
        return g > other.g;
        /* if (break_ties) {
            if (g + H < other.g + other.H) {
                return g + H < other.g + other.H;
            }
            return g > other.g;
            }
        return g < other.g; */
    }
    void print() {
        std::cout << "i = " << i << " j = " << j << std::endl;
        std::cout << "g = " << g << "H = " << H << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
};
#endif
