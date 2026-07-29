#include<iostream>
#include<algorithm>
using namespace std;
using int128 = int;
// void printInt128(int128 x)
// {
//     if(x==0)
//     {
//         cout<<0;
//         return;
//     }

//     string s;

//     while(x>0)
//     {
//         s += char('0' + x%10);
//         x/=10;
//     }

//     reverse(s.begin(),s.end());

//     cout<<s;
// }
bool isprime(int128 n)
{
    if(n<=1)
    {
        return false;
    }
    for(int128 i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            return false;
        }
    }
    return true;
}
int128 gcd(int128 a,int128 b)
{
   while(b!=0)
   {
      int128 temp = b;
      b=a%b;
      a=temp;
   }
   return a;
}
int128 powerMod(int128 base,int128 exp,int128 mod)
{
  int128 result = 1;
  base = base%mod;
  while(exp>0)
  {
    if(exp%2==1)
    {
        result = result*base% mod;
    }
    base = base*base%mod;
    exp=exp/2;
  }
  return result;
}
int128 generateE(int128 phi)
{
   for(int128 e=2 ; e < phi; e++)
   {
    if(gcd(e,phi)==1)
    {
        return e;
    }
   }
   return -1; 
}
int main()
{
    int128 p,q;
    cout<<"Enter two prime numbers p and q: ";
    cin>>p>>q;

    if(!isprime(p) || !isprime(q))
    {
        cout<<"Both numbers must be prime."<<endl;
        return 0;
    }
    
    int128 n = p*q;
    int128 phi = (p-1)*(q-1);
    cout<<"n: "<<n<<endl;
    cout<<"phi: "<<phi<<endl;
    int128 e = generateE(phi);
    cout<<"e: "<<e<<endl;
    int128 m ;
    cout<<"Enter a message (as an integer) to encrypt: ";
    cin>>m;
    cout<<"Message: "<<m<<endl;

    int128 c = powerMod(m,e,n);
    cout<<"Ciphertext: "<<c<<endl;
    int128 d = 1;
    while((d*e)%phi!=1)
    {
        d++;
    }
    cout<<"d: "<<d<<endl;

    int128 decrypted = powerMod(c,d,n);
    cout<<"Decrypted: "<<decrypted<<endl;


}
