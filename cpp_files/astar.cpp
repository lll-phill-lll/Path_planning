#include "astar.h"


Astar::Astar(double HW, bool BT)
{
    hweight = HW;
    breakingties = BT;
}

double Astar::computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options)
{
     return sqrt((i1 - i2) * (i1 - i2) + (j1 - j2) * (j1 - j2));
}
