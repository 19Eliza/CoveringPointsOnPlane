#include "CoverAlgorithm.h"

namespace coverAlgorithm {

std::pair<Point, std::pair<int, PointSet>>
CoveredMaxPointOneCluster(const PointSet& optional, const PointVector& position) {
  PointSet coveredOptional;
  int max = 0;
  Point optPosition;
  for (auto pos : position) {
    PointSet coveredOptionalTmp;
    for (auto pointOptional : optional) {
      if (pos.Dist(pointOptional) <= 1.0)
        coveredOptionalTmp.insert(pointOptional);
    }
    if (coveredOptionalTmp.size() > max) {
      max = coveredOptionalTmp.size();
      coveredOptional = coveredOptionalTmp;
      optPosition = pos;
    }
  }
  //std::cout<<"3\n";
  return {optPosition, {max, coveredOptional}};
}

std::pair<std::pair<std::size_t, Point>, std::pair<int, PointSet>>
CoveredMaxPoint(const PointSet& optional,
                const std::map<std::size_t, PointVector>& position) {
  PointSet coveredOptionalGlobal;
  int maxGlobal = 0;
  std::size_t indexCluster;
  Point optimalPosition;
  for (auto iter = position.begin(); iter != position.end(); ++iter) {
    auto [optPos, pairCountOptional] =
        CoveredMaxPointOneCluster(optional, iter->second);
    auto max = pairCountOptional.first;
    auto coveredOptional = pairCountOptional.second;

    if (max > maxGlobal) {
      maxGlobal = max;
      coveredOptionalGlobal = coveredOptional;
      indexCluster = iter->first;
      optimalPosition = optPos;
    }
  }
  //std::cout<<"2\n";
  return {{indexCluster, optimalPosition}, {maxGlobal, coveredOptionalGlobal}};
}

std::pair<int, std::map<std::size_t, Point>>
GreedyAlgorithm(const PointSet& optional_, const std::vector<PointVector> &I) {
  std::size_t m = I.size();

  PointSet optional=optional_;
  
  std::map<std::size_t, PointVector> position;
  for (auto i = 0; i < m; ++i){
    if(!I[i].empty())position.insert({i, I[i]});
  }

  int sumCoveredPoints = 0;
  std::map<std::size_t, Point> optimalPositionDisk;

  while (!position.empty() && !optional.empty() ) {
    //std::cout<<"1\n";
    auto prevSumCoveredPoints = sumCoveredPoints;
    auto [pairIndClusterPosition, pairCountOptional] =
        CoveredMaxPoint(optional, position);

    auto indexCluster = pairIndClusterPosition.first;
    auto optimalPosition = pairIndClusterPosition.second;

    auto maxCount = pairCountOptional.first;
    auto coveredOptional = pairCountOptional.second;

    sumCoveredPoints += maxCount;

    if(prevSumCoveredPoints==sumCoveredPoints)break;
    //std::cout<<sumCoveredPoints<<std::endl;
    position.erase(indexCluster);
    for (auto pt : coveredOptional)
      optional.erase(pt);

    optimalPositionDisk.insert({indexCluster, optimalPosition});
  }

  for(std::size_t i=0;i<position.size();++i){
    if(optimalPositionDisk.find(i)== optimalPositionDisk.end())optimalPositionDisk[i]=position[i][0];
  }

  return {sumCoveredPoints, optimalPositionDisk};
}

} // namespace coverAlgorithm