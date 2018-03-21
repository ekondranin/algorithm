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
S Sync_stdio { Sync_stdio() { cin.tie(NULL); ios_base::sync_with_stdio(false); } } _sync_stdio;
S FAIL { FAIL () { cout << "CHANGE!!!" << endl;}};

struct Edge {
    int from;
    int to;
    LL cost;
    LL cap;
    LL flow;
    Edge(int from_, int to_, LL cost_ = 1, LL cap_ = 1)
        : from(from_),
          to(to_),
          cost(cost_),
          cap(cap_),
          flow(0) {}
};

template <class Edge>
class SPFA
{
  public:
    SPFA(int vertices_count_, vector <Edge> &edges_)
      : vertices_count(vertices_count_),
        edges(edges_),
        dist(vertices_count, SPFA <Edge>::INF),
        g(vertices_count),
        pre(vertices_count, -1) {
        for (int i = 0; i < edges.size(); ++i) {
            g[edges[i].from].push_back(i);
        }
    }
    void calculate(int source_)
    {
        source = source_;
        dist[source] = 0;
        queue <int> q;
        q.push(source);
        vector <int> used(vertices_count);
        while (q.size()) {
            int u = q.front();
            q.pop();
            used[u] = 0;
            for (int index: g[u]) {
                const auto &edge = edges[index];
                if (edge.cap - edge.flow == 0) {
                    continue;
                }
                if (dist[u] + edge.cost < dist[edge.to]) {
                    dist[edge.to] = dist[u] + edge.cost;
                    pre[edge.to] = index;
                    if (!used[edge.to]) {
                        used[edge.to] = 1;
                        q.push(edge.to);
                    }
                }
            }
        }
    }
    vector <int> restore_path(int target)
    {
        vector <int> path;
        while (target != source)
        {
            int index = pre[target];
            const auto &edge = edges[index];
            target = edge.from;
            path.push_back(index);
        }
        reverse(IT(path));
        return path;
    }
    void reset()
    {
        dist.assign(vertices_count, INF);
    }
    Edge &get_edge(int index) {
        return edges[index];
    }
    const Edge &get_edge(int index) const {
        return edges[index];
    }
    const vector <LL> &get_distances() const {
        return dist;
    }
    const LL no_path() const {
        return INF;
    }
  private:
    const LL INF = 1e18;
    int vertices_count;
    vector <Edge> &edges;
    vector <LL> dist;
    vector <vector <int>> g;
    vector <int> pre;
    int source;
};

class MinCostMaxFlow
{
  public:
    MinCostMaxFlow(int vertices_count_): vertices_count(vertices_count_) {};
    LL calculate()
    {
        SPFA <Edge> spfa(vertices_count, edges);
        LL flow = 0;
        while (1) {
            spfa.reset();
            spfa.calculate(source);
            if (spfa.get_distances()[sink] == spfa.no_path()) {
                break;
            }
            vector <int> path = spfa.restore_path(sink);
            LL add = path_flow(path);
            flow += add;
            for (auto index: path) {
                edges[index].flow += add;
                edges[index ^ 1].flow -= add;
            }
        }
        return flow;
    }
    LL get_cost() {
        LL res = 0;
        for (auto &edge: edges) {
            if (edge.cap > 0 && edge.flow > 0) {
                res += edge.cost;
            }
        }
        return res;
    }
    void set_sink(int sink_)
    {
        sink = sink_;
    }
    void set_source(int source_)
    {
        source = source_;
    }
    vector <Edge> &get_edges() {
        return edges;
    }
    const vector <Edge> &get_edges() const {
        return edges;
    }
    LL add_edge(int from, int to, int cap, int cost)
    {
        edges.push_back({from, to, cost, cap});
        edges.push_back({to, from, -cost, 0});
    }
    void print_edges() {
        for (int i = 0; i < edges.size(); i += 2) {
            cout << edges[i].from << "->" << edges[i].to <<
                " " << "CAP: " << edges[i].cap << " " << "COST: " << edges[i].cost << endl;
        }
    }
  private:
    LL path_flow(const vector <int> &path_indices) {
        LL flow = LLONG_MAX;
        for (int index: path_indices) {
            flow = min(flow, edges[index].cap - edges[index].flow);
        }
        return flow;
    }
    int vertices_count;
    vector <Edge> edges;
    int source = -1;
    int sink = -1;
};

int main()
{
    string s;
    cin >> s;
    vector <int> cnt(26);
    FOR (i, 0, s.size()) {
        ++cnt[s[i] - 'a'];
    }
    int n;
    cin >> n;
    MinCostMaxFlow min_cost_max_flow(n + 26 + 2);
    min_cost_max_flow.set_source(0);
    min_cost_max_flow.set_sink(n + 26 + 1);
    FOR (i, 0, n) {
        string t;
        cin >> t;
        int max_cnt;
        cin >> max_cnt;
        min_cost_max_flow.add_edge(0, i + 1, max_cnt, 0);
        for (auto letter: t) {
            min_cost_max_flow.add_edge(i + 1, n + 1 + (letter - 'a'), 1, i + 1);
        }
    }
    FOR (i, 0, 26) {
        if (cnt[i] == 0) {
            continue;
        }
        min_cost_max_flow.add_edge(n + 1 + i, n + 26 + 1, cnt[i], 0);
    }
    LL flow = min_cost_max_flow.calculate();
    if (flow != s.size()) {
        cout << -1;
        return 0;
    }
    cout << min_cost_max_flow.get_cost();
}
