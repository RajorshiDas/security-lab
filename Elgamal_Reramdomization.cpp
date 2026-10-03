#include<bits/stdc++.h>
using namespace std;
long long modPower(long long base,long long exp ,long long p )
{
    long long result = 1;
    while(exp)
    {result = (result*base)%p;
    exp --;
    }
    return result;

}

  
long long modInverse(long long a ,long long p)
{
    for(long long i = 1;i<p ;i++)
    {
        if((a*i)%p==1)
        {return i;
        }
    }
    return -1;
}


int main()
{
   long long p = 23;
   long long alpha = 5;
   long long a =6; // Private key
   long long beta = (long long)modPower(alpha,a,p);
   cout<<"PUBLIC KEY (  "<<alpha <<" , "<<beta<< " , " <<p<<" ) "<<endl;
   cout<<"PRIVATE KEY (  "<<a<<" ) "<<endl;
   long long r = 3;
   long long m = 15;
   cout<<"Message ( "<<m<<" ) "<<endl;
   long long c1 = modPower(alpha ,r,p);
   long long k = modPower(beta ,r,p);
   long long c2 = (m*k)%p;
    cout<<"Encrypted message ( "<<c1<<" , "<<c2<<" ) "<<endl;
    long long r1 = 4;
    long long R1 = modPower(alpha ,r1,p);
    long long R2 = modPower(beta, r1, p);
    long long c1_1 = (c1*R1)%p;
    long long c2_1 = (c2*R2)%p;
   
    cout<<"Encrypted message ( "<<c1_1<<" , "<<c2_1<<" ) "<<endl;
   
    long long K = modPower(c1_1,a,p);
    long long k_inv = modInverse(K,p);
    long long m1 = (c2_1*k_inv)%p;
    cout<<"Decrypted message ( "<<m1<<" ) "<<endl;


}