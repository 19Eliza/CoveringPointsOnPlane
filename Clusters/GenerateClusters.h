#pragma once

#include "GeometryObjectsClass.h"
#include "RandomPoints.h"
#include <iostream>
#include <set>
#include <vector>

namespace clusters {

std::pair<PointSet, std::vector<PointVector>> GenerateClusters();
std::pair<PointSet, PointSet> GeneratePointsInSquare(int n, int m, int l);

std::pair<PointSet, std::vector<PointVector>> coveredPoints(PointSet pointSet,
                                                            PointSet centerSet);
std::pair<PointVector,PointVector> ChooseRandomCountPoints(PointVector mandatoryCluster);

std::vector<PointVector> Position(const PointSet &optional,
                                  const std::vector<PointVector> &CH);
} // namespace clusters