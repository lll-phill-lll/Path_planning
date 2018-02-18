#include "astar.h"


Astar::Astar(double HW, bool BT)
{
    hweight = HW;
    breakingties = BT;
}

double Astar::computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options)
{
    if (options.metrictype == CN_SP_MT_EUCL) {
        return hweight * sqrt((i1 - i2) * (i1 - i2) + (j1 - j2) * (j1 - j2));
    }
    if (options.metrictype == CN_SP_MT_MANH) {
        return hweight * (abs(i1 - i2) + abs(j1 - j2));
    }
    if (options.metrictype == CN_SP_MT_CHEB) {
        return hweight * (std::max(abs(i1 - i2), abs(j1 - j2)));
    }
    if (options.metrictype == CN_SP_MT_DIAG) {
        return hweight * std::min(abs(i1 - i2), abs(j1 - j2)) + abs(abs(i1 - i2) - abs(j1 - j2));
    }
    return 0;
}
