#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    vector<int> v(n);
    for_each(v.begin(), v.end(), [](int& e) {cin >> e;});
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int qv;
        cin >> qv;
        auto it = lower_bound(v.begin(), v.end(), qv);
        int j = (it - v.begin());
        if ((*it) == qv)
            cout << "Yes ";
        else
            cout << "No ";
        cout << j+1 << '\n';
    }
    return 0;
}
