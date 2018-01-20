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
    int steps = 0;
    Node *start = new Node;
    ++nodes;
    (*start).i = (map.getStart()).first;
    (*start).j = (map.getStart()).second;
    (*start).g = 0;
    int finish_i = (map.getFinish()).first;
    int finish_j = (map.getFinish()).second;
    (*start).H = computeHFromCellToCell((map.getStart()).first, (map.getStart()).second, finish_i, finish_j, options);
    (*start).parent = nullptr;
    bool reached = false;
    open.insert(start);
    Node *finish_node = new Node;
    ++nodes;
    while (!open.empty()) {
        ++steps;
        Node *v = *open.begin();
        open.erase(v);
        close.insert(v);
        if ((*v).i == finish_i && (*v).j == finish_j) {
            reached = true;
            (*finish_node).i = (*v).i;
            (*finish_node).j = (*v).j;
            (*finish_node).parent = (*v).parent;
            (*finish_node).g = (*v).g;
            (*finish_node).H = (*v).H;
            open.insert(finish_node);
            break;
        }
        std::list<Node> Successors = findSuccessors(v, map, options);
        for (auto successor : Successors) {
            int adj_i = successor.i;
            int adj_j = successor.j;
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
                    (*adj_node).H = computeHFromCellToCell(adj_i, adj_j, finish_i, finish_j, options);
                    open.insert(adj_node);
                } else {
                    if ((*(*it)).g > (*v).g + 1) {
                        (*(*it)).g = (*v).g + 1;
                        (*(*it)).H = (*v).H;
                        (*(*it)).parent = v;
                    }
                }

            }
        }
    }
    makePrimaryPath(finish_node);
    if (reached) {
        lppath.push_front(*start);
    }
    makeSecondaryPath();
    for(auto i : open) {
        delete i;
    }
    for (auto i : close) {
        delete i;
    }
    unsigned int finish_time = clock();
    sresult.pathfound = reached;
    sresult.nodescreated = nodes ;
    sresult.numberofsteps = steps;
    sresult.time = finish_time - start_time;
    sresult.hppath = &hppath;
    sresult.lppath = &lppath;
    return sresult;
}

std::list<Node> ISearch::findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options) {
    std::list<Node> successors;
    Node to_insert;
    int bariers_around;
    for (int i = -1; i != 2; ++i) {
        for (int j = -1; j != 2; ++j) {
            if (!(i == 0 && j == 0)) {
                int adj_i = (*curNode).i + i;
                int adj_j = (*curNode).j + j;
                if (adj_i >= 0 && adj_j >= 0 && adj_i < map.getMapHeight() &&
                        adj_j < map.getMapWidth() && !map.getValue(adj_i, adj_j)) {
                    bariers_around = 0;
                    if (i != 0 && j != 0) {
                        if (map.getValue(adj_i, adj_j - j)) {
                            ++bariers_around;
                        }
                        if (map.getValue(adj_i - i, adj_j)) {
                            ++bariers_around;
                        }
                    }
                    if (options.allowdiagonal) {
                        if (bariers_around == 0) {
                            to_insert.i = adj_i;
                            to_insert.j = adj_j;
                            successors.push_back(to_insert);
                        } else if (options.cutcorners) {
                            if (bariers_around == 1) {
                                to_insert.i = adj_i;
                                to_insert.j = adj_j;
                                successors.push_back(to_insert);
                            } else if (options.allowsqueeze) {
                                to_insert.i = adj_i;
                                to_insert.j = adj_j;
                                successors.push_back(to_insert);
                            }
                        }
                    } else {
                        if (i == 0 || j == 0) {
                            to_insert.i = adj_i;
                            to_insert.j = adj_j;
                            successors.push_back(to_insert);
                        }
                    }
                }
            }
        }
    }
    return successors;
}

void ISearch::makePrimaryPath(Node *curNode) {
    while ((*curNode).parent != nullptr) {
        lppath.push_front(*curNode);
        curNode = (*curNode).parent;
    }
}

void ISearch::makeSecondaryPath() {
    bool direction_chosen = false;
    Node prev;
    int i_dif = 0, j_dif = 0;
    for (auto node : lppath) {
        if (!direction_chosen) {
            prev = node;
            direction_chosen = true;
        } else {
            if (prev.i - node.i != i_dif || prev.j - node.j != j_dif) {
                hppath.push_back(prev);
                i_dif = prev.i - node.i;
                j_dif = prev.j - node.j;
                prev = node;
            } else {
                prev = node;
            }
        }
    }
    hppath.push_back(*lppath.rbegin());
}

