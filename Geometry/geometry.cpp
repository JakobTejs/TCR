#include <iostream>
#include <cstdio>
#include <complex>
#include <vector>
#include <algorithm>

using namespace std;

typedef complex<double> com;

com circumcenter(com a, com b, com c) {
    return (a * conj(a) * (c-b) + b * conj(b) * (a-c) + c * conj(c) * (b-a))/
           ( conj(a) * (c-b) + conj(b) * (a-c) + conj(c) * (b-a));
}

com centroid(com a, com b, com c) {
    return (a+b+c)/3.0;
}

com orthocenter(com a, com b, com c) {
    return a+b+c - 2.0 * circumcenter(a,b,c); //2O + H = 3G
}

double area(com a, com b, com c) {
    return abs(0.5 * imag((a-b)*conj(c-b)));
}

double turn(com a, com b, com c) {
    return imag((a-b)*conj(c-b));
}

int turn2(com a, com b, com c) {
    double x = imag((a-b)*conj(c-b));
    return x < 0 ? -1 : x > 0;
}

double area(com p[], int n) {
    double sum = 0;
    for(int i=1;i+1<n;i++) {
        sum += turn(p[0],p[i],p[i+1]);
    }
    return abs(0.5 * sum);
}

com omega(com x, com y) {
    return conj(x-y)/(x-y);
}

com rho(com x, com y) {
    return (conj(x) * y - x * conj(y))/(x-y);
}

com intersection(com a, com b, com c, com d) {
    return (rho(a,b) - rho(c,d))/(omega(a,b) - omega(c,d));
}

bool straddles(com a, com b, com c, com d) {
    return turn2(c, d, a) * turn2(c, d, b) == -1 &&
           turn2(a, b, c) * turn2(a, b, d) == -1;
}

bool straddlesInclEndpoints(com a, com b, com c, com d) {
    return turn2(c, d, a) * turn2(c, d, b) <= 0 &&
           turn2(a, b, c) * turn2(a, b, d) <= 0;
}

com proj(com a, com b, com p) {
    return 0.5 * conj(p * omega(a,b) + conj(p) - rho(a,b));
}

bool hasLineCirleIntersection(com a, com b, com c, double r) {
    com p = proj(a, b, c);
    double dist = abs(p-c);
    return dist <= r;
}

pair<com, com> lineCircleIntersection(com a, com b, com c, double r) {
    com p = proj(a, b, c);
    double dist = abs(p-c);
    if(dist > r) return make_pair(0, 0);
    com ex = sqrt(pow(r/dist, 2) - 1) * (p-c) * com(0,1);
    return make_pair( p + ex, p - ex);
}

com radicalAxis(com c1, double r1, com c2, double r2) {
    double d = abs(c1-c2);
    return 0.5 * (1 + (r1*r1 - r2*r2)/(d*d)) * (c2-c1) + c1;
}

bool hasCircleCircleIntersection(com c1, double r1, com c2, double r2) {
    return abs(r1 - r2) <= abs(c1-c2) && abs(c1-c2) <= r1+r2;
}

pair<com, com> circleCircleIntersection(com c1, double r1, com c2, double r2) {
    com p = radicalAxis(c1, r1, c2, r2);
    double dist = abs(p-c1);
    if(dist > r1) return make_pair(0, 0);
    com ex = sqrt(pow(r1/dist, 2) - 1) * (p-c1) * com(0,1);
    return make_pair(p + ex, p - ex);
}

bool lexCmp(com a, com b) {
    return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
}

void convexHull (vector<com>& a) {
    if (a.size () == 1) return;
    sort(a.begin(), a.end(), lexCmp);
    com p1 = a[0], p2 = a.back();
    vector<com> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (size_t i = 1; i < a.size(); ++i) {
        if(i == a.size()-1 || turn(p1, a[i], p2) < 0) {
            while(up.size() >= 2 && turn(up[up.size()-2], up[up.size ()-1], a[i]) >= 0) {
                up.pop_back();
            }
            up.push_back(a[i]);
        }
        if (i == a.size() -1 || turn(p1, a[i], p2) > 0) {
            while (down.size() >= 2 && turn(down[down.size () -2], down[down.size () -1], a[i]) <= 0)
                down.pop_back ();
            down.push_back (a [i]);
        }
    }
    a.clear();
    for (size_t i = 0; i <up.size(); ++i)
        a.push_back(up[i]);
    for (size_t i = down.size()-2; i > 0; --i)
        a.push_back(down[i]);
}

int main() {
    return 0;
}