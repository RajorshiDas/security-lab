#include<bits/stdc++.h>
using namespace std;
long long modPower(long long base ,long long exp ,long long p)
{
    long long res = 1;
    while(exp)
    {
        res = (res*base)%p;
        exp --;
    }
    return res ;
}
long long modInverse(long long a ,long long p)
{
    for(long long i =1 ;i<p ;i++)
    {
        if((a*i)%p==1)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    long long p = 23;
    long long alpha = 5;
    long long a = 6 ; //Private Key
    long long beta = (long long)(modPower(alpha,a,p));

    cout<<"Public key ( "<< alpha << ", " << beta << ", " << p << " )" << endl;
    cout<<"Private key: " << a << endl;
    long long r = 3;
    long long m = 15;
    long long c1 = (long long)modPower(alpha,r,p);
    long long r_inv = (long long)modInverse(r,p-1);
    long long c2 = (long long)(r_inv*(m - a*c1))%(p-1);
      if (c2 < 0)
        c2 += (p - 1);


    cout<<"Signature: (" << c1 << ", " << c2 << ")" << endl;

    long long left = (long long )(modPower(alpha,m,p));
    long long right = (long long)((modPower(beta,c1,p))*(modPower(c1,c2,p)))%p;

    cout<<"Left side: " << left << endl;
    cout<<"Right side: " << right << endl;

    return 0;

}