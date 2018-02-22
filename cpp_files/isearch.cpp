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
    int width = map.getMapWidth();
    int nodes = 0;
    int steps = 0;
    Node start;
    ++nodes;
    start.i = (map.getStart()).first;
    start.j = (map.getStart()).second;
    start.g = 0;
    int finish_i = (map.getFinish()).first;
    int finish_j = (map.getFinish()).second;
    (start).H = computeHFromCellToCell((map.getStart()).first, (map.getStart()).second, finish_i, finish_j, options);
    (start).parent = -1;
    bool reached = false;
    open.push_back(start);
    Node finish_node;
    ++nodes;
    while (!open.empty()) {
        ++steps;
        open.sort();
        Node v = *open.begin();
        open.erase(std::find(open.begin(), open.end(), v));
        int current_key = width * v.i + v.j;
        close[current_key] = v;
        if (v.i == finish_i && v.j == finish_j) {
            reached = true;
            finish_node.i = v.i;
            finish_node.j = v.j;
            finish_node.parent = v.parent;
            finish_node.g = v.g;
            finish_node.H = v.H;
            open.push_back(finish_node);
            break;
        }
        std::list<Node> Successors = findSuccessors(v, map, options);

        for (auto successor : Successors) {
            int adj_i = successor.i;
            int adj_j = successor.j;
            int node_key = width * adj_i + adj_j;
            bool node_in_closed = false;
            auto it = close.find(node_key);
            if (it != close.end()) {
                node_in_closed = true;
            }
            if (!node_in_closed) {
                bool node_in_open = false;
                auto it_open = open.begin();
                for (it_open; it_open != open.end(); ++it_open) {
                    if ((*it_open).i == adj_i && (*it_open).j == adj_j) {
                        node_in_open = true;
                        break;
                    }
                }
                if (!node_in_open) {
                    Node adj_node;
                    ++nodes;
                    adj_node.i = adj_i;
                    adj_node.j = adj_j;
                    adj_node.g = v.g + successor_g(v, adj_node);
                    adj_node.parent = current_key;
                    adj_node.H = computeHFromCellToCell(adj_i, adj_j, finish_i, finish_j, options);
                    open.push_back(adj_node);
                } else {
                    if ((*it_open).g > v.g + successor_g(v, *it_open)) {
                        (*it_open).g = v.g + successor_g(v, *it_open);
                        (*it_open).H = v.H;
                        (*it_open).parent = current_key;
                    }
                }

            }
        }
    }
    makePrimaryPath(finish_node);
    if (reached) {
        lppath.push_front(start);
    }
    makeSecondaryPath();
    unsigned int finish_time = clock();
    sresult.pathfound = reached;
    sresult.nodescreated = nodes ;
    sresult.numberofsteps = steps;
    sresult.time = finish_time - start_time;
    sresult.hppath = &hppath;
    sresult.lppath = &lppath;
    return sresult;
}

double ISearch::successor_g(Node a, Node b) {
    int i_parent = a.i, j_parent = a.j, i = b.i, j = b.j;
    if (abs(i_parent - i) - abs(j_parent - j) != 0) {
        return 1;
    } else {
        return sqrt(2);
    }
}

std::list<Node> ISearch::findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options) {
    std::list<Node> successors;
    Node to_insert;
    int bariers_around;
    for (int i = -1; i != 2; ++i) {
        for (int j = -1; j != 2; ++j) {
            if (!(i == 0 && j == 0)) {
                int adj_i = curNode.i + i;
                int adj_j = curNode.j + j;
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
                            if (i == 0 || j == 0) {
                                successors.push_front(to_insert);
                            } else {
                                successors.push_back(to_insert);
                            }
                        } else if (options.cutcorners) {
                            if (bariers_around == 1) {
                                to_insert.i = adj_i;
                                to_insert.j = adj_j;
                                if (i == 0 || j == 0) {
                                    successors.push_front(to_insert);
                                } else {
                                    successors.push_back(to_insert);
                                }
                            } else if (options.allowsqueeze) {
                                to_insert.i = adj_i;
                                to_insert.j = adj_j;
                                if (i == 0 || j == 0) {
                                    successors.push_front(to_insert);
                                } else {
                                    successors.push_back(to_insert);
                                }
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

void ISearch::makePrimaryPath(Node curNode) {
    while (curNode.parent != -1) {
        lppath.push_front(curNode);
        curNode = close[curNode.parent];
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

