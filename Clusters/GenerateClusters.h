#pragma once

#include "PointClass.h"
#include "RandomPoints.h"
#include <iostream>
#include <set>
#include <vector>

using PointSet = std::set<Point, cmp>;
using PointVector = std::vector<Point>;

namespace clusters {
std::pair<PointSet, std::vector<PointVector>> GenerateClusters();
std::pair<PointSet, PointSet> GeneratePointsInSquare(int n, int m, int l);

std::pair<PointSet, std::vector<PointVector>> coveredPoints(PointSet pointSet,
                                                            PointSet centerSet);
} // namespace clusters