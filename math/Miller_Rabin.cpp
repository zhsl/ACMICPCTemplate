/*   Miller Rabin b  */

/* （吉大模板)，poj验证超时，谨慎使用。
   CALL: bool res = miller(n); 
   快速测试n是否满足素数的'必要'条件, 出错概率很小; 
   对于任意奇数 n>2 和正整数 s, 算法出错概率 <= 2^(-s); 
   初始化时间种子：srand(time(NULL));      */
LL witness(LL a, LL n)
{
  LL x,d=1,i=ceil(log(n-1.0)/log(2.0))-1;
	for (;i>=0;i--){
		x=d;d=(d * d)%n;
		if (d==1 && x!=1 && x!=n-1) return 1;
		if (((n-1)&(1<<i))>0)d=(d*a)%n;
	}
	return d==1?0:1;
}

LL miller(LL n, LL s=50)
{
	if (n==2) return 1;
	if ((n%2)==0) return 0;
	int j,a;
	for (j=0;j<s;j++){
		a=rand()*(n-2)/RAND_MAX+1;
		// rand()只能随机产生[0, RAND_MAX)内的整数
		// 而且这个RAND_MAX只有32768直接%n的话永远也产生不了
		// [RAND-MAX, n)之间的数
		if (witness(a, n)) return 0;
	}
	return 1;
}


/*  网络模板，时间效率不错
  Miller_Rabin 算法进行素数测试
  速度快，而且可以判断 <2^63的数
  srand(time(NULL)); 需要time.h头文件  POJ上G++要去掉这句话
  const int S=20;  随机算法判定次数，S越大，判错概率越小
  计算 (a*b)%c.   a,b都是long long的数，直接相乘可能溢出的
  a,b,c <2^63                                           */
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
//计算  x^n %c
LL pow_mod(LL x,LL n,LL mod)//x^n%c
{
    if(n==1)return x%mod;
    x%=mod;
    LL tmp=x;
    LL ret=1;
    while(n)
    {
        if(n&1) ret=mult_mod(ret,tmp,mod);
        tmp=mult_mod(tmp,tmp,mod);
        n>>=1;
    }
    return ret;
}
//以a为基,n-1=x*2^t      a^(n-1)=1(mod n)  验证n是不是合数
//一定是合数返回true,不一定返回false
bool check(LL a,LL n,LL x,LL t)
{
    LL ret=pow_mod(a,x,n);
    LL last=ret;
    for(int i=1;i<=t;i++)
    {
        ret=mult_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1) return true;//合数
        last=ret;
    }
    if(ret!=1) return true;
    return false;
}

// Miller_Rabin()算法素数判定
//是素数返回true.(可能是伪素数，但概率极小)
//合数返回false;
bool Miller_Rabin(LL n)
{
    if(n<2)return false;
    if(n==2)return true;
    if((n&1)==0) return false;//偶数
    LL x=n-1;
    LL t=0;
    while((x&1)==0){x>>=1;t++;}
    for(int i=0;i<S;i++)
    {
        LL a=rand()%(n-1)+1;//rand()需要stdlib.h头文件
        if(check(a,n,x,t))
            return false;//合数
    }
    return true;
}
