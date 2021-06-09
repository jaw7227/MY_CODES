#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

using namespace std;
#define int long long int
#define watch(x) cout << (#x) << " is " << (x) << endl
#define all(x) x.begin(), x.end()
#define MOD 1000000007
#define Endl endl

int gcd(int a, int b) {
  if (a == 0 || b == 0) {
    return (a + b);
  }
  return gcd(b, a % b);
}

double bs(int val) {
  double ans = 0;
  double l = 0, r = val;
  for (int i = 0; i < 60; i++) {
    double m = (l + r) / 2;
    if (m * m <= val) {
      // deb(m);
      ans = m;
      l = m;
    } else
      r = m;
  }
  return ans;
}

vector<int> sieve(int n) {
  vector<int> v(n + 2, 0);
  n++;
  v[0] = 1;
  for (int i = 2; i * i < n; i++) {
    if (!v[i])
      for (int j = 2 * i; j < n; j += i)
        v[j]++;
  }
  return v;
}
int fastExpo(int a, int n, int mod) {
  int result = 1;
  while (n > 0) {
    if (n & 1)
      result = (result * a) % mod;
    a = (a * a) % mod;
    n >>= 1;
  }
  return result;
}

int modInverse(int n, int mod) { return fastExpo(n, mod - 2, mod); }
const int facsz = 2;
int Fact[facsz];
int inFact[facsz];
void factorial() {
  Fact[0] = inFact[0] = 1;
  for (int i = 1; i < facsz; i++) {
    Fact[i] = (Fact[i - 1] * i) % MOD;
    inFact[i] = modInverse(Fact[i], MOD);
  }
}

int __nCr(int n, int r, int mod) {
  if (r > n || r < 0)
    return 0;
  return Fact[n] * inFact[n - r] % mod * inFact[r] % mod;
}

const int psz = 2;
int phi[psz];
void eulerTotient() {
  for (int i = 1; i < psz; i++)
    phi[i] = i;

  for (int i = 2; i < psz; i++) {
    if (phi[i] == i) {
      for (int j = i; j < psz; j += i) {
        phi[j] = (phi[j] * (i - 1)) / i;
      }
    }
  }
}

class Triplet {
public:
  int x;
  int y;
  int gcd;
};
Triplet extendedEuclid(int a, int b) {
  if (b == 0) {
    Triplet obj;
    obj.x = 1;
    obj.y = 0;
    obj.gcd = a;
    return obj;
  }
  Triplet smallans = extendedEuclid(b, a % b);
  Triplet ans;
  ans.gcd = smallans.gcd;
  ans.x = smallans.y;
  ans.y = smallans.x - (a / b) * smallans.y;
  return ans;
}

void precompute_hash(string const &s) {
  const int sz = 1e6 + 5;
  vector<long long> h(sz + 5);
  vector<long long> p_pow(sz + 5);
  const int p = 31;
  const int m = 1e9 + 9;
  int n = s.size();
  p_pow[0] = 1;
  h[0] = 0;
  for (int i = 1; i < n; i++)
    p_pow[i] = (p_pow[i - 1] * p) % m;

  for (int i = 0; i < n; i++)
    h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;

  /*
  long long cur_h = (h[i + l] + m - h[i]) % m;
  cur_h = (cur_h * p_pow[n-i-1]) % m;
  */
}
class DSU {

public:
  vector<int> parent;
  vector<int> size;
  int n;
  DSU(int n) {
    this->n = n;
    for (int i = 0; i <= n; i++) {
      parent.push_back(i);
      size.push_back(1);
    }
  }

  int find_set(int v) {
    if (v == parent[v])
      return v;
    return parent[v] = find_set(parent[v]);
  }
  void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (size[a] < size[b])
        swap(a, b);
      parent[b] = a;
      size[a] += size[b];
    }
  }
  void printset() {
    for (int i = 1; i <= n; i++) {
      cout << parent[i] << " ";
    }
    cout << endl;
  }
};

struct node {
public:
  node *left, *right;
  node() {
    left = nullptr;
    right = nullptr;
  }
};
class Trie {
  node *root;

public:
  Trie() { root = new node(); }

  void insert(int num) {
    node *temp = root;
    for (int i = 31; i >= 0; i--) {
      int bit = (num) & (1 << i);
      if (bit) {
        if (temp->right == nullptr)
          temp->right = new node();
        temp = temp->right;
      } else {
        if (temp->left == nullptr)
          temp->left = new node();
        temp = temp->left;
      }
    }
  }

  int max_Xor(int num) {
    node *temp = root;
    int xorsum = 0;
    for (int i = 31; i >= 0; i--) {
      int bit = num & (1 << i);
      if (bit) {
        if (temp->left != nullptr) {
          xorsum |= (1 << i);
          temp = temp->left;
        } else {
          temp = temp->right;
        }
      } else {
        if (temp->right != nullptr) {
          xorsum |= (1 << i);
          temp = temp->right;
        } else
          temp = temp->left;
      }
    }
    return xorsum;
  }
};

