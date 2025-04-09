#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


// class Point

class Point {
protected:
  double x;
  double y;

public:
  Point();
  Point(double x_, double y_);
  Point(std::string x_str, std::string y_str);

  Point(const Point &p);

  double Dist(const Point &p) const;

  double SetX() const;
  double SetY() const;

  Point &operator=(const Point &p);

  bool operator==(const Point& p)const;
  bool operator!=(const Point& p)const;

  bool operator<(const Point& other) const {
    return (x < other.x) || (x == other.x && y < other.y);
}

  friend std::ostream &operator<<(std::ostream &os, const Point &p);
  friend std::istream &operator>>(std::istream &is, Point &p);
};

//Компаратор

class cmp {
public:
  bool operator()(const Point p1, const Point p2) const {
    if (p1.SetX() < p2.SetX())
      return true;

    if (p1.SetX() > p2.SetX())
      return false;

    if (p1.SetY() < p2.SetY())
      return true;
    else
      return false;
  }
};

using PointSet = std::set<Point, cmp>;
using PointVector = std::vector<Point>;
using pairPointPoint= std::pair<Point,Point>;


//class Disk

class Disk {
  private:
      Point center;
      double radius;
  public:
      Disk();
      Disk(double x, double y);
      Disk(const Point& p);
  
      double Dist(const Disk& d)const;
  
      bool PointIsBelong(const Point& p)const;
  
      //double Length()const;
      //double Square()const;

      PointSet IntersectionDisk(const Disk& d1) const;
  
      friend std::ostream& operator<<(std::ostream& os, const Disk& d);
      friend std::istream& operator>>(std::istream& is, Disk& d);
  
  };

// class Segment

class Segment {
protected:
  Point p1_;
  Point p2_;

public:
  Segment(Point p1, Point p2) : p1_(p1), p2_(p2){};
  Segment(double x1, double y1, double x2, double y2)
      : p1_(Point(x1, y1)), p2_(Point(x2, y2)){};
  Segment(const Segment &s) {
    p1_ = s.p1_;
    p2_ = s.p2_;
  }
  Point IntersectionSegment(const Segment &s) const;
};

// class Triangle

class Triangle {
protected:
  Point p1_;
  Point p2_;
  Point p3_;

public:
  Triangle(Point p1, Point p2, Point p3) : p1_(p1), p2_(p2), p3_(p3){};
  Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
      : p1_(Point(x1, y1)), p2_(Point(x2, y2)), p3_(Point(x3, y3)){};
  Point CentroidTriangle() const {
    double x = (p1_.SetX() + p2_.SetX() + p3_.SetX()) / 3.0;
    double y = (p1_.SetY() + p2_.SetY() + p3_.SetY()) / 3.0;
    return Point{x, y};
  }
};

// class Polygon

class Polygon {
protected:
  std::vector<Point> plg_;

public:
  Polygon(std::vector<Point> plg) : plg_(plg){};
  bool IsBelongPolygon(const Point &p) const;
};