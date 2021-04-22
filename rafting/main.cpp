/*
 * @AUTHOR: Hugo Cedervall
 * @DATE: 2021-04-22
 * @PROBLEM: rafting
*/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

double INF = 10e9;

double distance(pair<double, double> p1, pair<double, double> p2) {
    double x = p1.first - p2.first, y = p1.second - p2.second;
    return sqrt(x * x + y * y);
}

// Shortest distance between point b and any point on line between point a and point b
double distanceLinePoint(pair<double, double> a, pair<double, double> b, pair<double, double> p) {
    double len = distance(a, b);
    // a and b are same
    if (len == 0) return distance(a, p);

    // How far on the line between point a and point b that point p is projected
    double u =
            ((p.first - a.first) * (b.first - a.first) + ((p.second - a.second) * (b.second - a.second))) / (len * len);
    pair<double, double> projection = {a.first + u * (b.first - a.first), a.second + u * (b.second - a.second)};

    double pDistToLine = distance(projection, p);
    // If point is on the line
    if (pDistToLine < 1e-8) pDistToLine = INF;
    // If projection lies outside the line
    if (distance(projection, a) + distance(projection, b) - distance(a, b) > 1e-8) pDistToLine = INF;
    // Distance to projection on line if valid, else the min distance to any of starting points
    return min(pDistToLine, min(distance(a, p), distance(b, p)));
}


struct Poly {
    vector<pair<double, double>> points;

    Poly() {
        this->points = vector<pair<double, double>>();
    }

    void addPoint(double a, double b) {
        this->points.emplace_back(a, b);
    }
};

double solution(Poly &inner, Poly &outer) {
    double minDist = INF;
    for (int i = 0; i < outer.points.size(); ++i)
        for (auto &point : inner.points)
            minDist = min(distanceLinePoint(outer.points[i],
                                            outer.points[(i + 1) < outer.points.size() ? i + 1 : 0],
                                            point), minDist);
    return minDist / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int ni, no;
    double a, b;
    cin >> n;
    while (n--) {
        Poly inner, outer;
        cin >> ni;
        for (int i = 0; i < ni; ++i) {
            cin >> a >> b;
            inner.addPoint(a, b);
        }
        cin >> no;
        for (int i = 0; i < no; ++i) {
            cin >> a >> b;
            outer.addPoint(a, b);
        }
        cout << setprecision(8) << solution(inner, outer) << '\n';
    }
    cout << flush;

    return 0;
}