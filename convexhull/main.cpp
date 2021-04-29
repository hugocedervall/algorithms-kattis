/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-29
 * @PROBLEM: convexhull
 *      The problem is to create the smallest convex hull of a given set of points,
 *      in other words the task is to find minimal amount of points such that the points
 *      connected as segments will encapsulate all points in the set. This is solved
 *      with Graham's Scan algorithm, which basically divides the set of points into two
 *      sets divided by the segment between the smallest and largest point (largest firstly in
 *      terms of x-value). For every point in these sets, the orientation can be checked to see
 *      if a point should be included in the hull or not.
 *
 * @COMPLEXITIES:
 *      TIME: O(n*log(n)), where n = nr of points
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int CLOCKWISE = 1, COLINEAR = 0, COUNTER_CLOCKWISE = -1;

// Point coordinate type
typedef int pct;

/**
 * Point represents a point/vector in 2d space
 */
struct Point {
    pct x, y;

    Point(pct x, pct y) { this->x = x, this->y = y; }

    Point() { this->x = 0, this->y = 0; }

    bool operator<(const Point &p) const {
        if (this->x == p.x) return this->y < p.y;
        return this->x < p.x;
    }

    bool operator==(const Point &p) const {
        return this->x == p.x && this->y == p.y;
    }

    Point operator+(const Point &p) const { return (Point(this->x + p.x, this->y + p.y)); }

    Point operator-(const Point &p) const { return (Point(this->x - p.x, this->y - p.y)); }

    Point operator*(const Point &p) const { return (Point(this->x * p.x, this->y * p.y)); }

    Point operator*(const double &dist) const { return (Point(this->x * dist, this->y * dist)); }

    Point operator/(const Point &p) const { return (Point(this->x / p.x, this->y / p.y)); }

    Point operator/(const double &dist) const { return (Point(this->x / dist, this->y / dist)); }

};


/**
 * The orientation Point @param p has in relation to the segment
 * from point @param a to point @param b
 * @return either clockwise, counter clockwise, or colinear
 */
int orientation(Point &p, Point &a, Point &b) {
    double val = a.x * (p.y - b.y) + p.x * (b.y - a.y) + b.x * (a.y - p.y);
    return (val < 0) ? CLOCKWISE : (val > 0) ? COUNTER_CLOCKWISE : COLINEAR;
}

/**
 * Creates a convex hull from a given set of points. This is done
 * with Graham's scan algorithm.
 *
 * @param ps the points to create convex hull from.
 * @param res the points that create convex hull in counter
 * clockwise order.
 */
void convexHull(vector<Point> &ps, vector<Point> &res) {
    // If only one point, solution already found
    if (ps.size() <= 1) {
        copy(ps.begin(), ps.end(), back_inserter(res));
        return;
    };

    /* Contains two sets of points, which are divided by the line from the smallest
     * to the biggest point */
    vector<Point> up, down;
    sort(ps.begin(), ps.end());
    /* First and last points, sorted on x-value and secondly on y, which
     * allows to draw a line smallest point -> biggest point, which divides
     * the points into two sets*/
    Point smallestP = ps[0], biggestP = ps[ps.size() - 1];
    up.push_back(smallestP), down.push_back(smallestP);

    for (int i = 1; i < ps.size(); ++i) {
        bool lastPoint = (i == ps.size() - 1);
        int currOrientation = orientation(ps[i], smallestP, biggestP);
        if (lastPoint || currOrientation == CLOCKWISE) {
            // Remove points which are not clockwise to the previous points connected to current point
            while (up.size() > 1 && orientation(up[up.size() - 1], up[up.size() - 2], ps[i]) != CLOCKWISE)
                up.pop_back();
            up.push_back(ps[i]);
        }
        if (lastPoint || currOrientation == COUNTER_CLOCKWISE) {
            // Remove points which are not counter clockwise to the previous points connected to current point
            while (down.size() > 1 &&
                   orientation(down[down.size() - 1], down[down.size() - 2], ps[i]) != COUNTER_CLOCKWISE)
                down.pop_back();
            down.push_back(ps[i]);
        }
    }

    // Result wanted counter clockwise
    for (auto &p : down) res.push_back(p);
    for (int i = (int) up.size() - 2; i > 0; --i) res.push_back(up[i]);
    if (res.size() > 1 && res[0] == res[res.size() - 1]) res.pop_back();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    pct a, b;
    while (cin >> n && n != 0) {
        vector<Point> poly(n);
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            poly[i] = {a, b};
        }
        vector<Point> hull;
        convexHull(poly, hull);
        cout << hull.size() << '\n';
        for (auto &p : hull) cout << p.x << " " << p.y << '\n';
        cout << flush;
    }
    cout << flush;
    return 0;
}