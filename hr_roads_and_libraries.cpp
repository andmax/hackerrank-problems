#include <bits/stdc++.h>

using namespace std;

int subset_find(
    const int& i,
    const vector<int>& parent) {
    // find the subset root of an element i
    if (parent[i] == 0) // if i has no parent
        return i; // i is in the subset of itself
    return subset_find(parent[i], parent);
}

void subset_union(
    vector<int>& parent,
    const int& i,
    const int& j) {
    // union of two subsets
    int root_i = subset_find(i, parent);
    int root_j = subset_find(j, parent);
    parent[root_i] = root_j;
}

bool there_is_a_cycle(
    vector<int>& parent,
    const int& e,
    const vector< pair<int, int> >& _ae) {
    // use union-find algorithm to check if there is a cycle
    int i = subset_find(_ae[e].first, parent);
    int j = subset_find(_ae[e].second, parent);
    if (i == j)
        return true;
    subset_union(parent, i, j);
    return false;
}

int main() {
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        int n; // number of cities
        int m; // number of roads
        long x; // cost of build a library in a city
        long y; // cost of build a road connecting two cities
        cin >> n >> m >> x >> y;
        vector< pair<int, int> > edges(m); // edges of the graph
        for(int a1 = 0; a1 < m; a1++){
            int city_1;
            int city_2;
            cin >> city_1 >> city_2;
            edges[a1] = make_pair(city_1, city_2);
        }
        long long total = 0;
        if (x <= y) {
            // if the cost of building a library in a city is lower than the
            // cost of building a road connecting two cities, the result is
            // that you should build a library in every city and the total cost
            // is the number of cities times the cost to build one library
            total = (long long)n * x;
        } else {
            // else, the cost of building a library in a city is greater than
            // the cost to build a road connecting two cities, the result is
            // more involving as we should find the best combination of roads
            // and libraries to rebuid
            vector< vector<int> > v2e(n+1);
            for (int ei = 0; ei < edges.size(); ++ei) {
                const pair<int, int>& e = edges[ei];
                v2e[e.first].push_back(ei);
                v2e[e.second].push_back(ei);
            }
            // vector of booleans comprising the rebuilt strategy to be taken
            vector<bool> rr(m); // rebuilt roads
            vector<bool> rc(n+1); // rebuilt city library
            vector<bool> ep(m); // edges already processed
            vector<bool> vp(n+1); // vertices already processed
            vector<int> parent(n+1); // union-find parent data structure
            for (int re = 0; re < m; ++re) { // for each root edge index
                if (ep[re]) {
                    continue;
                }
                stack<int> ea;
                ea.push(re);
                vector<int> se; // spanning-tree edges
                while (not ea.empty()) {
                    int e = ea.top();
                    ea.pop();
                    if (ep[e]) {
                        continue;
                    } else {
                        ep[e] = true;
                    }
                    const int& v0 = edges[e].first;
                    const int& v1 = edges[e].second;
                    vp[v0] = true;
                    vp[v1] = true;
                    if (not there_is_a_cycle(parent, e, edges)) {
                        se.push_back(e);
                    }
                    for (const auto& ne : v2e[v0]) {
                        if (ne != e and not ep[ne]) {
                            ea.push(ne);
                        }
                    }
                    for (const auto& ne : v2e[v1]) {
                        if (ne != e and not ep[ne]) {
                            ea.push(ne);
                        }
                    }
                }
                for (const auto& e : se) {
                    rr[e] = true;
                }
                rc[edges[re].first] = true;
            }
            for (int i = 1; i <= n; ++i) {
                if (not vp[i])
                    rc[i] = true;
            }
            for (const bool& rebuilt_lib : rc) {
                if (rebuilt_lib)
                    total += x;
            }
            for (const bool& rebuilt_road : rr) {
                if (rebuilt_road)
                    total += y;
            }
        }
        cout << total << '\n';
    }
    return 0;
}
