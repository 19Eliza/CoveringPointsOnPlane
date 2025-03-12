#pragma once 

#include<iostream>
#include<cmath>
#include<vector>
#include<string>

// class Shape {
// public:
// 	virtual void Show() = 0;
// 	virtual ~Shape() {};
// };

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


//class Disk

// class Disk {
// private:
// 	Point center;
// 	double radius;
// public:
// 	Disk();
// 	Disk(double x, double y, double r = 1.0);
// 	Disk(const Point& p, double r = 1.0);

// 	double Dist(const Disk& d)const;

// 	bool PointIsBelong(const Point& p)const;

// 	double Length()const;
// 	double Square()const;

// 	friend std::ostream& operator<<(std::ostream& os, const Disk& d);
// 	friend std::istream& operator>>(std::istream& is, Disk& d);

// };


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