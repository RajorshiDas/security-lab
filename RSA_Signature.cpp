#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a ,long long b)
{
    while(b)
    {
        long long temp =b;
        b = a%b;
        a = temp;
        
    }
    return a;
}
long long FindE(long long phi)
{
    for(long long e =2 ;e<phi ;e++)
    {
        if(gcd(e,phi)==1)
        {
            return e;
        }
    }
    return -1;
}
long long FindD(long long e,long long phi)
{
    for(long long d = 2 ; d< phi ; d++)
    {
        if((e*d)%phi == 1)
        {
            return d;
        }
    }
    return -1;
}
long long modPower(long long b , long long e , long long m)
{
    long  long res = 1 ;
    while(e)
    {
        res = (res * b)% m;
        e--;
    }
    return res;
}
int main()
{
   int p ,q ;
   cin >> p >> q;
   long long n = p*q;
   long  long phi = (p-1)*(q-1);
   long long e = FindE(phi);
   long long d = FindD(e ,phi);
    cout << "n: " << n << endl;
    cout << "phi: " << phi << endl;
    cout << "e: " << e << endl;
    cout << "d: " << d << endl;
    cout << "Public Key: (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (" << d << ", " << n << ")" << endl;
    long long m ;
    cin >> m;
    long long s = modPower(m,d,n);
    cout << "Signature: " << s << endl;
    long long v = modPower(s,e,n);
    cout << "Verification: " << v << endl;
    long long m1 ;
    cin >> m1;
    long m2 ;
    cin>> m2;
    long  long c1 =  modPower(m1,e,n);
    long long c2 = modPower(m2, e,n);
    long long  c = (c1*c2)%n;
    cout << "Ciphertext: " << c << endl;
    long long d1 = modPower(c,d,n);
    cout << "Decrypted Message: " << d1 << endl;

    long long d2 = (m1*m2)%n;
    cout << "Decrypted Message: " << d2 << endl;



}