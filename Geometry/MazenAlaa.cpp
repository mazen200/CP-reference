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
int pointInPolygon(vector<point>polygon,point p){
    int n = polygon.size();
    
    for(int i=0;i<n;i++){
            if( (orientation(polygon[i],polygon[(i+1)%n],p) == 0) && onSegment(polygon[i],polygon[(i+1)%n],p))
            {
                //"BOUNDARY\n";
                return 1;
            }
        }
 
        bool inside = false;
        for(int i=0;i<n;i++){
            point a = polygon[i],b = polygon[(i+1)%n];
            if(a.Y > b.Y)
                swap(a,b);
            if( p.Y >= a.Y && p.Y < b.Y )
            {
                if(orientation(a,b,p) == 1){
                    inside = !inside;
                }
            }
        
        }
       // cout << (inside? "INSIDE\n":"OUTSIDE\n");
        if(inside)
            return 2;
        return 0;
}

// line xy , ab
bool lineSegmentsIntersect(point a,point b,point x,point y){
    long long r1 = orientation(a,b,x);
    long long r2 = orientation(a,b,y);
    long long r3 = orientation(x,y,a);
    long long r4 = orientation(x,y,b);
    
    if(r1*r2 < 0 && r3*r4 < 0)
        return 1;
    else if( (r1 == 0 && onSegment(a,b,x)) || 
        (r2 == 0 && onSegment(a,b,y)) ||
        (r3 == 0 && onSegment(x,y,a)) ||
        (r4 == 0 && onSegment(x,y,b))
        ){
            return 1;
    }
    return 0;
}

int main()
{

   ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    return 0;
}