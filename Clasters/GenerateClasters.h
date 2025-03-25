#pragma once

#include"DiskClass.h"
#include"RandomPoints.h"
#include<iostream>
#include<set>

using PointSet=std::set<Point,cmp>;


namespace clasters{
    void GenerateClasters();
    std::pair<PointSet,PointSet> GeneratePointsInSquare(int n,int m, int l);
    std::pair<PointSet,std::vector<PointSet>> coveredPoints(std::set<Point, cmp> pointSet,std::set<Point, cmp> centerSet);
}