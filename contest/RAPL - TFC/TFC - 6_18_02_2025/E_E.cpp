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
#define sz(x) ((int)(x).size())
#define PI 3.1415926535897932384626
#define endl "\n"
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define fsp(x) cout << fixed << setprecision(x)
#define fast_IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

#define f(i, a, b) for (int i = a; i <= b; i++)
#define r(i, a, b) for (int i = a; i >= b; i--)
#define fc(i, a, b, c) for (int i = a; i <= b; i+=c)
#define rc(i, a, b, c) for (int i = a; i >= b; i-=c)
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

inline void setBit(ll &x, int pos) { x |= (1LL << pos); }
inline void unsetBit(ll &x, int pos) { x &= ~(1LL << pos); }
inline void toggleBit(ll &x, int pos) { x ^= (1LL << pos); }
inline bool isSet(ll x, int pos) { return x & (1LL << pos); }
inline ll countTotalBits(ll x) { return 64 - __builtin_clzll(x); }
inline int countSetBits(ll x) { return __builtin_popcountll(x); }
inline int countLeadingZeros(ll x) { return __builtin_clzll(x); }
inline int countTrailingZeros(ll x) { return __builtin_ctzll(x); }
inline bool isPowerOfTwo(ll x) { return x && !(x & (x - 1)); }
inline ll nextPowerOfTwo(ll x) { if (x == 0) return 1; return 1LL << (64 - __builtin_clzll(x - 1)); }
inline ll prevPowerOfTwo(ll x) { if (x == 0) return 0; return 1LL << (63 - __builtin_clzll(x)); }
inline int lowestSetBitPos(ll x) { return countTrailingZeros(x); }
inline ll lowestSetBitValue(ll x) { return x & -x; }
inline ll clearLowestSetBit(ll x) { return x & (x - 1); }
inline string toBinary(ll n) { return bitset<64>(n).to_string(); }
inline ll toDecimal(string s) { return bitset<64>(s).to_ullong(); }

void solve() {
    ull n; cin>>n;
    vector<ull> v(n); cin>>v;
    ull s = accumulate(all(v),0ll);
    
    ull ar[46];
    ull p = n;
    for(int i=0; i<46; i++){
        ar[i] = p;
        p *= 2;
    }

    bitset<46> bt;
    for(int i=45; i>=0; i--){
        if(i>0 and s<ar[i] and s<ar[i-1]) continue;
        else if(s>=ar[i]){
            bt[i] = 1;
            s -= ar[i];
        }
        else if(accumulate(ar,ar+i,0ull)<s){
            bt[i] = 1;
            s = 0;
        }
    }
    
    if(s!=0) bt[0] = 1;
    cout<<bt.to_ullong()<<endl;
}

int main() {
    fast_IO;

    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    //     freopen("error.txt", "w", stderr);
    // #endif  

    int t = 1;
    //cin >> t;
    for (int caseNo = 1; caseNo <= t; caseNo++) {
        //printCase(caseNo, solve());
        solve();
    }

    return 0;
}