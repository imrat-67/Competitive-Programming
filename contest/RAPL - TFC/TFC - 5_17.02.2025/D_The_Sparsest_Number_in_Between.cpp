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

#define setBit(x, pos) (x |= (1LL << pos))
#define unsetBit(x, pos) (x &= ~(1LL << pos))
#define toggleBit(x, pos) (x ^= (1LL << pos))
#define isSet(x, pos) (x & (1LL << pos))
#define countSetBits(x) __builtin_popcountll(x)
#define countLeadingZeros(x) __builtin_clzll(x)
#define countTrailingZeros(x) __builtin_ctzll(x)
#define firstSetBit(x) __builtin_ffsll(x)
#define lastSetBit(x) countTrailingZeros(x)
#define isPowerOfTwo(x) (x && !(x & (x - 1)))
#define nextPowerOfTwo(x) (1LL << (32 - __builtin_clz(x - 1)))
#define prevPowerOfTwo(x) (1LL << (31 - __builtin_clz(x)))
inline string toBinary(ll n) { return bitset<20>(n).to_string(); }


void solve() {
    ull a,b; cin>>a>>b;
    bitset<70> ba(a),bb(b),bc(0);
    
    debug(a);
    debug(b);
    ull idx = 0;
    ro(i,70){
        if(ba[i] != bb[i]) {
            idx = i;
            break;;
        }
        bc[i] = ba[i];
    }
    debug(ba.to_string());
    debug(bb.to_string());
    debug(bc.to_string());

    set<ull> st;
    st.insert(bc.to_ullong());
    ro(i,idx+1){
        bc[i] = 1;
        debug(bc.to_string());
        st.insert(bc.to_ullong());
        bc[i] = 0;
    }
    debug(idx);
    debug(st);

    cout<<*st.lower_bound(a)<<endl;
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