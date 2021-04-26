/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-26
 * @PROBLEM: polygonarea
 *      The problem is to calculate the area of a polygon defined
 *      by a set of points. This is solved with the Shoelace formula.
 * @COMPLEXITIES:
 *      TIME: O(n)
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/**
 * Point represents a point/vector in 2d space
 */
struct Point {
    double x, y;

    Point(double x, double y) {
        this->x = x, this->y = y;
    }

    Point() {
        this->x = 0, this->y = 0;
    }

    /**
     * Distance from current point to other point
     * @param p point to find distance to
     * @return distance between points
     */
    double distance(const Point &p) const {
        Point diff = (*this) - p;
        return sqrt(diff.x * diff.x + diff.y * diff.y);
    }

    /**
     * Calculates the shortest distance between a point and a line, which is
     * defined by two points.
     * @param a start of the line
     * @param b end of the line
     * @return the shortest distance between this point and the given line
     */
    double shortestDistanceToLine(const Point &a, const Point &b) const {
        double len = a.distance(b);
        // a and b are same, return distance to them
        if (len == 0) return this->distance(a);

        // How far on the line between point a and point b that point p is projected
        double u =
                ((this->x - a.x) * (b.x - a.x) + ((this->y - a.y) * (b.y - a.y))) /
                (len * len);
        Point projection = {a.x + u * (b.x - a.x), a.y + u * (b.y - a.y)};

        double pDistToLine = this->distance(projection);
        // If point is on the line
        if (pDistToLine < 1e-8) pDistToLine = INFINITY;
        // If projection lies outside the line
        if (a.distance(projection) + b.distance(projection) - a.distance(a) > 1e-8) pDistToLine = INFINITY;
        // Distance to projection on line if valid, else the min distance to any of starting points
        return min(pDistToLine, min(this->distance(a), this->distance(b)));
    }

    double dotProduct(const Point &p) const {
        return this->x * p.x + this->y * p.y;
    }

    /**
     * Cross product between two points in 2d-space,
     * which really isn't defined but it  is often
     * interpreted as following.
     */
    double crossProduct(const Point &p) const {
        return (this->x * p.y - this->y * p.x);
    }

    Point operator+(const Point &p) const {
        double x = this->x + p.x;
        double y = this->y + p.y;
        return (Point(x, y));
    }

    Point operator-(const Point &p) const {
        double x = this->x - p.x;
        double y = this->y - p.y;
        return (Point(x, y));
    }

    Point operator*(const Point &p) const {
        double x = this->x * p.x;
        double y = this->y * p.y;
        return (Point(x, y));
    }

    Point operator*(const double &dist) const {
        double x = this->x * dist;
        double y = this->y * dist;
        return (Point(x, y));
    }


    Point operator/(const Point &p) const {
        double x = this->x / p.x;
        double y = this->y / p.y;
        return (Point(x, y));
    }

    Point operator/(const double &dist) const {
        double x = this->x / dist;
        double y = this->y / dist;
        return (Point(x, y));
    }

};

/**
 * Calculates the area of a polygon according to the Shoelace formula.
 * @param points the points defining the polygon.
 * @return If order of points are clockwise (CW) or counter clockwise,
 * and the total area of the polygon
 */
tuple<string, double> polyArea(vector<Point> points) {
    int n = points.size();
    double area = 0;
    for (int i = 0; i < n; ++i) {
        int i1 = i + 1 < n ? i + 1 : 0;
        area += (points[i1].x + points[i].x) * (points[i1].y - points[i].y);
    }
    area /= 2;

    // If area is negative, the points were defined clockwise order, else counter clockwise
    string order = area < 0 ? "CW" : "CCW";

    return {order, abs(area)};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Insert code here
    int n;
    double a, b;
    while (cin >> n && n != 0) {
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            points[i] = {a, b};
        }
        auto res = polyArea(points);
        printf("%s %.1f\n", get<0>(res).c_str(), get<1>(res));
    }
    cout << flush;
    return 0;
}