#include <iostream>
#include <fstream>
#include "GeometryObjectsClass.h"
#include "RandomPoints.h"
#include "ConvexHall.h"
#include "GenerateClusters.h"
#include "CoverAlgorithm.h"

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include "PointsWidget.h"

std::string Mandatory="mandatory.txt";
std::string Optional="optional.txt";


inline uint qHash(const Point &point, uint seed = 0) {

  return qHash(QPair<int, int>(point.SetX(), point.SetY()), seed);
}

int main() {

  int N,M,l;

  std::tie(N,M,l)=clusters::EnterParameters();

  auto [optional, mandatory] = clusters::GenerateClusters(N,M,l); //Set of optional points, vector of PointVec of mandatory points
  std::cout << "Count of optional set points: " << optional.size() << std::endl;

  std::ofstream fout1{Mandatory};
  int i=1;
  for(auto vect :mandatory){
    fout1<<"Cluster "<<i<<std::endl;
      for(auto point:vect )
      fout1<<point;
    fout1<<std::endl;
    ++i;
  }

  std::ofstream fout2{Optional};
  for(auto point :optional)fout2<<point;

  auto m = mandatory.size();
  std::vector<PointVector> ConvexHullMandatoryPoint(m);
  int j = 0;
  for (auto i = 0; i < m; i++) {
    if (!mandatory[i].empty()) {
      ConvexHullMandatoryPoint.at(i) = convexHull::ConvexHull(mandatory[i]);
      j++;
    }
  }
  std::cout << "Clusters count of mandatory points: " << m << std::endl;

  if(!optional.empty()){
  std::vector<PointVector> I=clusters::Position(optional,ConvexHullMandatoryPoint);

  for(int i=0;i<I.size();++i){
    if(I[i].empty()) I[i].push_back(mandatory[i][0]);
    else continue;
  }
  auto [optimalCountCoveredPoints,optimalPositionDisks]=coverAlgorithm::GreedyAlgorithm(optional,I);
  std::cout<<optimalCountCoveredPoints<<std::endl;
}

  int argc = 0;
  char** argv = nullptr;
  QApplication a(argc, argv);

    PointWidget w;
    w.setL(l); 
    w.setOptional(optional);
    w.setMandatory(mandatory);

    w.show();

    return a.exec();
}