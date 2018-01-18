#include "isearch.h"


ISearch::ISearch()
{
    hweight = 1;
    breakingties = CN_SP_BT_GMAX;
}

ISearch::~ISearch(void) {}


SearchResult ISearch::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options)
{
    unsigned int start_time = clock();
    int nodes = 0;
    Node *start = new Node;
    ++nodes;
    (*start).i = (map.getStart()).first;
    (*start).j = (map.getStart()).second;
    (*start).g = 0;
    int finish_i = (map.getFinish()).first;
    int finish_j = (map.getFinish()).second;
    bool reached = false;
    open.insert(start);
    Node *finish_node = new Node;
    ++nodes;
    while (!open.empty()) {
        Node *v = *open.begin();
        open.erase(v);
        close.insert(v);
        if ((*v).i == finish_i && (*v).j == finish_j) {
            reached = true;
            (*finish_node).i = (*v).i;
            (*finish_node).j = (*v).j;
            (*finish_node).parent = v;
            (*finish_node).g = (*v).g;
            close.insert(finish_node);
            break;
        }
        for (int i = -1; i != 2; ++i) { // find successors
            for (int j = -1; j != 2; ++j) { // --"--
                if (!(i == 0 && j == 0)) { // --"--
                    int adj_i = (*v).i + i;
                    int adj_j = (*v).j + j;
                    if (adj_i >= 0 && adj_j >= 0 && adj_i < map.getMapHeight() &&
                            adj_j < map.getMapWidth() && !map.getValue(adj_i, adj_j)) {
                        bool node_in_closed = false;
                        auto it = close.begin();
                        for (it; it != close.end(); ++it) {
                            if ((*(*it)).i == adj_i && (*(*it)).j == adj_j) {
                                node_in_closed = true;
                                break;
                            }
                        }
                        if (!node_in_closed) {
                            bool node_in_open = false;
                            auto it = open.begin();
                            for (it; it != open.end(); ++it) {
                                if ((*(*it)).i == adj_i && (*(*it)).j == adj_j) {
                                    node_in_open = true;
                                    break;
                                }
                            }
                            if (!node_in_open) {
                                Node *adj_node = new Node;
                                ++nodes;
                                (*adj_node).i = adj_i;
                                (*adj_node).j = adj_j;
                                (*adj_node).g = (*v).g + 1;
                                (*adj_node).parent = v;
                                open.insert(adj_node);
                            } else {
                                if ((*(*it)).g > (*v).g + 1) {
                                    (*(*it)).g = (*v).g + 1;
                                    (*(*it)).parent = v;
                                }
                            }

                        }
                    }
                }
            }
        }
    }
    int steps = 0;
    Node *it = finish_node;
    if (reached) { // makePrimaryPath
        while ((*it).parent != nullptr) {
            std::cout << (*it).i << " " << (*it).j << std::endl;
            it = (*it).parent;
            ++steps;
        }
    }
    int deleted = 0;
    for(auto i : open) {
        delete i;
        ++deleted;
    }
    for (auto i : close) {
        delete i;
        ++deleted;
    }
    unsigned int finish_time = clock();
    std::cout << deleted << " deleted " << std::endl;

    sresult.pathfound = reached;
    sresult.nodescreated = nodes ;
    sresult.numberofsteps = steps;
    sresult.time = finish_time - start_time;
    /* sresult.hppath = &hppath; //Here is a constant pointer
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
