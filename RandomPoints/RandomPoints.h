#include "GeometryObjectsClass.h"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <set>

namespace randomPoints {
std::set<Point, cmp> GenerateRandomPoints(int n, int l);//generate n random points in square [0,l]*[0,l]

std::set<Point, cmp> GenerateRandomPointsAtOneDistance(int n, int l);//generate n random points in square [0,l]*[0,l]
}

// Point generateRandomPoint(double l) {
//     return {static_cast<double>(rand()) / RAND_MAX * l,
//             static_cast<double>(rand()) / RAND_MAX * l};
// }

// std::set<Point> generateUniquePoints(int n, double l) {
//     std::set<Point> points;

//     while (points.size() < n) {
//         points.insert(generateRandomPoint(l));
//     }
//     return points;
// }