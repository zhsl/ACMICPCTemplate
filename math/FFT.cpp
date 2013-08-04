/*  FFT    O(n*logn)   
 多项式转化为点值表示法,利用n次单位复根来分治运算
 例如做大数乘法：
    1.得到向量a,b  DFT
    2.a,b作一次乘积得到向量c
    3.向量c作FFT   IDFT
    4.转化结果                       */


//定义复试结构体
struct complex
{
    double r,i;
    complex(double _r = 0.0,double _i = 0.0){r = _r; i = _i;}
    complex operator +(const complex &b){return complex(r+b.r,i+b.i);}
    complex operator -(const complex &b){return complex(r-b.r,i-b.i);}
    complex operator *(const complex &b){return complex(r*b.r-i*b.i,r*b.i+i*b.r);}
};
/*
 * 进行FFT和IFFT前的反转变换。
 * 位置i和 （i二进制反转后位置）互换
 * len必须去2的幂
 */
void change(complex y[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2;i < len-1; i++)
    {
        if(i < j)swap(y[i],y[j]);
        //交换互为小标反转的元素，i<j保证交换一次
        //i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        k = len/2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
/*
 * 做FFT
 * len必须为2^k形式，
 * on==1时是DFT，on==-1时是IDFT
 */
void FFT(complex y[],int len,int on)
{
    change(y,len);
    for(int h = 2; h <= len; h <<= 1)
    {
        complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j+=h)
        {
            complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                complex u = y[k];
                complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}

/*  大数乘法
char s1[N],s2[N];
int ans[N];
complex a[N],b[N];

int main(){
  //  freopen("in.txt","r",stdin);
    int i,j,len1,len2,len;
    while(~scanf("%s%s",s1,s2))
    {
        len1=strlen(s1);
        len2=strlen(s2);
        len=1;
        while(len<(len1<<1) || len<(len2<<1))len<<=1;
        for(i=0;i<len1;i++)a[i]=complex(s1[len1-i-1]-'0',0);
        for(;i<len;i++)a[i]=complex(0,0);
        for(i=0;i<len2;i++)b[i]=complex(s2[len2-i-1]-'0',0);
        for(;i<len;i++)b[i]=complex(0,0);

        FFT(a,len,1);
        FFT(b,len,1);
        for(i=0;i<len;i++)a[i]=a[i]*b[i];
        FFT(a,len,-1);
        for(i=0;i<len;i++)ans[i]=(int)(a[i].r+0.5);
        len=len1+len2-1;
        for(i=0;i<len;i++){
            ans[i+1]+=ans[i]/10;
            ans[i]%=10;
        }
        for(i=len;ans[i]<=0 && i>0;i--);
        for(;i>=0;i--)
            printf("%d",ans[i]);
        putchar('\n');
    }
    return 0;
}
*/
