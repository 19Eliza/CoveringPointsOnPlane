#include "GeometryObjectsClass.h"
#include "RandomPoints.h"
#include "ConvexHall.h"
#include "GenerateClusters.h"
#include "CoverAlgorithm.h"
#include <iostream>
#include <fstream>

std::string Mandatory="mandatory.txt";
std::string Optional="optional.txt";

int main() {

  auto [optional, mandatory] = clusters::GenerateClusters();//Set of optional points, vector of PointVec of mandatory points
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
  // std::cout << "m: " << m<< std::endl;

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
  
  j=1;
  // for(auto el1:I){
  //   std::cout<<"Position cluster "<<j<<std::endl;
  //   for(auto el2:el1)std::cout<<el2<<std::endl;
  //   ++j;
  // }
  std::cout<<"End Position\n";
  auto [optimalCountCoveredPoints,optimalPositionDisks]=coverAlgorithm::GreedyAlgorithm(optional,I);
  std::cout<<optimalCountCoveredPoints<<std::endl;
}
  
  return 0;
}