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
        double dx = abs(i1 - i2);
        double dy = abs(j1 - j2);
        double D = 1, D2 = sqrt(2);
        return hweight * sqrt(D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy));
    }
    return 0;
}
