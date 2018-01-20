#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "astar.h"

class Dijkstra : public ISearch
{
    public:
        Dijkstra();
    protected:
        double computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options);
};
#endif
