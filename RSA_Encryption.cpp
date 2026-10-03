#include<bits/stdc++.h>
using namespace std;

//gcd 
long long gcd(long long a ,long long b)
{
    while(b)
    {
        long long temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}

long long FindE(long long phi)
{
    for(long long e= 2 ; e <phi ; e++)
    {
        if(gcd(e,phi)==1)
        {
            return e;
        }
    }
    return -1;
}

long long FindD(long long e ,long long phi)
{

    for(long long d = 2 ; d<phi ; d++)
    {
        if((e*d)%phi ==1)
        { return d;}
    }
    return -1;
}

long long modPower( long long b , long long e ,long long m)
{
    long long res =1 ;
    while(e)
    {
        res = (res*b)%m;
        e--;
    }
    return res;
}
int main()
{
    int p , q;
    cin>> p>>q;
    long long  n = p*q;

    long long phi = (p-1)*(q-1);
    long long e = FindE(phi);   
    long long d = FindD(e, phi);

    cout<<"Public Key: ("<<e<<","<<n<<")"<<endl;
    cout<<"Private Key: ("<<d<<","<<n<<")"<<endl;   
    cout<<"n: "<<n<<endl;
    cout<<"phi: "<<phi<<endl;
    cout<<"e: "<<e<<endl;
    cout<<"d: "<<d<<endl;
    long long m;
    cin>>m;
    cout<<"Message: "<<m<<endl;
    long long encrypted = modPower(m, e, n);
    cout<<"Encrypted Message: "<<encrypted<<endl;
    long long decrypted = modPower(encrypted, d, n);
    cout<<"Decrypted Message: "<<decrypted<<endl;
}