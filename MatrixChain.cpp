#include <bits/stdc++.h>

using namespace std;
#define int long long int
#define watch(x) cout << (#x) << " is " << (x) << endl
#define all(x) x.begin(), x.end()
#define MOD 1000000007

void solve(int T) {
    int n,k,z;
    cin >> n >> k >> z;
    int arr[n];
    for(int i = 0 ; i < n ;i++)
      cin >> arr[i];

    int sum = 0;
    multiset<int> s;
    for(int i = 0 ; i <= k ;i++){
      sum+=arr[i];
      s.insert(arr[i]);
    }
    int ans = sum;

    for(int i = 0; i<z; i++){
      s.erase(s.find(arr[k-i]));
      sum = ans - arr[k-i] + *s.rbegin();
      ans = max(ans,sum);
    }
    cout <<ans <<endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("inputf.txt", "r", stdin);
    freopen("outputf.txt", "w", stdout);
#endif

    int T = 1;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}
