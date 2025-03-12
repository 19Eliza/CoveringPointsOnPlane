#include "RandomPoints.h"

int main() {

  int n, m, l; // n-количество необязательных точек;
               // m-количество обязательных точек;
               // l-размер квадрата [0,l]*[0,l], в котором распределны точки

  std::cin >> n >> m >> l;

  assert(std::cin.good());

  std::set<Point, cmp> pointSet = randomPoints::GenerateRandomPoints(n,l);//генерация точек, которые требуется покрыть
  std::set<Point, cmp> centerSet = randomPoints::GenerateRandomPoints(m,l);//генерация центров

  for (auto elem : pointSet)
    std::cout << elem << std::endl;

  return 0;
}