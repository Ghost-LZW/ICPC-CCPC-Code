/*************************************************************************
    > File Name: solve.cpp
    > Author: XeroxAuto
    > Mail: lanzongwei@gmail.com
    > Created Time: 2020-07-18 12:42:05
 ************************************************************************/

#define GOODOJ
#define SYNC 0

#ifdef GOODOJ
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
#include <chrono>
#include <random>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
#else
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <limits>
#include <cassert>
#include <sstream>
#include <iterator>
#include <functional>
#endif
using namespace std;

#define endl '\n'
#define fep(i,b,e) for(int i=(b);i<(e);++i)
#define rep(i,x) for(int i=0;i<(x);++i)
#define rap(i,x) for(auto& i : (x))
#define seg(t) (t).begin(), (t).end()
#define ep emplace_back
#define mkp make_pair
#define qxx(i,x) for(int i = head[x]; ~i; i = node[i].nex)
#define F first
#define S second
#define lowbit(x) ((-(x))&(x))
#define RE register
#define getchar() getchar_unlocked()
#ifdef DEBUG
void err(istream_iterator<string>){}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << ' ';
	err(++it, args...);
}
#define debug(args...) {string _s=#args;replace(seg(_s),',',' ');\
cerr<<"DEBUG:";istringstream it(_s);\
err(istream_iterator<string>(it), args);cerr<<endl;}
#else
#define debug(...)
#endif

template<typename T> inline bool cmax(T& a,const T& b) {return a<b?a=b,1:0;}
template<typename T> inline bool cmin(T& a,const T& b) {return a>b?a=b,1:0;}

#ifdef GOODOJ
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
typedef __gnu_pbds::priority_queue<int> pq;
#endif
typedef std::string str;
typedef long long ll;
typedef double db;
typedef pair<int, int> pa;

