#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> unsorted(n);
    for(int unsorted_i = 0; unsorted_i < n; unsorted_i++){
       cin >> unsorted[unsorted_i];
    }
    // your code goes here
    vector<int> idx(unsorted.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int id0, int id1) {
        if (unsorted[id0].size() == unsorted[id1].size()) {
            return unsorted[id0] < unsorted[id1];
        } else {
            return unsorted[id0].size() < unsorted[id1].size();
        }
    } );
    for_each(idx.begin(), idx.end(), [&](const int& i){
        cout << unsorted[i] << '\n';
    });
    return 0;
}
