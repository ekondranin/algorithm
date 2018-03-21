#include <bits/stdc++.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif // M_PI
#define endl "\n"
#define S struct
#define X first
#define Y second
#define V vector
#ifndef __linux__
#define LLD "%I64d"
#else
#define LLD "%ll""d"
#endif
#define FOR(x, y, z) for (int x = (y); x < (z); ++x)
#define FORR(x, y, z) for (int x = (y); x > (z); --x)
#define GET(a, n) for (int __i = 0; __i < (n); ++__i) cin >> a[__i];
#define GETM(a, n, m) for (int __i = 0; __i < (n); ++__i) for (int __j = 0; __j < m; ++__j) cin >> a[__i][__j];
#define PRINTM(a, n, m) for (int __i = 0; __i < (n); ++__i) { for (int __j = 0; __j < m; ++__j) cout << a[__i][__j] << " ";  cout << endl; };
#define PRINT(a, n) for (int __i = 0; __i < (n); ++__i) cout << a[__i] << " ";
#define IT(a) a.begin(), a.end()
#define SQR(x) (x) * (x)
#define CASE(a, s) cout << "Case #" << a << ": " << s << endl;
#define DEB(a) cout << #a << " = " << (a) << endl; cout.flush();
#define DEBA(a) for (auto __i: a) cout << __i << " "; cout << endl; cout.flush();
#define IFDEB(b, a) if (b) { cout << #a << " = " << (a) << endl; cout.flush(); }
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair <int, int> PII;
typedef pair <LL, LL> PLL;
const int MOD = 1000000007;
void sync_stdio() { cin.tie(NULL); ios_base::sync_with_stdio(false); }
S Sync_stdio { Sync_stdio() { cin.tie(NULL); ios_base::sync_with_stdio(false); } } _sync_stdio;
S FAIL { FAIL () { cout << "CHANGE!!!" << endl;}};

class BipartiteMatching
{
  public:
    struct Edge {
      int first_part_vertex;
      int second_part_vertex;
    };

    struct Vertex {
      int vertex_id;
      int part;
    };

    BipartiteMatching(int size_first_, int size_second_)
      : size_first(size_first_),
        size_second(size_second_),
        graph(size_first) {}

    void add_edge(int first_part_vertex, int second_part_vertex) {
        graph[first_part_vertex].push_back(second_part_vertex);
    }

    vector <Edge> find_matching() {
        if (!calculated_matching) {
            calculate_matching();
        }
	    vector <Edge> answer;
	    for (int i = 0; i < size_second; ++i) {
		    if (mt[i] != -1) {
			    answer.push_back({mt[i], i});
		    }
        }
        return answer;
    }

    vector <Vertex> find_minimum_vertex_cover() {
        if (!calculated_matching) {
            calculate_matching();
        }
        cerr << "Doesn't work" << endl;
        return {};
    }

  private:

    bool try_kuhn(int vertex) {
	    if (used[vertex]) {
            return false;
        }
   	    used[vertex] = true;
	    for (int to: graph[vertex]) {
		    if (mt[to] == -1 || try_kuhn(mt[to])) {
			    mt[to] = vertex;
                return true;
		    }
	    }
	    return false;
    }

    void calculate_matching() {
        mt.assign(size_second, -1);
        for (int i = 0; i < size_first; ++i) {
            used.assign(size_first, false);
		    try_kuhn(i);
	    }
	    calculated_matching = true;
    }

    int size_first, size_second;
    int calculated_matching = false;
    vector <vector <int>> graph;
    vector <int> mt;
    vector <char> used;
};

int main()
{
    int n, m;
    cin >> n >> m;
    return 0;
}


