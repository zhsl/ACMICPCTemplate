/* Lacus定理求 C(n，m)%p
 Lucas(n,m,p)=C(n%p,m%p)* Lucas(n/p,m/p,p)
 Lucas(n,0,p)=1;      */

#define LL __int64
LL fac[MAX];   //MAX<=p,p为取模数

void init(LL p)
{
    int i;
    fac[0]=1;
    for(i=1;i<=p;i++)
        fac[i]=fac[i-1]*i%p;
}

LL pow(LL a, LL b,LL p)
{
    LL tmp=a%p,ans=1;
    while(b)
    {
        if(b&1)ans=ans*tmp%p;
        tmp=tmp*tmp%p;
        b>>=1;
    }
    return  ans;
}

LL C(LL n, LL m,LL p)
{
    return  m>n?0:fac[n]*pow(fac[m]*fac[n-m],p-2,p)%p;
}

LL lucas(LL n,LL m,LL p)
{
    return  m?(C(n%p,m%p,p)*lucas(n/p,m/p,p))%p:1;
}