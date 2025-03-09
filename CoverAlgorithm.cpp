#include"CoverAlgorithm.h"

namespace cover{
    std::set<Point, cmp> IntersectionDisk(const Point& p1, const Point& p2){
        std::set<Point, cmp> SetCenter;

        if (p1.Dist(p2) > 2.0) {
            return SetCenter;
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

                SetCenter.insert(Point{ x_1,y_1 });
                SetCenter.insert(Point{ x_2,y_2 });
                return SetCenter;
            }
            if (discr == 0.0) {
                double y_1, y_2, x_1, x_2;

                y_1 = -G / 2.0 + p1.SetY();
                x_1 = A * (y_1 - p1.SetY()) + B + p1.SetX();
                SetCenter.insert(Point{ x_1,y_1 });
                return SetCenter;
                
            }
            if (discr < 0.0)return SetCenter;
        }
        else {
            double y_1, y_2, x_1, x_2;

            y_1 = d_0 / 2.0 + c_0 * c_0 / (2.0 * d_0) + p1.SetY();
            x_1 = sqrt(1.0 - d_0 * d_0 / 4.0) + p1.SetX();
            x_2 = -sqrt(1.0 - d_0 * d_0 / 4.0) + p1.SetX();
            SetCenter.insert(Point{ x_1,y_1 });
            SetCenter.insert(Point{ x_2,y_1 });
            return SetCenter;
        }
    }

    std::pair<std::vector<Point>,std::vector<Point> > EnterPoint(vector<point>& optional, vector<point>& mandatory){
        int a;
    }
}