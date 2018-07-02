#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
    int T; cin >> T;
    cout << setiosflags(ios::uppercase);
    cout << setw(0xf) << internal;
    while(T--) {
        double A; cin >> A;
        double B; cin >> B;
        double C; cin >> C;
        /* Enter your code here */
        cout << resetiosflags(ios_base::basefield | ios_base::adjustfield
            | ios_base::floatfield | ios_base::showbase | ios_base::showpos
            | ios_base::uppercase);
        cout << setw(0) << hex << showbase << (long long)A << '\n';
        cout << resetiosflags(ios_base::hex | ios_base::showbase);
        cout << setw(15) << showpos << right << fixed << setfill('_')
            << setprecision(2) << B << '\n';
        cout << resetiosflags(ios_base::basefield | ios_base::adjustfield
            | ios_base::floatfield | ios_base::showpos);
        cout << uppercase << scientific
            << setprecision(9) << setw(15) << C << '\n';
    }
    return 0;

}
