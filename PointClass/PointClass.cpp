#include"PointClass.h"


//Class Point

Point::Point() {
	x = y = 0;
}

Point::Point(double x_, double y_) {
	x = x_;
	y = y_;
}

Point::Point(std::string x_str, std::string y_str) {
	x = stold(x_str);
	y = stold(y_str);
}

Point::Point(const Point& p) {
	x = p.x;
	y = p.y;
}

double Point::Dist(const Point& p)const {
	return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
}

double Point::SetX()const { return x; };
double Point::SetY()const { return y; };

Point& Point::operator=(const Point& p) {
	x = p.x;
	y = p.y;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << p.x << " " << p.y << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
	is >> p.x >> p.y;
	return is;
}