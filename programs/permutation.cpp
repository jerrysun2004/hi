#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using P = pair<int,int>;
using Tri = array<int,3>;

#define f first
#define s second

const int MOD = 1e9+7;

struct mi {
 	int v; explicit operator int() const { return v; } 
	mi() { v = 0; }
	mi(ll _v):v(_v%MOD) { v += (v<0)*MOD; }
};
mi& operator+=(mi& a, mi b) { 
	if ((a.v += b.v) >= MOD) a.v -= MOD; 
	return a; }
mi& operator-=(mi& a, mi b) { 
	if ((a.v -= b.v) < 0) a.v += MOD; 
	return a; }
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
mi& operator*=(mi& a, mi b) { return a = a*b; }

vector<mi> dp[100][100][100];
int N;
vector<P> points;
 
P& operator-=(P& a, const P& b) {
	a.f -= b.f, a.s -= b.s;
	return a;
}
int cross(P a, P b, P c) {
	b -= a; c -= a;
	return b.f*c.s-b.s*c.f;
}
 
int area(Tri a) {
	return abs(cross(points[a[0]],points[a[1]],points[a[2]]));
}
 
bool inside(Tri a, int b) {
	int sum = 0;
	for (int i = 0; i < 3; ++i) {
		swap(a[i],b);
		sum += area(a);
		swap(a[i],b);
	}
	sum -= area(a); assert(sum >= 0);
	return sum == 0;
}
 
void ad(vector<mi>& v, int ind, mi val) {
	while (v.size() <= ind) v.push_back(0);
	v[ind] += val;
}
 
int main() {
	cin >> N; points.resize(N); 
	for (P& p: points) cin >> p.f >> p.s;

	vector<Tri> triangles;
	for (int i = 0; i < N; ++i)
		for (int j = i+1; j < N; ++j)
			for (int k = j+1; k < N; ++k)
				triangles.push_back({i,j,k});
	sort(begin(triangles),end(triangles),[&](Tri a, Tri b) {
		return area(a) < area(b); });

	mi ans = 0;
	for (Tri& t: triangles) {
		int tot_inside = 0;
		vector<Tri> nex;
		
		for (int i = 0; i < N; ++i) {
			if (inside(t,i)) ++tot_inside;
			else {
				for (int j = 0; j < 3; ++j) {
					Tri new_t = t; new_t[j] = i;
					sort(begin(new_t),end(new_t));
					if (inside(new_t,t[j])) 
						nex.push_back(new_t);
				}
			}
		}
	
		

		tot_inside -= 3;
		assert(tot_inside >= 0);
		dp[t[0]][t[1]][t[2]].resize(1+tot_inside);
		dp[t[0]][t[1]][t[2]][0] = 1;

		for (int i = 0; i <= tot_inside; ++i) {
			mi v = dp[t[0]][t[1]][t[2]][i];
			if (i < tot_inside)
				ad(dp[t[0]][t[1]][t[2]],1+i,(tot_inside-i)*v);
			for (Tri u: nex)
				ad(dp[u[0]][u[1]][u[2]],1+i,v);
		}
		if (tot_inside == N-3) 
			ans += dp[t[0]][t[1]][t[2]][tot_inside];
	}

	cout << (6*ans).v << "\n";
}