#include <cstdio>
#include <cmath>
#include <cstdlib>

inline double sqr(double a) { return a * a; }
inline double SQRT(double a) { return a < 0 ? 0 : sqrt(a); }

struct Point{
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
	Point operator *(const double &a) const {
		return Point(a * x, a * y, a * z);
	}
	Point operator +(const Point &t) const {
		return Point(x + t.x, y + t.y, z + t.z);
	}
	Point operator -(const Point &t) const {
		return Point(x - t.x, y - t.y, z - t.z);
	}
	Point operator /(double t) const {
		return Point(x / t, y / t, z / t);
	}
	double dot(const Point &t) {
		return x * t.x + y * t.y + z * t.z;
	}
	double norm() {
		return this->dot(*this);
	}
	double abs() {
		return SQRT(this->norm());
	}
	Point unit() {
		return *this / abs();
	}
	Point cross(const Point &t) {
		Point ret;
		ret.x = y * t.z - z * t.y;
		ret.y = z * t.x - x * t.z;
		ret.z = x * t.y - y * t.x;
		return ret;
	}
	void read() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	void write() {
		printf("%.10f %.10f %.10f", x, y, z);
	}
};

double mix(Point a, Point b, Point c) {
	return a.dot(b.cross(c));
}

const double pi = acos(-1.);
double upperarm, forearm, angle, len;
Point a, b, c;

double getangle(double a, double b, double c, double &height) {
	double p = (a + b + c) / 2;
	double area = SQRT(p * (p - a) * (p - b) * (p - c)) * 2;
	height = area / c;
	return acos((sqr(a) + sqr(b) - sqr(c)) / 2 / a / b);
}

int main() {
	scanf("%lf%lf", &upperarm, &forearm);
	a = Point(0, 0, 0);
	b.read(), c.read();
	Point p = b + (c - b).unit() * (a - b).dot(c - b) / (c - b).abs();
	if (p.norm() > sqr(upperarm + forearm) + 1e-7 || p.norm() - sqr(upperarm) - sqr(forearm) < -1e-7) {
		puts("No solution.");
		return 0;
	}
	angle = getangle(upperarm, forearm, p.abs(), len);
	Point q = (a - b).cross(c - b).unit() * len;
	double x = SQRT(sqr(upperarm) - sqr(len));
	Point ans = p.unit() * x + q;
	ans.write();
	printf(" %.16f\n", angle);
	return 0;
}
