#pragma once

#include "GeometryObjectsClass.h"
#include <algorithm>
#include <vector>

namespace convexHull {
bool LeftRotation(Point p1, Point p2, Point p3);
std::vector<Point> ConvexHull(std::vector<Point> &p);
} // namespace convex_hull