#include "isearch.h"
#include <set>

ISearch::ISearch()
{
    hweight = 1;
    breakingties = CN_SP_BT_GMAX;
}

ISearch::~ISearch(void) {}


SearchResult ISearch::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{
    std::cout << (map.getStart()).first << " " << (map.getStart()).second << std::endl << (map.getFinish()).first << " " << (map.getFinish()).second << std::endl;
    std::set<Node> open;
    std::set<Node> closed;
    Node start;
    start.i = (map.getStart()).first;
    start.j = (map.getStart()).second;
    int finish_i = (map.getFinish()).first;
    int finish_j = (map.getFinish()).second;
    start.g = 0;
    open.insert(start);
    Node v;
    while (!open.empty()) {
        v = *open.begin();
        open.erase(v);
        closed.insert(v);
        if (v.i == finish_i && v.j == finish_j) {
            std::cout << "reached!" << std::endl;
            break;
        }
        for (int i = -1; i != 2; ++i) {
            for (int j = -1; j != 2; ++j) {
                if (!(i == 0 && j == 0)) {
                    int adj_i = v.i + i;
                    int adj_j = v.j + j;
                    if (adj_i >= 0 && adj_j >= 0 && adj_i < map.getMapHeight() && adj_j < map.getMapWidth()) {
                        Node adj;
                        adj.i = adj_i;
                        adj.j = adj_j;
                        std::cout << adj_i << " " << adj_j << std::endl;
                        auto it = std::find(closed.begin(), closed.end(), adj);
                        if (it == closed.end()) {
                            auto in_open = std::find(open.begin(), open.end(), adj);
                            if (in_open == open.end()) {
                                adj.g = v.g + 1;
                                open.insert(adj);
                            } else {
                                if ((*in_open).g > v.g + 1) {
                                    std::cout << "yes" << std::endl;
                                    // (*in_open).g = v.g + 1;

                                }
                            }

                        }
                    }
                }
            }
        }
    }



    /*sresult.pathfound = ;
    sresult.nodescreated =  ;
    sresult.numberofsteps = ;
    sresult.time = ;
    sresult.hppath = &hppath; //Here is a constant pointer
    sresult.lppath = &lppath;*/
    return sresult;
}

/*std::list<Node> ISearch::findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options)
{
    std::list<Node> successors;
    //need to implement
    return successors;
}*/

/*void ISearch::makePrimaryPath(Node curNode)
{
    //need to implement
}*/

/*void ISearch::makeSecondaryPath()
{
    //need to implement
}*/
