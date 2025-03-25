#include"GenerateClasters.h"

namespace Clasters{
    void GenerateClasters(){
        int n, m, l; // n-количество необязательных точек;
                    // m-количество обязательных точек;
                    // l-размер квадрата [0,l]*[0,l], в котором распределны точки

        std::cout<<"\nEnter count of optional points (n), count of mandatory points (m), size of square (l):\n";
        std::cin >> n >> m >> l;

        assert(std::cin.good());

        auto [pointSet,centerSet]=GeneratePointsInSquare(n,m,l);

        auto [optional,mandatory]=coveredPoints(pointSet,centerSet);

    }

    std::pair<PointSet,PointSet> GeneratePointsInSquare(int n,int m,int l){

        std::set<Point, cmp> pointSet = randomPoints::GenerateRandomPoints(n, l); //генерация точек, которые требуется покрыть
        std::set<Point, cmp> centerSet = randomPoints::GenerateRandomPoints(m, l); //генерация центров

        return {pointSet,centerSet};

    }

    std::pair<PointSet,std::vector<PointSet> > coveredPoints(PointSet pointSet,PointSet centerSet){
        
        std::vector<PointSet> mandatory;
        PointSet optional;

        std::size_t i=0;
        for(auto center:centerSet){
            for(auto point : pointSet){
                if(center.Dist(point)<=1.0){
                    mandatory[i].insert(point);
                    pointSet.erase(point);
                }
            }
            ++i;
        }
        
        optional=pointSet;

        return {optional,mandatory};
    }

}