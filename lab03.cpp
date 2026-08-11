#include<bits/stdc++.h>
using namespace std;

using ll = long long;

ll power(ll a ,  ll b, ll m){
    ll r = 1;
    while(b){
        if(b & 1)
        r = (__int128)r*a % m ;
        a = (__int128)a*a % m;
        b >>= 1;
    }
    return r;
}

ll egcd(ll a ,ll b , ll &x , ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
     ll x1,y1;
     ll g = egcd(b,a%b,x1,y1);
     x = y1;
     y = x1 - (a/b)*y1;
     return g;

}
ll inverse(ll a , ll m){
    ll x,y;
    ll g = egcd(a,m,x,y);
    if(g!=1) return -1;
    return (x%m + m)%m;
    
}
ll getE(ll phi) {
    for (ll e = 2; e < phi; e++)
        if (__gcd(e, phi) == 1)
            return e;
    return -1;
}

int main(){
   ll ps,qs,pr,qr,M;
   cin >> ps >> qs;
   cin >> pr >> qr;
   cin >> M;
   ll ns = ps * qs;
   ll nr = pr * qr;
   ll phis = (ps - 1) * (qs - 1);
   ll phir = (pr - 1) * (qr - 1);
   ll es = getE(phis);
   ll ds = inverse(es, phis);
   ll er = getE(phir);
   ll dr = inverse(er, phir);

   ll S = power(M,ds,ns);
   ll C = power(M,er,nr);
    ll D = power(C, dr, nr);
    ll V = power(S, es, ns);
 if (D == M)
        cout << "Decryption Successful\n";
    else
        cout << "Decryption Failed\n";

    if (V == M)
        cout << "Signature Valid\n";
    else
        cout << "Signature Invalid\n";

    return 0;
}