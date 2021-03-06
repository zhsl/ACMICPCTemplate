\subsection{数学基础}
	\begin{verbatim}
/*  number theory basic
  -gcd
  -external gcd
  -inverse
  -Chinese Remainder Theorem
  -Modline
  -primetable
  -eulerphi
  -eulerphi table        */

LL a[N],m[N],phi[N];
int n;

LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}

//求出来的(x,y),有|x|+|y|最小
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

//求ax = 1( mod m) 的x值，就是逆元(0<a<m)
LL inv(LL a,LL m)
{
    if(a == 1)return 1;
    return inv(m%a,m)*(m-m/a)%m;
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

/*  primetable  O(n)  
 isprime[i]=0为素数
 prime存储素数
 cnt为素数个数     */
int isprime[N],prime[N];
int cnt;
void primetable(int n)
{
    int i,j;
    //Init isprime[N],prime[N],全局变量初始为0
    cnt=0;isprime[1]=1;
    for(i=2;i<=n;i++){
        if(!isprime[i])prime[cnt++]=i;
        for(j=0;j<cnt && i*prime[j]<=n;j++){
            isprime[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
}

LL eulerphi(LL n)
{
    int i,j;
    LL m,ans=n;
    m=(LL)sqrt(n+0.5);
    for(i=2;i<=m && i<n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0)n/=i;
        }
    }
    if(n>1)ans=ans/n*(n-1);
    return ans;
}

/*   eulerphi table O(n)算法
 效率是下面那个phitable的3-4倍！  O(n)
 主要是递推优化：
    如果i%prime[j]，那么phi[i*prime[j]]=n(p1-1)/p1*...(pn-1)/pn*(prime[j]-1)/prime[j]*prime[j]=phi[i]*(prime[j]-1)
    否则：phi[i*prime[j]]=n(p1-1)/p1*...(pn-1)/pn*prime[j]=phi[i]*(prime[j]-1)
prime存储素数
cnt为1-n之间的素数个数   */
int phi[N],prime[N];
int cnt;
void phitable(int n)
{
    int i,j;
    //Init phi[N],prime[N],全局变量初始为0
    cnt=0;phi[1]=1;
    for(i=2;i<=n;i++){
        if(!phi[i]){
            prime[cnt++]=i;  //prime[i]=1;为素数表
            phi[i]=i-1;
        }
        for(j=0;j<cnt && i*prime[j]<=n;j++){
            if(i%prime[j])
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            else {phi[i*prime[j]]=phi[i]*prime[j];break;}
        }
    }
}

/*  eulerphi table  朴素算法O(n*loglogn)   */
int phi[N],isprime[N];
void phitable(int n)
{
    int i,j;
    //Init phi[N],isprime[N],全局变量初始为0
    phi[1]=1;
    for(i=2;i<=n;i++)if(!phi[i]){
      //  isprime[i]=1;   //筛质数，isprime[i]=1为质数
        for(j=i;j<=n;j+=i){
            if(!phi[j])phi[j]=j;
            phi[j]=phi[j]/i*(i-1);
        }
    }
}
	\end{verbatim}
