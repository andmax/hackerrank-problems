#include <bits/stdc++.h>

using namespace std;

int migratoryBirds(int n, vector <int> ar) {
    // Complete this function
    vector<int> bh(6); // birds histogram
    for (const int& e : ar) {
        bh[e] += 1;
    }
    int max = 0;
    for (int i = 1; i < bh.size(); ++i) {
        if (bh[i] > bh[max]) {
            max = i;
        }
    }
    return max;    
}

int main() {
    int n;
    cin >> n;
    vector<int> ar(n);
    for(int ar_i = 0; ar_i < n; ar_i++){
       cin >> ar[ar_i];
    }
    int result = migratoryBirds(n, ar);
    cout << result << endl;
    return 0;
}
