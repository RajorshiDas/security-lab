#include<bits/stdc++.h>
using namespace std;
long long modpower(long long base, long long exp, long long mod)
    {
        long long result = 1;
        while(exp)
        {result = (result * base) % mod;
            exp--;
        }
        return result;
    }
long long modinverse(long long a ,long long p)
{
    for(long long i = 1 ;i <p ;i++)
    {
        if((a*i)%p==1)
        return i ;
    }
    return -1;
}

int main()
{
    long long p = 23;
    long long alpha = 5;

    long long a = 6; // Private key
    long long beta = (long long)(modpower(alpha ,a,p));
    cout<<"Public key ( "<< alpha << ", " << beta << ", " << p << " )" << endl;
     cout<<"Private key ( "<< a << " )" << endl;

     long long m = 15;
     long long r = 3;
     long long c1 = (long long)(modpower(alpha ,r,p));
     long long k = (long long)(modpower(beta ,r,p));
     long long c2 = (long long)((m * k) % p);
     cout<<"Encrypted message ( "<< c1 << ", " << c2 << " )" << endl;
     
     // Decryption

     long long k1 = (long long)(modpower(c1,a,p));
     long long k_inv = (long long)(modinverse(k1,p));
     long long m1 = (long long)((c2 * k_inv) % p);
     cout<<"Decrypted message ( "<< m1 << " )" << endl;

   

    
    return 0;
}
