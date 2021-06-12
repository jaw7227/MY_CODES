#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define watch(x) cout << (#x) << " is " << (x) << endl
#define all(x) x.begin(), x.end()
#define printVec(vec) {for(auto &x : vec) cout << x <<" "; cout << endl; }
#define printMap(mp) {for(auto &p : mp) cout << p.first <<" " <<p.second <<endl;}
#define MOD 1000000007
#define hM 9999999900000001
#define inf 1e17
// const int maxN = 1;
// int BIT[maxN];
// void add(int x){while(x<N)BIT[x]++,x+=x&-x;}
// int sum(int x){return x?BIT[x]+sum(x-(x&-x)):0;}
vector<int> part[710];
int b, n;
int arr[30005];

int getCount(int l, int r, int k){
  int ans = 0;
  if(l/b == r/b){
    for(int i = l ; i <= r; i++){
      if(arr[i] >= k)
        ans++;
    }
    return ans;
  }
  for(int i = l ; i < (l/b)*b + b ; i++){
    if(arr[i] >= k)
      ans++;
  }

  for(int i = (l/b)+1 ; i < (r/b) ; i++){
    int idx = lower_bound(all(part[i]), k) - part[i].begin();
    ans += b - idx;
  }

  for(int i = (r/b)*b ; i<= r; i++){
    if(arr[i] >= k)
      ans++;
  }
  return ans;
}

void solve(int T) {
  cin >> n;
  vector<int> a(n);
  for(int i = 0 ; i < n ; i++)
    cin >> a[i];
  map<int,int> mp;

  for(int i = n-1 ; i >= 0 ; i--){
    if(mp.count(a[i])){
      arr[i] = mp[a[i]];
    }else{
      arr[i] = n+1;
    }
    mp[a[i]] = i;
  }

  b = sqrt(n);
  for(int i = 0 ; i < n ; i++){
    part[i/b].push_back(arr[i]);
  }
  for(int i = 0 ; i < (n + b - 1) / b ; i++)
    sort(all(part[i]));
  int Q;
  cin >> Q;
  while(Q--){
    int l, r, k;
    cin >> l >> r;
    l--, r--;
    k = r + 1;
    int ans = getCount(l, r, k);
    cout << ans <<endl;
  }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("inputf.txt", "r", stdin);
    freopen("outputf.txt", "w", stdout);
#endif

    int T = 1;
    //cin >> T;
    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}
