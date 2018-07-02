#include <bits/stdc++.h>

using namespace std;

long findUniqueSolutions(
    vector< map<int, int> >& d,
    const int& h,
    const long& n,
    const vector<long>& c) {
    if (n == 0) {
        return 1;
    } else if (c.size() == 0) {
        return 0;
    } else if (n < *min_element(c.begin(), c.end())) {
        return 0;
    }
    if (d[h].find(n) != d[h].end()) {
        return d[h][n];
    }
    vector<long> cc(c); // copy of c
    long rc = c.back(); // removed c
    cc.pop_back();
    long ways = 0;
    for (int i = 0; i <= n / rc; ++i) {
        ways += findUniqueSolutions(d, h+1, n - rc*i, cc);
    }
    d[h][n] = ways;
    return ways;
}

long getWays(long n, vector < long > c){
    // Complete this function
    clock_t s, e; s = clock();
    c.erase(remove_if(c.begin(), c.end(), [&](const long& e)
        { return e > n; }), c.end());
    long ways = 0;
    auto it = remove(c.begin(), c.end(), n);
    if (it != c.end()) {
        ways += 1;
        c.erase(it);
    }
    // in c now there are only values less than n
    vector<long> revc(c.size());
    copy(c.rbegin(), c.rend(), revc.begin());
    vector< map<int, int> > dones(c.size()+1);
    ways += findUniqueSolutions(dones, 0, n, revc);
    return ways;
}

int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<long> c(m);
    for(int c_i = 0; c_i < m; c_i++){
       cin >> c[c_i];
    }
    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
    long ways = getWays(n, c);
    cout << ways << '\n';
    return 0;
}
