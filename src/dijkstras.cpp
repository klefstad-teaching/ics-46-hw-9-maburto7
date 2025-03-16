#include "dijkstras.h"
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numV = G.size();
    if (numV == 0 || source < 0 || source >= numV) {
        return vector<int>();
    }

    vector<int> distances(numV, INF);
    distances[source] = 0;
    previous[source] = -1;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        auto [dist, u] = minHeap.top();
        minHeap.pop();

        if (dist > distances[u]) continue;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    if (previous[destination] == INF) {return path;}
    for (int at = destination; at != -1; at = previous[at]) {path.push_back(at);}
    reverse(path.begin(), path.end());
    return path;
}


void print_path(const vector<int>& v, int total){
    
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i != v.size() - 1) cout << " ";
    }
    cout << "\nTotal cost is:  "<< total << endl;
}