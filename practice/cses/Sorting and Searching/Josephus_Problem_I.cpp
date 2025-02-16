#include <bits/stdc++.h>
using namespace std;

int josephus_recursive(int n) {
    if (n == 1) return 1;
    return (josephus_recursive(n - 1) + 2 - 1) % n + 1;
}

int main() {
    int n;
    cin >> n;
    cout << josephus_recursive(n) << endl;
    return 0;
}
