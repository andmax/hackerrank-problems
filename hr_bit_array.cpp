#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
constexpr unsigned int p2t31 = (1 << 31);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    unsigned int n, s, p, q; // (s, p, q) mod 2^31 = (s, p, q)
    cin >> n >> s >> p >> q;
    if (n == 0) {
        cout << "0\n";
        return 0;
    }
    unsigned int curr_a = s, apm;
    vector<bool> ut(p2t31);
    ut[curr_a] = true;
    int u = 1;
    for (int i = 1; i < n; ++i) {
        apm = (curr_a * p) & (0x7FFFFFFF); // = a * p mod 2^31
        curr_a = (apm + q) & (0x7FFFFFFF); // = (apm + q) mod 2^31
        if (not ut[curr_a]) {
            ++u;
            ut[curr_a] = true;
        }
    }
    cout << u << "\n";
    return 0;
}
