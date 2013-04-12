/*  number theory basic
   gcd
   external gcd
   inverse
   Chinese Remainder Theorem
   Modline
   eulerphi
   eulerphi table        */

LL a[N],m[N],phi[N];
int n;

LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}

void exgcd(LL a,LL b,LL &d,LL &x,LL &y)
{
    if(!b){d=a;x=1;y=0;}
    else {exgcd(b,a%b,d,y,x);y-=x*(a/b);}
}

LL inv(LL a,LL n)
{
    LL d,x,y;
    exgcd(a,n,d,x,y);
    return d==1?(x+n)%n:-1;
}

LL china()
{
    int i;
    LL M=1,w,d,y,x=0;
    for(i=0;i<n;i++)M*=m[i];
    for(i=0;i<n;i++){
        w=M/m[i];
        exgcd(m[i],w,d,d,y);
        x=(x+y*a[i])%M;
    }
    return (x+M)%M;
}

LL Modline(int n)
{
    LL d,x,y,A,M,Mod;
    A=a[n-1],M=m[n-1];
    n--;
    // m1*x-m2*y=a2-a1
    while(n--){
        exgcd(M,m[n],d,x,y);
        if((A-a[n])%d!=0){
            return -1;
        }
        Mod=m[n]/d;
        x=(x*((a[n]-A)/d)%Mod+Mod)%Mod;
        A+=M*x;
        M=M/d*m[n];
    }
    return A;
}

LL eulerphi(LL n)
{
    int i,j;
    LL m,ans=n;
    m=(LL)sqrt(n+0.5);
    for(i=2;i<m && i<n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0)n/=i;
        }
    }
    if(n>1)ans=ans/n*(n-1);
    return ans;
}

void phitable(LL n)
{
    int i,j;
    for(i=0;i<=n;i++)phi[i]=0;
    phi[1]=1;
    for(i=2;i<=n;i++)if(!phi[i]){
        for(j=i;j<=n;j+=i){
            if(!phi[j])phi[j]=j;
            phi[j]=phi[j]/i*(i-1);
        }
    }
}