namespace Geo{
	typedef double db;
	const db eps = 1e-9, PI = acos(-1), inf = numeric_limits<db>::max();
	inline int sign(db a) {return a < -eps ? -1 : a > eps;}
	inline int cmp(db a, db b) {return sign(a - b);}
	inline bool inmid(db k, db a, db b) {return sign(a - k) * sign(b - k) <= 0;}
	struct Point{
		db x, y;
		Point(db _x, db _y) : x(_x), y(_y) {}
		Point() = default;
		Point operator + (const Point& b) const{return {x + b.x, y + b.y};}
		Point operator - (const Point& b) const{return {x - b.x, y - b.y};}
		Point operator * (const db& b) const{return {x * b, y * b};}
		Point operator / (const db& b) const{return {x / b, y / b};}
		bool operator == (const Point& b) const{return cmp(x,b.x)==0&&cmp(y,b.y)==0;}
		bool operator != (const Point& b) const{return not (*this == b);}
		bool operator < (const Point& b) const {
			int c = cmp(x, b.x);
			if (c) return c == -1;
			return cmp(y, b.y) == -1;
		}
		bool operator > (const Point& b) const {return b < *this;}
		Point right(const db& len) {return Point(x + len, y);}
		Point up(const db& len) {return Point(x, y + len);}
		db length() const {return hypot(x, y);}
		db length2() const {return x*x+y*y;}
		Point unit() const {return *this / this->length();}
		void print() const {printf("%.11f %.11f\n", x, y);}
		void scan() {scanf("%lf%lf", &x, &y);}
		db dis(Point b) const {return (*this - b).length();}
		db dis2(Point b) const {return (*this - b).length2();}
		Point roate(db ac) const {return Point(x * cos(ac) - y * sin(ac), y * cos(ac) + x * sin(ac));}
		Point roate90() const {return {-y, x};}
	};
	typedef Point Vector;
	typedef std::vector<Point> Polygon;
	struct Line {
		Point u, v;
		Line(const Point& _a, const Point& _b) : u(_a), v(_b) {}
		Line() = default;
		Vector getVec() const {return Vector(v - u);}
		Line go(Vector t) {return {u + t, v + t};}
		bool isPoint() const {return u == v;}
		db length() const {return u.dis(v);}
		void print() const {u.print(), v.print();}
		void scan() {u.scan(), v.scan();}
	};
	inline db dot(Point ab, Point ac) {return ab.x*ac.x+ab.y*ac.y;} //|ab|*|ac|*cosθ
	inline int dotOp(Point c, Point a={0,0}, Point b={0,1e5}) {return sign(dot(b-a,c-a));} //+ : 1,4 - : 2,3
	inline db cross(Point ab, Point ac) {return ab.x*ac.y-ab.y*ac.x;} //|ab|*|ac|*sinθ
	inline int crossOp(Point c, Point a={0,0}, Point b={0,1e5}) {return sign(cross(b-a,c-a));} //+ : 1,2 -: 3,4
	inline int Op(Point c, Point a={0,0}, Point b={0,1e5}) { // 相对象限
		int lr = dotOp(c,a,b), ud = crossOp(c,a,b);
		if(lr==0 or ud == 0) return 0;
		return lr + ud == 2 ? 1 : (lr + ud == -2 ? 3 : (lr == -1 ? 2 : 1));
	}
	inline int Quadrant(const Point& a) { // 象限
		if (a.x > 0 and a.y >= 0) return 1;
		if (a.x <= 0 and a.y > 0) return 2;
		if (a.x < 0 and a.y <= 0) return 3;
		if (a.x >= 0 and a.y < 0) return 4;
		return 0;
	}
	bool parallel(const Line& a, const Line& b) {return sign(cross(a.getVec(), b.getVec())) == 0;}
	bool sameDir(const Line& a, const Line& b) {
		return parallel(a, b) and sign(dot(a.getVec(), b.getVec())) == 1;
	}
	bool compairAng(const Point& a, const Point& b) {
		int p1 = Quadrant(a), p2 = Quadrant(b);
		return p1 < p2 or (p1 == p2 and sign(cross(a, b)) > 0);
	}
	bool operator < (const Line& a, const Line& b) {
		if (sameDir(a, b)) return crossOp(b.u, a.u, a.v) < 0;
		else return compairAng(a.getVec(), b.getVec());
	}
	inline db disPtoL(Point c, Line a) { // 点到直线距离
		return fabs(cross(a.v - a.u, c - a.u)) / a.length();
	}
	inline Point nearestPoint(Point c, Line ab) { // 线到点最近点
		db t = dot(c - ab.u, ab.getVec()) / dot(ab.getVec(), ab.getVec());
		if(0 <= t and t <= 1) return ab.u + (ab.v - ab.u) * t;
		return c.dis(ab.u) > c.dis(ab.v) ? ab.v : ab.u;
	}
	inline db disPtol(Point c, Line a) {return c.dis(nearestPoint(c, a)); }// 点到线段的距离
	inline Point pjPoint(Point c, Point a, Point b) { // 投影点
		return a + (b - a).unit() * dot(c - a, b - a) / (b - a).length();
	}
	inline Point symPoint(Point c, Point a, Point b) { // 对称点
		return pjPoint(c, a, b) * 2.0 - c;
	}
	struct Circle {
		Point o; db r; void scan() {o.scan(); scanf("%lf", &r);}
		Circle(Point _t, db _r) : o(_t), r(_r) {}
		Circle() = default;
		bool operator == (const Circle b) const {return o == b.o and cmp(r, b.r) == 0;}
		db area() {return PI * r * r;}
		int contain(Point t) { // 1 圆外 0 圆上 -1 圆内
			return cmp(o.dis(t), r);
		}
		bool intersect(const Circle b) {
			return cmp(o.dis(b.o), r + b.r) != 1 and cmp(o.dis(b.o), fabs(r - b.r)) != -1;
		}
		int intersect(Line t) { // 0 相切 1 相离 -1 相交
			return cmp(disPtoL(o, t), r);
		}
		int intersect_seg(Line t) {
			Point k = nearestPoint(o, t);
			return cmp(o.dis(k), r);
		}
	};
	db rad(Point a, Point b) {return atan2l(cross(a, b), dot(a, b));}
	inline bool ckpar(Point a, Point b, Point c, Point d) { // 检查直线平行
		return cmp(cross(c-a,d-a), cross(c-b,d-b)) == 0;
	}
	inline bool ckpar(Line a, Line b) {return ckpar(a.u, a.v, b.u, b.v);}
	inline Point getInsec(Point a, Point b, Point c, Point d) { // 获取交点
		db w1 = cross(a-c,d-c), w2 = cross(d-c,b-c);
		return (a * w2 + b * w1) / (w1 + w2);
	}
	inline Point getInsec(Line a, Line b) {return getInsec(a.u, a.v, b.u, b.v);}
	inline bool inseg(Point c, Point a, Point b) { //点在线段a, b上
		if (c == a or c == b) return true;
		return sign(cross(b - a, c - a)) == 0 and sign(dot(a - c, b - c)) == -1;
	}
	inline bool inseg(Point c, Line p) {
		return inseg(c, p.u, p.v);
	}
	inline bool intersect(db l1, db r1, db l2, db r2) { // 排斥 [l1,r1] [l2,r2]有交集
		if (l1 > r1) swap(l1, r1); if (l2 > r2) swap(l2, r2);
		return cmp(r2, l1) != -1 and cmp(r1, l2) != -1;
	}
	inline int spanLine(Point a, Point b, Point c, Point d) { // ab跨立cd直线 跨立实验<0成功=0在直线上
		return sign(cross(a - c, d - c)) * sign(cross(b - c, d - c));
	}
	inline int spanLine(Line a, Line b) {
		return spanLine(a.u, a.v, b.u, b.v);
	}
	inline bool checkSS(Point a, Point b, Point c, Point d) { // 线段相交 非规范
		return intersect(a.x, b.x, c.x, d.x) and intersect(a.y, b.y, c.y, d.y) and
			spanLine(a, b, c, d) <= 0 and spanLine(c, d, a, b) <= 0;
	}
	inline bool checkSSsp(Point a, Point b, Point c, Point d) { // 线段相交 规范
		return spanLine(a, b, c, d) < 0 and spanLine(c, d, a, b) < 0;
	}
	inline bool checkSS(Line a, Line b, bool Notsp=true) {
		if(Notsp)return checkSS(a.u, a.v, b.u, b.v);
		else return checkSSsp(a.u, a.v, b.u, b.v);
	}
	inline db area(const Polygon& v) { // area of Polygon 逆时针
		db ans = 0; int len = v.size(); if (len < 3) return 0;
		for(int i = 0; i < len; i++) ans += cross(v[i], v[(i+1)%len]);
		return ans / 2;
	}
	inline int contains(const Polygon& ps, Point q) { // 内部1 外部-1 边上0 点于多边形
		int n = ps.size();
		int res = -1;
		for(int i = 0; i < n; i++) {
			Vector a = ps[i] - q, b = ps[(i + 1) % n] - q;
			if (cmp(a.y, b.y) == 1)	swap(a, b);
			if (sign(a.y) != 1 and sign(b.y) == 1 and sign(cross(a, b)) == 1)
				res = -res;
			if (sign(cross(a, b)) == 0 and sign(dot(a, b)) != 1) return 0;
		}

		return res;
	}
	bool cmpAtan(Point a, Point b) { // 极角排序
		if(atan2(a.y, a.x) != atan2(b.y, b.x))
			return atan2(a.y, a.x) < atan2(b.y, b.x);
		return a.x < b.x;
	}
	struct CMP {
		Point o;
		CMP(Point t=Point(0, 0)) : o(t) {};
		bool operator () (const Point& a, const Point& b) const {
			int p = crossOp(b, o, a); if(p == 0) return a.x < b.x;
			return p == 1;
		}
	};
	bool isConvex(const Polygon& ps) { // 1 凸多边形
		int s[3] = {1, 1, 1}; int n = ps.size();
		for(int i = 0; i < n and s[0] | s[2]; ++i)
			s[sign(cross(ps[(i + 1) % n] - ps[i], ps[(i + 2) % n] - ps[i])) + 1] = 0;
		return s[0] | s[2];
	}
	inline vector<Point> getCLInsec(Circle a, Line b) { //圆和直线交点
		int aim = a.intersect(b);
		if(aim == 1) return {};
		if(aim == 0) return {pjPoint(a.o, b.u, b.v)};
		Point t = pjPoint(a.o, b.u, b.v);
		db temp = a.o.dis(t);
		db len = a.r * a.r - temp * temp; len = sqrt(len);
		return {t - b.getVec().unit() * len, t + b.getVec().unit() * len};
	}
	inline int numOfCC(Circle a, Circle b) { // 外离 外切 相交 内切 内含
		if(a == b) return 0;
		if (cmp(a.r, b.r) == -1) swap(a, b);
		db dis = a.o.dis(b.o); int t1 = cmp(dis, a.r + b.r), t2 = cmp(dis, a.r - b.r);
		if (t1 > 0) return 4; else if (t1 == 0) return 3; else if (t2 > 0) return 2;
		else if (t2 == 0) return 1; else return 0;
	}
	inline vector<Point> getCCInsec(Circle a, Circle b) {
		if (cmp(a.r, b.r) == -1) swap(a, b);
		int p = numOfCC(a, b); if (p == 0 || p == 4) return {};
		if (p != 2) return {a.o + (b.o - a.o).unit() * a.r};
		db len = a.o.dis2(b.o), COSA = (len + a.r * a.r - b.r * b.r) / (2.0 * sqrt(len) * a.r);
		db dia = a.r * COSA, aid = sqrt(a.r * a.r - dia * dia);
		Vector k = (b.o - a.o).unit(), m = a.o + k * dia, del = k.roate90() * aid;
		return {m - del, m + del};
	}
	inline vector<Line> TangentCP(Circle c, Point a) {
		if (c.contain(a) == -1) return {};
		db len = a.dis(c.o), b = c.r * c.r / len, dlen = sqrt(c.r * c.r - b * b);
		Vector k = (a - c.o).unit(), m = c.o + k * b, del = k.roate90() * dlen;
		if (cmp(dlen, 0) == 0) return {Line(a, a + k.roate90() * len)};
		return {{a, m - del}, {a, m + del}};
	}
	inline vector<Line> TangentCCOut(Circle a, Circle b) {
		int p = numOfCC(a, b); if (p == 0) return {};
		if (p == 1) {Point c = getCCInsec(a, b)[0]; return {Line(c, c + (b.o - a.o).roate90())};}
		if (cmp(a.r, b.r) == 0) {
			Vector del = (b.o - a.o).unit().roate90();
			return {{a.o - del * a.r, b.o - del * b.r}, {a.o + del * a.r, b.o + del * b.r}};
		} else {
			Point t = (b.o * a.r - a.o * b.r) / (a.r - b.r);
			vector<Line> A = TangentCP(a, t), B = TangentCP(b, t);
			for(int i = 0; i < A.size(); i++) A[i] = Line(A[i].v, B[i].v);
			return A;
		}
	}
	inline vector<Line> TangentCCIn(Circle a, Circle b) {
		int p = numOfCC(a, b); if (p <= 2) return {};
		if (p == 3) {Point c = getCCInsec(a, b)[0]; return {Line(c, c + (b.o - a.o).roate90())};}
		Point t = (a.o * b.r + b.o * a.r) / (b.r + a.r);
		vector<Line> A = TangentCP(a, t), B = TangentCP(b, t);
		for(int i = 0; i < A.size(); i++) A[i] = Line(A[i].v, B[i].v);
		return A;
	}
	inline vector<Line> TangentCC(Circle a, Circle b) {
		bool flag = cmp(a.r, b.r); if (flag == -1) swap(a, b);
		vector<Line> A = TangentCCOut(a, b), B = TangentCCIn(a, b);
		A.insert(A.end(), seg(B));
		if (flag) for(auto& i : A) swap(i.u, i.v);
		return A;
	}
	inline db area(Circle c, Point a, Point b) { // area of circle c and tangle a b c.o ab逆正
		a = a - c.o, b = b - c.o; c.o = Point(0, 0);
		if (sign(cross(a, b)) == 0) return 0;
		if (c.intersect_seg(Line(a, b)) == 0) return c.r * c.r * rad(a, b) * 0.5;
		vector<Point> A = getCLInsec(c, Line(a, b));
		int p1 = c.contain(a), p2 = c.contain(b);
		if (p1 <= 0) {
			if (p2 <= 0) return cross(a, b) * 0.5;
			return cross(a, A[1]) * 0.5 + c.r * c.r * rad(A[1], b) * 0.5;
		} else if (p2 <= 0) return cross(A[0], b) * 0.5 + c.r * c.r * rad(a, A[0]) * 0.5;
		else {
			if (c.intersect_seg(Line(a, b)) != -1) return c.r * c.r * rad(a, b) * 0.5;
			return cross(A[0], A[1]) * 0.5 + c.r * c.r * (rad(a, A[0]) + rad(A[1], b)) * 0.5;
		}
	}
	inline db areaN(Circle c, vector<Point> b) { // c 交 b
		int n = b.size(); if (n < 3) return 0; db ans = 0;
		for(int i = 0; i < n; i++)
			ans += area(c, b[i], b[(i + 1) % n]);
		return ans;
	}
	inline db areaN(Circle a, Circle b) {
		int p = numOfCC(a, b);
		if (p > 2) return 0;
		if (p == 2) {
			db d = a.o.dis(b.o);
			db p1 = acos((d * d + a.r * a.r - b.r * b.r) / (2 * d * a.r)),
			   p2 = acos((d * d + b.r * b.r - a.r * a.r) / (2 * d * b.r));
			return p1 * a.r * a.r + p2 * b.r * b.r - d * a.r * sin(p1);
		} else {
			if (cmp(a.r, b.r) != -1) return b.area();
			else return a.area();
		}
	}
	inline db areaU(Circle a, Circle b) {return a.area() + b.area() - areaN(a, b);}
	bool checkPos(Line a, Line b, Line c) {return crossOp(getInsec(a, b), c.u, c.v) >= 0;}
	inline Polygon HalfPlane(vector<Line> A) { // n log(n)
		sort(seg(A)); deque<Line> q; int n = A.size();
		for (int i = 0; i < n; i++) {
			if (i and sameDir(A[i], A[i - 1])) continue;
			while (q.size() > 1 and !checkPos(q.back(), q[q.size() - 2], A[i])) q.pop_back();
			while (q.size() > 1 and !checkPos(q.front(), q[1], A[i])) q.pop_front();
			q.emplace_back(A[i]);
		}
		while (q.size() > 2 and !checkPos(q.back(), q[q.size() - 2], q.front())) q.pop_back();
		while (q.size() > 2 and !checkPos(q.front(), q[1], q.back())) q.pop_front();
		Polygon ans; n = q.size(); if (n < 2) return ans;
		for (int i = 0; i < n; i++)
			ans.emplace_back(getInsec(q[i], q[(i + 1) % n]));
		return ans;
	}
	inline Circle getcircle(Point a, Point b, Point c) {
		db a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) * 0.5;
		db a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) * 0.5;
		db d = a1 * b2 - b1 * a2;
		Point o(a.x + (c1 * b2 - b1 * c2) / d, a.y + (a1 * c2 - c1 * a2) / d);
		return {o, a.dis(o)};
	}
	inline Circle getNcircle(Point A, Point B, Point C) {
		db t1 = B.x - C.x, t2 = B.y - C.y, t3 = C.x - A.x, t4 = C.y - A.y,
		t5 = B.x - A.x, t6 = B.y - A.y;
		db aa = t1 * t1 + t2 * t2, bb = t3 * t3 + t4 * t4, cc = t5 * t5 + t6 * t6;
		db a = sqrt(aa), b = sqrt(bb), c = sqrt(cc);
		db a1 = b * t1 + a * t3, b1 = b * t2 + a * t4, c1 = (a * bb - 2 * b * aa - a * cc + a * aa) * 0.5;
		db a2 = b * t5 - c * t3, b2 = b * t6 - c * t4, c2 = (c * bb - 2 * b * cc - c * aa + c * cc) * 0.5;
		db d = a1 * b2 - b1 * a2;
		Point o(B.x + (c1 * b2 - b1 * c2) / d, B.y + (a1 * c2 - c1 * a2) / d);
		return {o, disPtoL(o, Line(A, B))};
	}
	struct Inversion {
		Point o; db R;
		Inversion(Point t={0,0}, db _r=10) : o(t), R(_r) {}
		Circle inversion(const Circle& a) { // 反演不过o点的圆
			db r2 = a.r * R * R / (o.dis2(a.o) - a.r * a.r);
			db ob = o.dis(a.o) * r2 / a.r;
			return {o + (a.o - o).unit() * ob, r2};
		}
		Line inversionCL(const Circle& a) { // 反演过o圆
			Point t = this->inversion(a.o + (a.o - o).unit() * a.r);
			return {t, t + (a.o - o).roate90()};
		}
		Point inversion(const Point& a) { // 反演点
			db ob = R * R / o.dis(a);
			return o + (a - o).unit() * ob;
		}
		Circle inversion(const Line& a) { // 反演不过o点线
			Point c = pjPoint(o, a.u, a.v);
			c = this->inversion(c);
			db r = o.dis(c) / 2;
			return {o + (c - o) / 2, r};
		}
		bool checkL(const Line& a) { //true 过o点
			return sign(cross(a.u - o, a.v - o)) == 0;
		}
	};
	inline Polygon ConvexHull(vector<Point> A, int flag=1) { // 0 不严格 1 严格
		int n = A.size(); if(n <= 1) return A; Polygon ans(n*2); int now = -1;
		sort(seg(A));
		for (int i = 0; i < n; ans[++now] = A[i++])
			while (now > 0 and crossOp(ans[now], ans[now - 1], A[i]) < flag) --now;
		for (int i = n - 2, pre = now; i >= 0; ans[++now] = A[i--])
			while (now > pre and crossOp(ans[now], ans[now - 1], A[i]) < flag) --now;
		ans.resize(now); return ans;
	}
	inline db convexDimater(Polygon v) {
		int now = 0, n = v.size(); db ans = 0;
		for(int i = 0; i < n; i++) {
			now = max(now, i);
			for (;;) {
				db k1 = v[i].dis(v[now % n]), k2 = v[i].dis(v[(now + 1) % n]);
				ans = max(k1, k2); if (k2 > k1) ++now; else break;
			}
		}
		return ans;
	}
	inline Polygon convexCut(Polygon v, Line a) {
		int n = v.size(); Polygon ans;
		for(int i = 0; i < n; i++) {
			int k1 = crossOp(v[i], a.u, a.v), k2 = crossOp(v[(i + 1) % n], a.u, a.v);
			if (k1 >= 0) ans.emplace_back(v[i]);
			if (k1 * k2 < 0) ans.emplace_back(getInsec(a, Line(v[i], v[(i + 1) % n])));
		}
		return ans;
	}
	/*---------------3D-------------------*/
	struct Point3{
		db x, y, z;
		Point3(db _x, db _y, db _z) : x(_x), y(_y), z(_z) {}
		Point3() = default;
		Point3 operator + (const Point3& b) const{return {x + b.x, y + b.y, z + b.z};}
		Point3 operator - (const Point3& b) const{return {x - b.x, y - b.y, z - b.z};}
		Point3 operator * (const db& b) const{return {x * b, y * b, z * b};}
		Point3 operator / (const db& b) const{return {x / b, y / b, z / b};}
		db length2() const {return x * x + y * y + z * z;}
    	db length() const {return sqrt(x * x + y * y + z * z);}
		void scan() {scanf("%lf%lf%lf", &x, &y, &z);}
		Point3 unit() const {return *this / this->length();}
	};
	db dot(Point3 a, Point3 b) {return a.x * b.x + a.y * b.y + a.z * b.z;}
	Point3 cross(Point3 a, Point3 b) {return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};}
	Point3 pjPoint(Point3 p, Point3 a, Point3 b, Point3 c) {
		Point3 u = cross(b - a, c - a).unit();
		return p - (u * dot(p - a, u));
	}
}

