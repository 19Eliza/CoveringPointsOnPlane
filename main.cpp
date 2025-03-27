#include"PointClass.h"
#include"RandomPoints.h"
#include"GenerateClusters.h"
#include<iostream>

int main(){
    Point p{1,2};
    std::cout<<p<<std::endl;
    auto [optional, mandatory] = clusters::GenerateClusters();
    std::cout<<optional.size()<<std::endl;
    return 0;
}