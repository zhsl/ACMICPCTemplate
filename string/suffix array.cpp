/*   suffix array
   倍增算法   O(n*lgn)   
   build_sa( ,n+1, )   注意n+1
   getHeight( , n)

 n        =  8 ；
 num[]    = { 1, 1, 2, 1, 1, 1, 1, 2, $ }.   注意num数组最后一位值为0，其它位须大于0!
 rank[]   = { 4, 6, 8, 1, 2, 3, 5, 7, 0 }.   (rank[0~n-1]为有效值)
 sa[]     = { 8, 3, 4, 5, 0, 6, 1, 7, 2 }.   (sa[1~n]为有效值)
 height[] = { 0, 0, 3, 2, 3, 1, 2, 0, 1 }.   (height[2~n]为有效值)    */


int sa[N],t1[N],t2[N],c[N],rank[N],height[N];
int n,m;

void build_sa(int s[],int n,int m)
{
    int i,k,p,*x=t1,*y=t2;
    //第一轮基数排序
    for(i=0;i<m;i++)c[i]=0;
    for(i=0;i<n;i++)c[x[i]=s[i]]++;
    for(i=1;i<m;i++)c[i]+=c[i-1];
    for(i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
    for(k=1;k<=n;k<<=1){
        p=0;
        //直接利用sa数组排序第二关键字
        for(i=n-k;i<n;i++)y[p++]=i;
        for(i=0;i<n;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
        //基数排序第一关键字
        for(i=0;i<m;i++)c[i]=0;
        for(i=0;i<n;i++)c[x[y[i]]]++;
        for(i=1;i<m;i++)c[i]+=c[i-1];
        for(i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
        //根据sa和x数组计算新的x数组
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(i=1;i<n;i++)
            x[sa[i]]=y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
        if(p>=n)break;   //已经排好序，直接退出
        m=p;     //下次基数排序的最大值
    }
}

void getHeight(int s[],int n)
{
    int i,j,k=0;
    for(i=0;i<=n;i++)rank[sa[i]]=i;
    for(i=0;i<n;i++){
        if(k)k--;
        j=sa[rank[i]-1];
        while(s[i+k]==s[j+k])k++;
        height[rank[i]]=k;
    }
}