/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-26
 * @PROBLEM: pointinpolygon
 *      The problem is to see if a given point is inside
 *      a polygon which is defined of segments between points.
 *      This is solved with a simple ray-casting algorithm
 *      which casts the point to inf in x-axis, and sees how
 *      many segments it crosses.
 * @COMPLEXITIES:
 *      TIME: O(n)
*/


#include <bits/stdc++.h>
#include <iostream>

using namespace std;

double ERR = 1e-9;
int OUTSIDE = -1, INSIDE = 1, ONSEGMENT = 0;

/**
 * Point represents a point/vector in 2d space
 */
struct Point {
    double x, y;

    Point(double x, double y) { this->x = x, this->y = y; }

    Point() { this->x = 0, this->y = 0; }

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
        if (a.distance(projection) + b.distance(projection) - a.distance(b) > ERR) pDistToLine = INFINITY;
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

    Point operator+(const Point &p) const { return (Point(this->x + p.x, this->y + p.y)); }

    Point operator-(const Point &p) const { return (Point(this->x - p.x, this->y - p.y)); }

    Point operator*(const Point &p) const { return (Point(this->x * p.x, this->y * p.y)); }

    Point operator*(const double &dist) const { return (Point(this->x * dist, this->y * dist)); }

    Point operator/(const Point &p) const { return (Point(this->x / p.x, this->y / p.y)); }

    Point operator/(const double &dist) const { return (Point(this->x / dist, this->y / dist)); }

};

/**
 * If segment @param p to {inf, p.y} is crossing segment between @param a and @param b
 */
bool lineIntersecting(const Point &p, const Point &a, const Point &b) {
    return ((p.y < a.y != p.y < b.y) && (p.x < a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y)));
}


/**
 * if @parm p is on segment between points @parm a and @parm b
 */
bool overLapping(const Point &p, const Point &a, const Point &b) {
    return p.shortestDistanceToLine(a, b) < ERR;
}

/**
 * If a given point is inside a polygon. This is solved with
 * a simple ray-casting algorithm which casts the point in
 * x-axis to inf, and sees how many segments it crosses. If it's
 * an even amount, the point is inside, else not inside.
 *
 * @param p the point to check if inside
 * @param polygon segments between point i and point i+1, where n+1=0
 * @return if @param p is inside, on, or outside @param polygon
 */
int pointInside(const Point &p, vector<Point> polygon) {
    int n = polygon.size();
    int count = 0;
    for (int i = 0; i < n; ++i) {
        // Next point to make segment with
        int ii = i + 1 < n ? i + 1 : 0;
        // Point is on segment
        if (overLapping(p, polygon[i], polygon[ii])) return ONSEGMENT;
        if (lineIntersecting(p, polygon[i], polygon[ii]))
            count++;
    }
    // If crossed even amount of segments, point is inside
    return (count % 2 != 0) ? INSIDE : OUTSIDE;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    double a, b;
    while (cin >> n && n != 0) {
        vector<Point> polygon(n);
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            polygon[i] = {a, b};
        }
        // queries
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b;
            Point p(a, b);
            auto res = pointInside(p, polygon);
            cout << (res == INSIDE ? "in" : res == OUTSIDE ? "out" : "on") << '\n';
        }
    }
    cout << flush;
    return 0;
}