#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define ld long double
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define len(x) ((int)(x).size())
#define PI 3.1415926535897932384626
#define endl "\n"
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define fsp(x) cout << fixed << setprecision(x)
#define fast_IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

#define each(i, v) for (auto& i : v)
#define fo(i, n) for (int i = 0; i < n; i++)
#define fi(i, n) for (int i = 1; i <= n; i++)
#define ro(i, n) for (int i = n - 1; i >= 0; i--)
#define ri(i, n) for (int i = n; i >= 1; i--)
#define fit(it, v) for (auto it = v.begin(); it != v.end(); it++)
#define rit(it, v) for (auto it = v.rbegin(); it != v.rend(); it++)

const ll INF = 1e18;
const int mod1 = 1000000007;
const int mod2 = 998244353;
const int N = 2e5 + 5;
const double EPS = 1e-9;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

#ifndef ONLINE_JUDGE
#include "headers/debug.hpp"
#define debug(x) cerr << #x << " = "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

template <typename T> void printCase(int caseNo, T result) { cout << "Case " << caseNo << ": " << result << endl; }
template<typename T, typename V> ostream& operator << ( ostream &os, const pair<T, V> &p ) { return os << p.first << " " << p.second; }
template<typename T, typename V> ostream& operator << ( ostream &os, const map<T, V> &mp ) { for( auto it : mp ) { os << it << endl;  } return os; }
template<typename T> ostream& operator << ( ostream &os, const vector<T> &v ) { bool space = false; for( T x : v ) { if( space ) os << " "; space = true; os << x; } return os; }
template<typename T> ostream& operator << ( ostream &os, const set<T> &st ) { bool space = false; for( T x : st ) { if( space ) os << " "; space = true; os << x; } return os; }
template<typename T> ostream& operator << ( ostream &os, const multiset<T> &st ) { bool space = false; for( T x : st ) { if( space ) os << " "; space = true; os << x; } return os; }
template<typename T, typename V> istream& operator >> ( istream &is, pair<T, V> &p ) { return is >> p.ff >> p.ss; }
template<typename T> istream& operator >> ( istream &is, vector<T> &v ) { for( T &x : v ) { is >> x; } return is;}
template <typename T, typename... Args> void print(T t, Args... args) { cout << t << " "; print(args...); }

ll const mxn = 1e6 + 7, b1 = 1e9 + 21, b2 = 1e9 + 181, m1 = 1e9 + 7, m2 = 1e9 + 9;
ll p1[mxn], p2[mxn], ip1[mxn], ip2[mxn],ib1 = 516162138, ib2 = 374699174;

ll exp(ll a, ll b, ll m) {
    ll r = 1; while (b) {
        if (b & 1) r = r * a % m;
        a = a * a % m,b /= 2;
    }   return r;
}

void pre_cal() {
    p1[0] = p2[0] = ip1[0] = ip2[0] = 1;
    ib1 = exp(b1, m1 - 2, m1), ib2 = exp(b2, m2 - 2, m2);
    for (ll i = 1; i < mxn; i++) {
        p1[i] = p1[i - 1] * b1 % m1, p2[i] = p2[i - 1] * b2 % m2;
        ip1[i] = ip1[i - 1] * ib1 % m1, ip2[i] = ip2[i - 1] * ib2 % m2;
    }
}

class hashing {
    vector<ll> h1, h2;
    ll n;

public:
    hashing(string s) {
        n = (int)s.size();
        h1.resize(n + 2);
        h2.resize(n + 2);

        h1[0] = h2[0] = 0;
        for (ll i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] + s[i - 1] * p1[i - 1]) % m1;
            h2[i] = (h2[i - 1] + s[i - 1] * p2[i - 1]) % m2;
        }
    }

    ll hash_val(ll l, ll r) {
        ll H1 = (h1[r + 1] - h1[l] + m1) * ip1[l] % m1;
        ll H2 = (h2[r + 1] - h2[l] + m2) * ip2[l] % m2;
        return H1 << 32 | H2;
    }

    static ll string_hash(const string& s) {
        ll h1 = 0, h2 = 0;
        ll power1 = 1, power2 = 1;
        for (char ch : s) {
            h1 = (h1 + ch * power1) % m1, h2 = (h2 + ch * power2) % m2;
            power1 = power1 * b1 % m1, power2 = power2 * b2 % m2;
        }
        return h1 << 32 | h2;
    }
};



void solve() {
    string a,b; cin>>a>>b;
    hashing ah(a),bh(b);
    
    ll n = len(a), m = len(b), cnt = 0;
    fo(i,min(n,m)) if(ah.hash_val(0,i)==bh.hash_val(0,i)) cnt++;

    cout<<n+m-cnt+(cnt!=0)<<endl;
}

int main() {
    fast_IO;
    pre_cal();
    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    //     freopen("error.txt", "w", stderr);
    // #endif  

    int t = 1;
    cin >> t;
    for (int caseNo = 1; caseNo <= t; caseNo++) {
        //printCase(caseNo, solve());
        solve();
    }

    return 0;
}