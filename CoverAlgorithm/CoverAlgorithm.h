#pragma once

#include "GeometryObjectsClass.h"

namespace coverAlgorithm {
std::pair<Point, std::pair<int, PointSet>>
CoveredMaxPointOneCluster(const PointSet& optional,const PointVector& position);

std::pair<std::pair<std::size_t, Point>, std::pair<int, PointSet>>
CoveredMaxPoint(const PointSet& optional, const std::map<std::size_t, PointVector>& position);

std::pair<int, std::map<std::size_t, Point>>
GreedyAlgorithm(const PointSet& optional, const std::vector<PointVector> &I);
} // namespace coverAlgorithm
