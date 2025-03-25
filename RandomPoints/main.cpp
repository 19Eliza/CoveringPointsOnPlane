#include "RandomPoints.h"


std::set<Point,cmp> CoveredPoints(std::set<Point, cmp> pointSet, std::set<Point, cmp> centerSet){
  auto m=centerSet.size();
  std::vector<std::set<Point,cmp>> coveredPoint(m);
  auto i=-1;
  for(auto center:centerSet){
    i++;
    for(auto point:pointSet){
      if(center.Dist(point)<=1)coveredPoint[i].insert(point);
    }
  }
}

int main() {

  int n, m, l; // n-количество необязательных точек;
               // m-количество обязательных точек;
               // l-размер квадрата [0,l]*[0,l], в котором распределны точки
  

  std::cout<<"\nEnter count of optional points (n), count of mandatory points (m), size of square (l):\n";
  std::cin >> n >> m >> l;

  assert(std::cin.good());

  std::set<Point, cmp> pointSet = randomPoints::GenerateRandomPoints(n, l); //генерация точек, которые требуется покрыть
  std::set<Point, cmp> centerSet = randomPoints::GenerateRandomPoints(m, l); //генерация центров

  
  
  for (auto elem : pointSet)
    std::cout << elem << std::endl;

  return 0;
}