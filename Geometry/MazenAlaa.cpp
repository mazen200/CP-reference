#include <bits/stdc++.h>
using namespace std;

#define T long double
#define point complex<T>
#define Y imag()
#define X real()
/*
abs(): Returns the magnitude (absolute value) of the complex number.
arg(): Returns the argument (polar angle) of the complex number.
conj(): Returns the complex conjugate of the complex number
hypot(c,d): Takes two lengths and returns the hypotenus
polar(c,theta): Return a complex with these polar cords
*/
const double EPS = 1e-9;
const double PI = 3.14159265358979323846;
point mkvec(point a,point b){ 
    return b - a;
}

T cross(point a, point b) {
    return a.X*b.Y - a.Y*b.X;
}

T clamp(T val){
    return min((T)1.0 , max( (T)-1.0 , val));
}

T dot(point a, point b) {
    return (conj(a) * b).real();
}
// dotProduct = |A| * |B| * cos(Theta)
T calcAngle(point v1,point v2){
    return acos(clamp(dot(v1,v2)/abs(v1)/abs(v2)));
}
// Convert degrees to radians
T toRad(T deg) { 
    return deg * PI / 180.0;
}

// Rotation CCW (use negative angle for CW)
point rotate(point p, point pivot, T angle) {
    return (p - pivot) * polar((T)1.0, angle) + pivot;
}
point readPoint(){
    int x,y;
    cin>>x>>y;
    return point(x,y);
}

T angleCCW(point v1, point v2) {
    T a1 = atan2(v1.Y, v1.X);
    T a2 = atan2(v2.Y, v2.X);
    T angle = a2 - a1;
    
    if (angle < -EPS) angle += 2.0 * PI;
    return angle;
}

// 1 - left - ccw
int orientation (point a,point b,point c){
    point ab = mkvec(a,b);
    point ac = mkvec(a,c);
    T cr = cross(ab,ac);
    if(cr > 0) return 1;
    if(cr < 0) return -1;
    return 0;
    
}
 
//////////////////////////Lines/////////////////////

// normal equation => Ax + By + C = 0
// slop-intercept form => y = Mx + B
// Essential Core Functions
//double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
//double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
//double magnitude(Point a) { return hypot(a.x, a.y); }
//double dist(Point a, Point b) { return hypot(a.x - b.x, a.y - b.y); }

// ==========================================
// 2. LINE STRUCT (Ax + By + C = 0)
// ==========================================
struct Line {
    double a, b, c;
    double slope,yinter;
    Line(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {}

    // Build line from two points 
    void fromTwoPoints(point p1, point p2) {
        a = p1.Y - p2.Y;
        b = p2.X - p1.X;
        c = -a * p1.X - b * p1.Y;
    }

    // Build line from a point and a normal vector 
    void fromPointAndNormal(point p, point normal) {
        a = normal.X;
        b = normal.Y;
        c = -a * p.X - b * p.Y;

    }
    void slop_inter(){
        slope = a/b;
        yinter = c/b;
    }
};

// ==========================================
// 3. MULTI-FUNCTION UTILITIES
// ==========================================

// Perpendicular distance from Point to Line 
T distToLine(point p, Line l) {
    return abs(l.a * p.X + l.b * p.Y + l.c) / hypot(l.a, l.b);
}

// Line-Line Intersection 
// Returns false if lines are parallel/coincident, true if they intersect
bool intersect(Line l1, Line l2, point& out_intersection) {
    T zn = l1.a * l2.b - l2.a * l1.b;
    if (abs(zn) < EPS) return false; 
    
    out_intersection = point (- (l1.c * l2.b - l2.c * l1.b) / zn, -(l1.a * l2.c - l2.a * l1.c) / zn);

    return true;
}

// Check which side of a line a point is on 
// Returns > 0 for one side, < 0 for the other, 0 if it's perfectly on the line
T evaluateSide(point p, Line l) {
    return l.a * p.X + l.b * p.Y + l.c;
}

// Area of any simple polygon using Shoelace Formula 
T polygonArea(const vector<point>& vertices) {
    T area = 0;
    int n = vertices.size();
    for (int i = 0; i < n; i++) {
        area += cross(vertices[i], vertices[(i + 1) % n]);
    }
    return abs(area) / 2.0;
}
// T t = dot(mkvec(a,p),mkvec(a,b)) / dot(mkvec(a,b),mkvec(a,b));
// t < 0 -> less than a
// t > 1 -> more than b
// else the image is on the line
bool onSegment(point a, point b, point c) {
    return (c.X >= min(a.X, b.X) && c.X <= max(a.X, b.X) &&
            c.Y >= min(a.Y, b.Y) && c.Y <= max(a.Y, b.Y));
}
//////// CIRCLES////////////////
T circumcircleRadius(point p1, point p2, point p3) {
    T a = abs(p1 - p2);
    T b = abs(p2 - p3);
    T c = abs(p3 - p1);
    
    T area = polygonArea({p1, p2, p3});
    
    // Avoid division by zero if the points are collinear (on the same line)
    if (area < EPS) return -1.0; 
    
    return (a * b * c) / (4.0 * area);
} 

vector<point> intersectCircles(point c1, T r1, point c2, T r2) {
    T d = abs(c2 - c1);
    
    // Case 1: Circles are too far apart, or one is strictly inside the other
    if (d > r1 + r2 + EPS || d < abs(r1 - r2) - EPS || d < EPS) {
        return {}; // No intersection
    }
    
    // Case 2: They intersect or are tangent
    // Using Law of Cosines to find the angle from c1: r2^2 = r1^2 + d^2 - 2*r1*d*cos(a)
    T cos_a = (r1 * r1 + d * d - r2 * r2) / (2.0 * r1 * d);
    cos_a = clamp(cos_a); // Ensure value is between [-1, 1] before acos
    T angle = acos(cos_a);
    
    // Create a vector from c1 pointing exactly to c2, then scale its length to r1
    point v = (c2 - c1) / d * r1;
    
    point p1 = c1 + v * polar((T)1.0, angle);
    point p2 = c1 + v * polar((T)1.0, -angle);
    
    if (abs(p1 - p2) < EPS) 
        return {p1}; 

    return {p1, p2}; 
}
// Returns the center of the circle passing through 3 non-collinear points (Circumcenter)
point circumcenter(point a, point b, point c) {
    point ab = b - a; // Vector from A to B
    point ac = c - a; // Vector from A to C
    
    // Calculate the determinant (which is 2 * cross product)
    T D = 2.0 * cross(ab, ac);
    
    // If D is 0, it means the 3 points are collinear (on the same line),
    // so a circle cannot be drawn through them.
    if (abs(D) < EPS) {
        return point(1e18, 1e18); // Return a dummy/infinity point as an error flag
    }
    
    // In <complex>, std::norm(v) returns the SQUARED magnitude (x^2 + y^2)
    // Don't confuse it with abs() which returns the actual distance.
    T ab_sq = norm(ab); 
    T ac_sq = norm(ac);
    
    // Apply Cramer's rule to find the center relative to 'a'
    T cx = (ac.Y * ab_sq - ab.Y * ac_sq) / D;
    T cy = (ab.X * ac_sq - ac.X * ab_sq) / D;
    
    // Add 'a' back to shift the center to its true absolute position
    return a + point(cx, cy);
}
int main()
{

   ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    return 0;
}