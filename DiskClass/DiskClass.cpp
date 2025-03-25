#include"DiskClass.h"

//Class Disk

Disk::Disk() :center(0, 0), radius(1) {};

Disk::Disk(double x, double y, double r = 1.0) :center(x, y), radius(r) {};

Disk::Disk(const Point& p, double r = 1.0) :center(p), radius(r) {};

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
