#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <algorithm>
#include "dijkstras.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, source);
    distances[source] = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int current_distance = pq.top().first;
        pq.pop();
        
        if (current_distance > distances[u]) continue;
        
        for (const auto& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.emplace(distances[v], v);
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return {};
    if (previous[destination] == -1 && destination != 0) return {};
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty() || total == numeric_limits<int>::max()) {
        cout << "No path found" << endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i + 1 < path.size() ? " " : " ");
    }
    cout << "\nTotal cost is " << total << endl;
}