class FenwickTree {
public:
  vector<int> BIT;
  int n;
  FenwickTree(int n) {
    this->n = n;
    BIT.resize(n + 1);
    // cout << BIT.size() << endl;
  }
  void update(int idx, int value) {
    for (; idx <= n; idx += (idx & (-idx))) {
      BIT[idx] += value;
    }
  }

  int query(int idx) {
    int ans = 0;
    for (; idx > 0; idx -= (idx & (-idx))) {
      ans += BIT[idx];
    }
    return ans;
  }
};

typedef long long  ll;
ll X[2000005],Y[2000005];

void calcsubarray(vector<int> &a, ll x[], int n, int c)
{
  for (int i=0; i<(1<<n); i++)
  {
    ll s = 0;
    for (int j=0; j<n; j++)
      if (i & (1<<j))
        s += a[j+c];
    x[i] = s;
  }
}
int size_X, size_Y;
void SubsetSum(vector<int> &a, int n)
{
  calcsubarray(a, X, n/2, 0);
  calcsubarray(a, Y, n-n/2, n/2);

  size_X = 1<<(n/2);
  size_Y = 1<<(n-n/2);
  sort(Y, Y+size_Y);
}

vector<int> dij(vector<int> &SOURCES, int n, vector<vector<pair<int,int>>> &adj){
  vector<int> dis(n+1, INT_MAX);
  vector<int> parent(n+1, -1);
  set< vector<int> > s;
  for(auto &node : SOURCES){
    dis[node] = 0;
    s.insert({0, node});
  }
  while(!s.empty()){
    auto it = s.begin();
    int u = (*it)[1];
    s.erase(it);
    for(auto &p : adj[u]){
      int v = p.first, w = p.second;
      if(dis[v] > dis[u] + w){
        s.erase({dis[v], v});
        dis[v] = w + dis[u];
        parent[v] = u;
        s.insert({dis[v], v});
      }
    }
  }
  return dis;
}
void floyd_warshall(vector<vector<int>>&grid){
  int n =grid.size();
  for(int k = 0 ; k < n ; k++){
    for(int i = 0;  i < n ; i++){
      for(int j = 0 ; j < n ; j++){
        if(grid[i][k] != -1 and grid[k][j] != -1){
          int val = grid[i][j];
          if(val == -1)
            val = 1e9;
          grid[i][j] = min(val, grid[i][k] + grid[k][j]);
        }
      }
    }
  }
  // cycle Detection
  bool isCycle = false;
  for(int i = 0 ; i <  n ; i++){
    if(grid[i][i] < 0){
      isCycle = 1;
      break;
    }
  }
  // part of cycle check for d[i][k]!= inf and d[k][k] < 0 ans dp[k][j] != inf
}

vector<int> bellman_ford(vector<vector<int>> edges, int n){
  vector<int> dist(n+1, 0);
  for(int i = 0 ; i < 2*n ; i++){
    for(auto &edge : edges){
      int u = edge[0], v = edge[1], w = edge[2];
      if( i < n - 1){
        dist[v] = min(dist[v], w + dist[u]);
      }
      else{
        if(dist[v] > w + dist[u]){
          dist[v] = -INT_MAX;
        }
      }
    }
  }
  return dist;
}

bool topologicalSort(int u, vector<int>&color, vector<int>&ans, vector<vector<int>> &adj){
  if(color[u] > 1){
    return color[u] == 3;
  }
  color[u] = 2;
  for(auto nbr : adj[u]){
    if(color[u]==3)
      continue;
    if(color[nbr]==2 || !topologicalSort(nbr, color, ans, adj)){
      return false;
    }
  }
  ans.push_back(u);
  color[u] = 3;
  return true;
}

int prims(vector<vector<pair<int,int>>> &adj, int n){
  vector<int> vis(n+1, false);
  priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> PQ;
  PQ.push({0, 1});
  int ans = 0;
  while(!PQ.empty()){
    auto it = PQ.top();
    int wt = (it.first);
    int u = (it.second);
    PQ.pop();
    if(vis[u])continue;
    vis[u] = 1;
    ans +=  wt;
    for(auto &p : adj[u]){
      int v = p.first, w = p.second;
        PQ.push({w, v});
    }
  }
//  cout << ans << endl;
  return ans;
}



/*---------------------------------------------------------*/

void solve(int T) {
  int n;
  cin >> n;
  if(n % 2 == 0){
    int N = n/2;
    int x = sqrt(N);
    if(x*x == N){
      cout <<"YES"<<endl;
      return;
    }
  }
  if(n%4==0){
    int N = n/4;
    int x = sqrt(N);
    if(x*x == N){
      cout <<"YES"<<endl;
      return;
    }
  }
  cout <<"NO"<<endl;
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

  cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
  return 0;
}
