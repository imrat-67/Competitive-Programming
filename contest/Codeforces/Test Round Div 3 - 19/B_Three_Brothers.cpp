#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define ull unsigned long long
#define ld long double
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.1415926535897932384626
#define endl "\n"
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

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

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sortall(x) sort(all(x))
#define rev(x) reverse(all(x))
#define sz(x) ((int)(x).size())
#define mem(a,b) memset(a,b,sizeof(a))
#define lb(v, x) lower_bound(all(v), x) - v.begin()
#define ub(v, x) upper_bound(all(v), x) - v.begin()
#define maxn(v) *max_element(all(v))
#define minn(v) *min_element(all(v))
#define sumn(v) accumulate(all(v), 0LL)
#define fsp(x) cout << fixed << setprecision(x)
#define endl "\n"
#define fast_IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

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

const ll INF = 1e18;
const int mod1 = 1000000007;
const int mod2 = 998244353;
const int MAX = 2e5 + 5;
const double EPS = 1e-9;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

inline ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
inline ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }
inline ll ceil(ll p, ll q) { return p < 0 ? p / q : p / q + !!(p % q); }
inline ll floor(ll p, ll q) { return p > 0 ? p / q : p / q - !!(p % q); }
inline double logb(ll base, ll num) { return log(num) / log(base); }
inline bool isPerfectSquare(ll x) { ll s = sqrt(x); return s * s == x; }
inline bool isPowerOfN(ll x, ll n) { if (x == 0) return false; ll p = pow(x, 1.0 / n); return (ll)pow(p, n) == x; }
inline ll randN(int min, int max) {static random_device rd; static mt19937 gen(rd()); std::uniform_int_distribution<> dis(min, max); return dis(gen); }
inline ll modAdd(ll a, ll b, ll mod) { return (a % mod + b % mod) % mod; }
inline ll modSub(ll a, ll b, ll mod) { return (a % mod - b % mod + mod) % mod; }
inline ll modMul(ll a, ll b, ll mod) { return (a % mod * b % mod) % mod; }
inline ll modPow(ll base, ll exp, ll mod) {ll result = 1; while (exp > 0) { if (exp & 1) result = modMul(result, base, mod); base = modMul(base, base, mod); exp >>= 1;}return result;}
inline ll modInv(ll a, ll mod) { return modPow(a, mod - 2, mod); }
inline ll modDiv(ll a, ll b, ll mod) { return modMul(a, modInv(b, mod), mod); }
inline string toBinary(ll n) { return bitset<64>(n).to_string(); }

// Custom Hash for unordered_map and unordered_set
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// Custom Hash for unordered_map with pair
//unordered_map<pair<int, int>, int, pair_hash> mp;
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = custom_hash{}(p.first);
        auto hash2 = custom_hash{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_multimap = tree<T, R, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using max_heap = priority_queue<T>;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template <typename T1, typename T2> using safe_map = unordered_map<T1, T2, custom_hash>;
template <typename T> using safe_set = unordered_set<T, custom_hash>;

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
template<typename T> istream& operator >> ( istream &is, vector<T> &v ) { for( T &x : v ) { is >> x; } return is; }template <typename T, typename... Args> void print(T t, Args... args) { cout << t << " "; print(args...); }

void solve() {
    int a,b; cin>>a>>b;
    cout<<6-a-b<<endl;
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