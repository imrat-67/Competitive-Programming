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
#define all(x) x.begin(), x.end()
#define sz(x) ((int)(x).size())
#define PI 3.1415926535897932384626
#define endl "\n"
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
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
vector<ll> baseConvert(ll num, ll base) { vector<ll> v; while (num) { v.pb(num % base); num /= base; } return v; }
ll sumOfDigits(ll n) { ll sum = 0; while (n != 0) { sum += n % 10; n /= 10; } return sum; }
ll countDigits(ll n) { return floor(log10(n) + 1); }

#define rall(x) x.rbegin(), x.rend()
#define sortall(x) sort(all(x))
#define rev(x) reserse(all(x))
#define mem(a,b) memset(a,b,sizeof(a))
#define lb(v, x) lower_bound(all(v), x) - v.begin()
#define ub(v, x) upper_bound(all(v), x) - v.begin()
#define maxn(v) *max_element(all(v))
#define minn(v) *min_element(all(v))
#define sumn(v) accumulate(all(v), 0LL)


void solve() {
    ll n , k; cin >> n >> k;
    if(k == 1) cout<<n<<endl;
    else{
        vector<ll> v = baseConvert(n, k);
        cout<<sumn(v)<<endl;
    }
}

int main() {
    fast_IO;

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