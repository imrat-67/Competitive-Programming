#include<bits/stdc++.h>
using namespace std;

int main(){
    string h[9],v[9];

    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++){
            char c; cin>>c;
            h[i] += c;
            v[j] += c;
        }

    function<bool(string)> lamda = [](string s){
        string::iterator it = unique(s.begin(),s.end());
        return it - s.begin() == 9;
    };

    if(all_of(h,h+9,lamda) and all_of(v,v+9,lamda)) cout<<"Congratulations!"<<endl;
    else cout<<"Oh No!"<<endl;;
}