#include"PointClass.h"
#include"RandomPoints.h"
#include"GenerateClusters.h"
#include"ConvexHall.h"
#include<iostream>

int main(){
    Point p{1,2};
    std::cout<<p<<std::endl;
    auto [optional, mandatory] = clusters::GenerateClusters();
    std::cout<<"Size of optional set points: "<<optional.size()<<std::endl;

    auto m=mandatory.size();
    std::vector<PointVector> ConvexHallMandatoryPoint(m);
    int j=0;
    for(auto i=0;i<m;i++){
            if(!mandatory[i].empty()){
                //std::cout<<"Size of mandatory set points: "<<mandatory[i].size()<<std::endl;
                ConvexHallMandatoryPoint.at(i)=convexHull::ConvexHull(mandatory[i]);
                //if(!ConvexHallMandatoryPoint.at(i).empty()) std::cout<<"Size of Convex Hull: "<<ConvexHallMandatoryPoint[i].size()<<std::endl;
                j++;
        }
    }
    std::cout<<"Size of mandatory set points: "<<j<<std::endl;
    return 0;
}