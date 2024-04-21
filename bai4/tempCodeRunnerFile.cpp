#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t; cin >> t;
    while(t--)
    {
        int n; int a[n];
        cin >> n;
        long long s[n];
        int f = 0;
        for(int i = 0; i < n; i++) s[i] = 0;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        s[0] = a[0];
        for(int i = 1; i < n; i++) s[i] = s[i - 1] + a[i];
        for(int i = 1; i < n; i++){
            if(s[n - 1] - a[i] - s[i-1] == s[i - 1]){
                cout << "YES" << endl;
                f = 1;
                break;
            }
        }
        if(f == 0) cout << "NO" << endl;
    }
}