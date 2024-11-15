#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
template <typename T>
inline void read(T &f) {
    f = 0; T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }
    while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;

}
 
template <typename T>
void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}
 
template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}
int dfs(int x){
	if (x==0)
		return 0;
	return dfs(x-1)+dfs(x-2);

}



int main(){
	int a=3;
	print(-202) ;
	cout << endl;
	int* b=&a;
	int * d=a;
	cout << b << endl;
	cout << *b << endl;
	funcpointer(b);	




	return 0;
}