typedef Geo::Point point;
typedef Geo::Line line;
typedef Geo::Circle circle;
function<int(db)> sign = Geo::sign;
function<int(db,db)> cmp = Geo::cmp;

const int Ma = 1e6, inf = 0x3f3f3f3f, mod = 1e9 + 7;

double lef[] = {9, 8, 1, 3, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 7, 1, 3,
                 1, 6};

vector<point> a(20);

signed main() {
	#if SYNC==1
    ios::sync_with_stdio(false);
    cin.tie(0);
    #endif
	int T; scanf("%d", &T);
	while (T--) {
		rap (i, a) i.scan();
		vector<db> tp(20);
		int ind = 0;
		for (int i = 0; i < 20; i++) {
			tp[i] = a[i].dis(a[(i + 1) % 20]);
			//cerr << tp[i] << endl;
			if (fabs(tp[i] - 9.0) < 1e-4) ind = i;
			//cerr << ind << ' ' << cmp(tp[i], 9.0) << endl;
		}
		bool rev = false;
		bool lf = true;
		if (fabs(tp[(ind + 1) % 20] - 8.0) > 1e-4)
			rev = true;
		//cerr << ind << ' ' << boolalpha << rev << endl;
		//a[ind].print(); a[(ind + 1) % 20].print(), a[(ind + 2) % 20].print();
		//cerr << crossOp(a[(ind + 2) % 20], a[(ind + 1) % 20], a[ind]) << endl;
		if ((Geo::crossOp(a[(ind + 2) % 20], a[(ind + 1) % 20], a[ind]) < 0) == rev)
				lf = false;

		//for (int i = 0; i < 20; i++)
		//	debug(tp[(ind+i)%20]);
		//for (int i = 0; lf and i < 20; i++)
		//	if (fabs(tp[(ind + i) % 20] - lef[rev ? 20 - i - 1 : i]) > 1e-3)
		//		lf = false;
		if (lf) cout << "right" << endl;
		else cout << "left" << endl;
	}
    
    return 0;
}
