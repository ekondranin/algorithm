#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::min;
using std::pair;

class MaxFlow {
  public:
    static const long long INF = 2e13;
    struct Edge {
        int from, to;
        long long cap, flow;
    };

    void add_edge(int from, int to, long long cap)
    {
        Edge edge_first = {from, to, cap, 0 };
        Edge edge_second = {to, from, 0, 0 };
        graph[from].push_back(edges.size());
        edges.push_back(edge_first);
        graph[to].push_back(edges.size());
        edges.push_back(edge_second);
    }

    explicit MaxFlow(int vertices_count_)
    {
        vertices_count = vertices_count_;
        dist.resize(vertices_count);
        ptr.resize(vertices_count);
        graph.resize(vertices_count);
    }

    long long calculate()
    {
        long long flow = 0;
        while (2 + 2 == 4) {
            if (!bfs()) {
                break;
            }
            ptr.assign(vertices_count, 0);
            while (long long pushed = dfs(source, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
    void set_source(int source_)
    {
        source = source_;
    }
    void set_sink(int sink_)
    {
        sink = sink_;
    }

  private:
    bool bfs()
    {
        queue <int> to_visit;
        to_visit.push(source);
        dist.assign(vertices_count, -1);
        dist[source] = 0;
        while (to_visit.size() && dist[sink] == -1) {
            int current_vertex = to_visit.front();
            to_visit.pop();
            for (int id: graph[current_vertex]) {
                int to = edges[id].to;
                if (dist[to] == -1 && edges[id].flow < edges[id].cap) {
                    to_visit.push(to);
                    dist[to] = dist[current_vertex] + 1;
                }
            }
        }
        return dist[sink] != -1;
    }

    long long dfs(int start_vertex, long long flow)
    {
        if (!flow) {
            return 0;
        }
        if (start_vertex == sink) {
            return flow;
        }
        for (; ptr[start_vertex] < graph[start_vertex].size(); ++ptr[start_vertex]) {
            int id = graph[start_vertex][ptr[start_vertex]];
            int to = edges[id].to;
            if (dist[to] != dist[start_vertex] + 1) {
                continue;
            }
            long long pushed = dfs(to, min(flow, edges[id].cap - edges[id].flow));
            if (pushed) {
                edges[id].flow += pushed;
                edges[id ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int vertices_count;
    int source = -1;
    int sink = -1;
    vector <int> dist;
    vector <int> ptr;
    vector <Edge> edges;
    vector <vector <int>> graph;
};

int main()
{
    int vertices_count, edges_count;
    cin >> vertices_count >> edges_count;
    vector <int> gold(vertices_count);
    for (int i = 0; i < vertices_count; ++i) {
        cin >> gold[i];
    }
    long long sum = accumulate(gold.begin(), gold.end(), 0LL);
    vector <pair <int, int>> edges(edges_count);
    for (int i = 0; i < edges_count; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }
    long long left = 0;
    long long right = 1e6 + 3;
    while (left < right) {
        long long mid = (left + right) / 2;
        MaxFlow max_flow(vertices_count + 2);
        for (int i = 0; i < edges_count; ++i) {
            max_flow.add_edge(edges[i].first, edges[i].second, MaxFlow::INF);
        }
        for (int i = 0; i < vertices_count; ++i) {
            max_flow.add_edge(0, i + 1, gold[i]);
        }
        for (int i = 0; i < vertices_count; ++i) {
            max_flow.add_edge(i + 1, vertices_count + 1, mid);
        }
        max_flow.set_source(0);
        max_flow.set_sink(vertices_count + 1);
        long long flow = max_flow.calculate();
        if (flow == sum) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    cout << left << endl;
    return 0;
}
