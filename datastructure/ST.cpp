/*    ST   预处理O( n*logn )  查询O( 1 )
   d[i][j]为区间[i,i+2^j-1]的最值
   d[i][j]=Min( d[i][j-1], d[i+(1<<(j-1))][j-1] )   */
  

struct ST
{
    int n;
    int num[N],d[N][20];
    
    void rmq_init(int n)
    {
        int i,j;
        for(i=1;i<=n;i++)d[i][0]=num[i];
        for(j=1;(1<<j)<=n;j++){
            for(i=1;i+(1<<j)-1<=n;i++){
                d[i][j]=Min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int rmq(int l,int r)
    {
        int k=0;
        while((1<<(k+1))<=r-l+1)k++;
        return Min(d[l][k],d[r-(1<<k)+1][k]);
    }
}st;
