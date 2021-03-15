#include <bits/stdc++.h>

using namespace std;
#define int long long int
#define watch(x) cout << (#x) << " is " << (x) << endl
#define all(x) x.begin(), x.end()
#define MOD 1000000007

bool isMatching(vector<pair<int,int>> &v1, vector<int,int> &v2){
  set<int> s;
  s.insert(v[i][0]);
  s.insert(v[i][1]);
  s.insert(v[i][2]);
  s.insert(v[i][3]);
  return (int)s.size()<4;
}

void solve() {
  int n, sum;
  cin >> n >> sum;
  vector<pair<int, int> > arr(n);
  for(int i = 0 ; i < n ; i++){
    int x; cin >> x;
    arr[i] = {x, i+1};
  }

  map<int, vector<pair<int, int> > > TWOSUM;
  for(int i = 0 ; i < n ; i++){
    for(int j = i+1 ; j < n ; j++){
      int s = arr[i].first + arr[j].first;
      int idx1 = arr[i].second;
      int idx2 = arr[j].second;
      pair<int, int> p(idx1, idx2);
      TWOSUM[s].push_back(p);
    }
  }

  int i = 0,  j = TWOSUM.size() - 1;
  while(  i < j) {
    int T = TWOSUM[i]. + TWOSUM[j].first;
    if (T > sum) {
      j--;
    } else if (T < sum) {
      i++;
    } else {
      int ni = i;
      int nj = j;
      while(TWOSUM[nj].first + TWOSUM[ni].first== T && nj < ){
      vector<int> v(4);
      v[0] = TWOSUM[i].second.first; v[1] = TWOSUM[i].second.second;
      v[2] = TWOSUM[j].second.first; v[3] = TWOSUM[j].second.second;
      ans.push_back(v);
    }
  }

  for(int  i = 0 ; i < ans.size(); i++){
    if(isMatching(ans,i)){continue;}
    else{
      for(auto x: ans[i])
        cout << x <<" ";
      return;
    }
  }
    cout<<"IMPOSSIBLE"<<endl;

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
        solve();
    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}
