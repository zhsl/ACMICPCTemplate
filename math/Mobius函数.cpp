\subsection{Mobius函数}
	\begin{verbatim}

/*     Mobius函数   O(n)
Mobius反演定理
　已知 f(n) = sigma(d|n, g(d))
　　　　那么 g(n) = sigma(d|n, mu(d)*f(n/d))
　还有另一种形式更常用：
　　　在某一范围内，已知 f(n) = sigma(n|d, g(d))
　　　那么 g(n) = sigma(n|d, mu(d/n)*f(d))
　　　
Mobius函数：
          1        n=1
  mu(n)= (-1)^k    n=p1*p2*...*pk, pi为不相同的质数
          0        others                           */

int isprime[N],mu[N],prime[N];
int cnt;
void Mobius(int n)
{
    int i,j;
    //Init isprime[N],mu[N],prime[N],全局变量初始为0
    cnt=0;mu[1]=1;
    for(i=2;i<=n;i++){
        if(!isprime[i]){
            prime[cnt++]=i;
            mu[i]=-1;
        }
        for(j=0;j<cnt && i*prime[j]<=n;j++){
            isprime[i*prime[j]]=1;
            if(i%prime[j])
                mu[i*prime[j]]=-mu[i];
            else {mu[i*prime[j]]=0;break;}
        }
    }
}
          \end{verbatim}
