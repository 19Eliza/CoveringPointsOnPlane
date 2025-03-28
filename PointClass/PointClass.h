#pragma once

#include<iostream>
#include<string>
#include<cmath>

//class Point

class Point{
    protected:
        double x;
        double y;
    public:
        Point();
        Point(double x_, double y_);
        Point(std::string x_str, std::string y_str);
    
        Point(const Point& p);
    
        double Dist(const Point& p)const;
    
        double SetX()const;
        double SetY()const;
    
        Point& operator=(const Point& p);
    
        friend std::ostream& operator<<(std::ostream& os ,const Point& p);
        friend std::istream& operator>>(std::istream& is,Point& p);
    };


    //Компаратор

class cmp {
    public:
        bool operator()(const Point p1, const Point p2)const {
            if (p1.SetX() < p2.SetX()) return true;
            
            if (p1.SetX() > p2.SetX()) return false;
    
            if (p1.SetY() < p2.SetY()) return true;
            else return false;
        }
    };