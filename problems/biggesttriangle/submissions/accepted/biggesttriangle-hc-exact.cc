#include <bits/stdc++.h>

using namespace std;

// Note: Applying operations to reduced fractions should yield a reduced answer
//       Make sure you reduce the fraction when you store it into the structure.
//  EXCEPT: 0 may be 0/x until reduce is called (then changed to 0/1)
typedef long long ll;
struct frac{  ll num,den; };

ll gcd(ll a, ll b)
{
  if (a < 0) return gcd(-a, b);
  if (b < 0) return gcd(a, -b);
  if (!b) return a;
  return gcd(b, a%b);
}

frac make_frac(ll n,ll d){ frac f; f.num = n,f.den = d; return f; }

frac reduce(frac a){
  if(a.num == 0) return make_frac(0,1); if(a.den < 0) { a.num *= -1; a.den *= -1; }
  ll g = gcd(a.num,a.den); return make_frac(a.num/g,a.den/g);
}
frac recip(frac a){ return reduce(make_frac(a.den,a.num)); }

frac operator+(frac a,frac b){
  ll g = gcd(a.den,b.den);
  return reduce(make_frac(a.num*(b.den/g) + b.num*(a.den/g), (a.den/g)*b.den));
}
frac operator-(frac a,frac b){ return a + make_frac(-b.num,b.den); }
frac operator*(frac a,frac b){
  ll g1 = gcd(a.num,b.den), g2 = gcd(a.den,b.num);
  return make_frac((a.num / g1) * (b.num / g2),(a.den / g2) * (b.den / g1));
}
frac operator/(frac a,frac b){ return a * recip(b); } // Watch division by 0

bool operator==(frac a,frac b){
  a=reduce(a); b=reduce(b);
  return a.num==b.num && a.den==b.den;
}

double to_double(frac a)
{
  return (double) a.num/a.den;
}

// Choose one. First one may overflow. Second one has rounding errors.
bool operator<(frac a,frac b){ return (a.num*b.den) < (b.num*a.den); }

//------------------------------------------------------------------------------
// 2D Integer geometry starts here

typedef long long ll;
bool dEqual(ll x, ll y) { return x == y; }  // replaces dEqual from double code
const ll EPS = 0;                           // replaces EPS from double code
struct Point {
  ll x, y;
  // safe ranges fro x and y:
  // SR1 : -10^18<=x,y<=10^18,  SR2 : -10^9<=x,y<=10^9
  // SR3 : -10^6<=x,y<=10^6,    SR4 : -3*10^4<=x,y<=3*10^4

  // operator== and operator<: use double geometry code
  bool operator==(const Point &p) const { return dEqual(x, p.x) && dEqual(y, p.y); }
  bool operator<(const Point &p) const { return y < p.y || (y == p.y && x < p.x); }

};

// +, -, inv: SR1
//  *, cross: SR2

Point operator-(Point p,Point q){ p.x -= q.x; p.y -= q.y; return p; }
Point operator+(Point p,Point q){ p.x += q.x; p.y += q.y; return p; }
Point operator*(double r,Point p){ p.x *= r; p.y *= r; return p; }
double operator*(Point p,Point q){ return p.x*q.x + p.y*q.y; }
double cross(Point p,Point q){ return p.x*q.y - q.x*p.y; }
Point inv(Point p){ Point q = {-p.y,p.x}; return q; }
double len(Point p){ return sqrt(p*p); }

ll len2(const Point &p){ return p*p; } // len2=len*len // SR2

//------------------------------------------------------------------------------
// Colinearity test // SR2
// Orientation test // SR2
// Signed Area of Polygon (*2) // SR2 divided by n, don't divide by 2
//------------------------------------------------------------------------------
// Convex hull: 
//   To remove colinear pts: Change ("<0" and ">0") to ("<=0" and ">=0") // SR2
//------------------------------------------------------------------------------
// Point in Polygon Test // SR2

//------------------------------------------------------------------------------
// Squared distance from "c" to the infinite line defined by "a" and "b"
frac dist_line2(Point a, Point b, Point c) // SR4
{ ll cr=cross(b-a,a-c);return make_frac(cr*cr,len2(b-a)); }

//------------------------------------------------------------------------------
// Intersection of lines (line segment or infinite line) // SR3
//   (1 == 1 intersection pt, 0 == no intersection pts, -1 == infinitely many
int intersect_line(Point a, Point b, Point c, Point d, 
		   frac &px, frac &py,bool segment) {
  ll num1 = cross(d-c,a-c), num2 = cross(b-a,a-c),denom = cross(b-a,d-c);
  if (denom!=0) {
    if(!segment || (denom<0 && num1<=0 && num1>=denom && num2<=0 && num2>=denom) ||
       (denom>0 && num1>=0 && num1<=denom && num2>=0 && num2<=denom)) {
      px=make_frac(a.x,1)+make_frac(num1,denom)*make_frac((b-a).x,1);
      py=make_frac(a.y,1)+make_frac(num1,denom)*make_frac((b-a).y,1); return 1;
    } else return 0;
  }
  if(!segment) return (num1==0) ? -1 : 0; // For infinite lines, this is the end
  if (num1!=0) return 0;
  if(b < a) swap(a,b); if(d < c) swap(c,d);
  if (a.x == b.x) {
    if (b.y == c.y) { px=make_frac(b.x,1); py=make_frac(b.y,1); return 1; }
    if (a.y == d.y) { px=make_frac(a.x,1); py=make_frac(a.y,1); return 1; }
    return (b.y < c.y || d.y < a.y) ? 0 : -1;
  } else if (b.x == c.x) { px=make_frac(b.x,1); py=make_frac(b.y,1); return 1; }
  else if (a.x == d.x) { px=make_frac(a.x,1); py=make_frac(a.y,1); return 1; }
  else if (b.x < c.x || d.x < a.x) return 0;
  return -1;
}

const int MAX_N = 200;
int n;
Point p1[MAX_N], p2[MAX_N];

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> p1[i].x >> p1[i].y >> p2[i].x >> p2[i].y;
  }
  double best = -1;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      for (int k = j+1; k < n; k++) {
	Point p[3];
	frac p0x, p0y, p1x, p1y, p2x, p2y;
	int res1 = intersect_line(p1[i], p2[i], p1[j], p2[j], p0x, p0y, false);
	int res2 = intersect_line(p1[i], p2[i], p1[k], p2[k], p1x, p1y, false);
	int res3 = intersect_line(p1[j], p2[j], p1[k], p2[k], p2x, p2y, false);
	if (res1 == 1 && res2 == 1 && res3 == 1 &&
	    !(p0x == p1x && p0y == p1y) &&
	    !(p0x == p2x && p0y == p2y) &&
	    !(p1x == p2x && p1y == p2y)) {
	  double temp = hypot(to_double(p0x-p1x), to_double(p0y-p1y)) +
	    hypot(to_double(p0x-p2x), to_double(p0y-p2y)) +
	    hypot(to_double(p2x-p1x), to_double(p2y-p1y));
	  best = max(temp, best);
	}
      }
    }
  }
  if (best < 0) {
    cout << "no triangle" << endl;
  } else {
    cout << fixed << setprecision(10) << best << endl;
  }
  return 0;
}
