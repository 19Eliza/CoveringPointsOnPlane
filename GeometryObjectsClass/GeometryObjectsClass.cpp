#include "GeometryObjectsClass.h"



// Class Point

Point::Point() { x = y = 0; }

Point::Point(double x_, double y_) {
  x = x_;
  y = y_;
}

Point::Point(std::string x_str, std::string y_str) {
  x = stold(x_str);
  y = stold(y_str);
}

Point::Point(const Point &p) {
  x = p.x;
  y = p.y;
}

double Point::Dist(const Point &p) const {
  return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
}

double Point::SetX() const { return x; };
double Point::SetY() const { return y; };

Point &Point::operator=(const Point &p) {
  x = p.x;
  y = p.y;
  return *this;
}

bool Point::operator==(const Point& p)const{
  return (x==p.x)&&(y==p.y);
}

bool Point::operator!=(const Point& p) const {
  return !(*this == p);
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << p.x << " " << p.y << std::endl;
  return os;
}

std::istream &operator>>(std::istream &is, Point &p) {
  is >> p.x >> p.y;
  return is;
}

using PointSet = std::set<Point, cmp>;
using PointVector = std::vector<Point>;

//Class Disk

Disk::Disk() :center(0, 0), radius(1) {};

Disk::Disk(double x, double y) :center(x, y), radius(1.0) {};

Disk::Disk(const Point& p) :center(p), radius(1.0) {};

double Disk::Dist(const Disk& d)const {
	return center.Dist(d.center);
};

bool Disk::PointIsBelong(const Point& p)const{
	return center.Dist(p)<=radius;
}

std::ostream& operator<<(std::ostream& os, const Disk& d){
	os<<d.center;
	return os;
}

std::istream& operator>>(std::istream& is, Disk& d){
	is>>d.center;
	return is;
}


PointSet Disk::IntersectionDisk(const Disk& d1) const {

	PointSet set_center;

  Point p1=center;
  Point p2=d1.center;

	if (center.Dist(d1.center) > 2.0) {
		return set_center;
	}

	double c_0, d_0;
	c_0 = p2.SetX() - p1.SetX();
	d_0 = p2.SetY() - p1.SetY();

	double A, B;
	if (c_0 != 0.0) {
		A = -d_0 / c_0;
		B = d_0 * d_0 / (2.0 * c_0)+0.5*c_0;
		double G, K;
		G = 2.0 * A * B / (A * A + 1.0);
		K = (B * B - 1.0) / (A * A + 1.0);
		double discr;
		discr = G * G - 4.0 * K;
		if (discr > 0.0) {
			double y_1, y_2, x_1, x_2;

			y_1 = p1.SetY() + (-G + sqrt(discr)) / 2.0;
			x_1 = A * (y_1 - p1.SetY()) + B + p1.SetX();


			y_2 = p1.SetY() + (-G - sqrt(discr)) / 2.0;
			x_2 = A * (y_2 - p1.SetY()) + B + p1.SetX();

			set_center.insert(Point{ x_1,y_1 });
			set_center.insert(Point{ x_2,y_2 });
			return set_center;
		}
		if (discr == 0.0) {
			double y_1, y_2, x_1, x_2;

			y_1 = -G / 2.0 + p1.SetY();
			x_1 = A * (y_1 - p1.SetY()) + B + p1.SetX();
			set_center.insert(Point{ x_1,y_1 });
			return set_center;
			
		}
		if (discr < 0.0)return set_center;
	}
	else {
		double y_1, y_2, x_1, x_2;

		y_1 = d_0 / 2.0 + c_0 * c_0 / (2.0 * d_0) + p1.SetY();
		x_1 = sqrt(1.0 - d_0 * d_0 / 4.0) + p1.SetX();
		x_2 = -sqrt(1.0 - d_0 * d_0 / 4.0) + p1.SetX();
		set_center.insert(Point{ x_1,y_1 });
		set_center.insert(Point{ x_2,y_1 });
		return set_center;
	}

}

// class Segment

Point Segment::IntersectionSegment(const Segment &s) const {
  auto x1 = p1_.SetX();
  auto y1 = p1_.SetY();
  auto x2 = p2_.SetX();
  auto y2 = p2_.SetY();

  auto x3 = s.p1_.SetX();
  auto y3 = s.p1_.SetY();
  auto x4 = s.p2_.SetX();
  auto y4 = s.p2_.SetY();

  auto A1 = y2 - y1;
  auto B1 = x1 - x2;
  auto C1 = x2 * y1 - x1 * y2;

  auto A2 = y4 - y3;
  auto B2 = x3 - x4;
  auto C2 = x4 * y3 - x3 * y4;

  auto D = A1 * B2 - A2 * B1;

  if (D == 0) {
    std::cout << "Segment does not intersect!\n";
    return Point{0, 0};
  } else {
    double x = static_cast<double>(C1 * B2 - C2 * B1) / D;
    double y = static_cast<double>(A1 * C2 - A2 * C1) / D;
    return Point{x, y};
  }
}

// class Polygon

bool Polygon::IsBelongPolygon(const Point &z) const {
  if (plg_.size() < 3)
    return false;

  auto p1 = plg_[0];
  auto p2 = plg_[1];
  auto p3 = plg_[2];

  //auto q = Triangle(p1, p2, p3).CentroidTriangle();
  
  double xc=0,yc=0;
  for(auto pt: plg_){
    xc+=pt.SetX();
    yc+=pt.SetY();
  }
  double n=plg_.size();
  Point q{xc/n,yc/n};
  std::vector<Point> sortedPolygon;
  std::vector<double> corner;
  std::map<double, Point> cornerPoint;

  for (auto pt : plg_) {
    auto teta = atan2(pt.SetY() - q.SetY(), pt.SetX() - q.SetX());
    corner.push_back(teta);
    cornerPoint.insert({teta, pt});
  }
  //std::cout<<corner.size()<<" "<<cornerPoint.size()<<std::endl;

  //assert(corner.size() == cornerPoint.size());


  sort(corner.begin(), corner.end());

  for (auto teta : corner) {
    auto iter = cornerPoint.find(teta);
    if (iter != cornerPoint.end()) {
      auto pt = iter->second;
      sortedPolygon.push_back(pt);
    }
  }

  std::pair<Point, Point> ray;

  double prevDi;

  for (auto i = 0; i < sortedPolygon.size() - 1; i++) {
    auto pi = sortedPolygon[i];
    auto pi1 = sortedPolygon[i + 1];
    auto Di = (pi1.SetX() - pi.SetX()) * (z.SetY() - pi.SetY()) -
              (pi1.SetY() - pi.SetY()) * (z.SetX() - pi.SetX());

    auto sign = [](double x) {
      if (x >= 0)
        return 1;
      if (x < 0)
        return -1;
    };

    if (i == 0)
      prevDi = Di;
    else {
      if (sign(Di) != sign(prevDi))
        return false;
      else
        prevDi = Di;
    }
  }
  return true;
};
