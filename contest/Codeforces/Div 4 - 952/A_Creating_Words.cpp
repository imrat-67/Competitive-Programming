#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define int long long
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define testcase cin>>t
#define ntestcase t=1
#define testcasen cin>>t; int caseno = 1
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define endl '\n'
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define mn1 cout<<"-1"<<endl
#define pr pair<int,int>
#define linf 1ll<<62
#define inf 1<<30
#define pi 3.1415926535897932385
int const mod = 1e9+7;
int const N = 1e5+7;
 
signed main(){
        fastio;
        int t; testcase;
        while(t--){
            string a,b; cin>>a>>b;
            swap(a[0],b[0]);
            cout<<a<<" "<<b<<endl;
        }
}