#pragma once

#include<iostream>
#include"PointClass.h"

//class Disk

class Disk {
    private:
        Point center;
        double radius;
    public:
        Disk(){};
        Disk(double x, double y, double r = 1.0);
        Disk(const Point& p, double r = 1.0);
    
        double Dist(const Disk& d)const;
    
        bool PointIsBelong(const Point& p)const;
    
        //double Length()const;
        //double Square()const;
    
        friend std::ostream& operator<<(std::ostream& os, const Disk& d);
        friend std::istream& operator>>(std::istream& is, Disk& d);
    
    };