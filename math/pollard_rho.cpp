\subsection{pollard rho质因数分解}
	\begin{verbatim}
/*   pollard rho    o(n^(1/4))
  mult_mod(LL a,LL b,LL c)-计算 (a*b)%c.   a,b都是long long的数，直接相乘可能溢出的
  pollard_rho 算法进行质因数分解  */
  
LL factor[100];   //质因数分解结果（刚返回时是无序的）
int tol;   //质因数的个数。数组小标从0开始

LL mult_mod(LL a,LL b,LL c)
{
    a%=c;
    b%=c;
    LL ret=0;
    while(b)
    {
        if(b&1){ret+=a;ret%=c;}
        a<<=1;
        if(a>=c)a%=c;
        b>>=1;
    }
    return ret;
}

LL gcd(LL a,LL b)
{
    if(a==0)return 1;
    if(a<0) return gcd(-a,b);
    while(b)
    {
        LL t=a%b;
        a=b;
        b=t;
    }
    return a;
}

LL Pollard_rho(LL x,LL c)
{
    LL i=1,k=2;
    LL x0=rand()%x;
    LL y=x0;
    while(1)
    {
        i++;
        x0=(mult_mod(x0,x0,x)+c)%x;
        LL d=gcd(y-x0,x);
        if(d!=1&&d!=x) return d;
        if(y==x0) return x;
        if(i==k){y=x0;k+=k;}
    }
}
//对n进行素因子分解
void findfac(LL n)
{
    if(Miller_Rabin(n))//素数
    {
        factor[tol++]=n;
        return;
    }
    LL p=n;
    while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
    findfac(p);
    findfac(n/p);
}
	\end{verbatim}
