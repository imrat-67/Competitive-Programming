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