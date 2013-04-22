/*  划分树   O(n*logn)
  s[]是数列的前缀和
  val[]是输入的数列，然后sort排序
  num[u+1][]存的是u层划分后的数字 (类似快排Partation （d-1）次后的结果)
  cnt[u][i]是统计在当前区间第i个数之前(包括第i个数)放到左区间的数的个数
  sum[u][i]是求在当前区间第i个数之前(包括第i个数)放到左区间的数和   
  注意：每次询问前初始化 ksum=0              */


int val[N],num[20][N],cnt[20][N];
LL sum[20][N],s[N];
int knum;
LL ksum;

void build(int u,int l,int r)
{
    if(l==r){
        sum[u][l]=num[u][l];
        return;
    }
    int i,mid,midnum,kl,kr,lsame;
    LL s=0;
    mid=(l+r)>>1;
    kl=l;kr=mid+1;lsame=mid-l+1;
    midnum=val[mid];
    for(i=l;i<=mid;i++)   //注意这里需要统计等于中位数放在左儿子区间的个数
        if(val[i]<midnum)lsame--;
    for(i=l;i<=r;i++){
        if(num[u][i]<midnum || (num[u][i]==midnum && lsame)){  //注意等于中位数情况
            if(num[u][i]==midnum)lsame--;
            num[u+1][kl++]=num[u][i];
            sum[u][i]=s+(LL)num[u][i];
            s=sum[u][i];
        }
        else {
            num[u+1][kr++]=num[u][i];
            sum[u][i]=s;
        }
        cnt[u][i]=kl-l;
    }
    build(u+1,l,mid);
    build(u+1,mid+1,r);
}

void query(int u,int l,int r,int a,int b,int k)
{
    if(a==b){   //注意这里可能l<r啦
        knum=num[u][a];   
        ksum+=num[u][a];
        return;
    }
    int i,t,mid,cnta;
    mid=(l+r)>>1;
    cnta=(a>l?cnt[u][a-1]:0);   //注意l==a
    t=cnt[u][b]-cnta;
    if(k<=t){
        query(u+1,l,mid,l+cnta,l+cnt[u][b]-1,k);
    }
    else{
        ksum+=sum[u][b]-(a>l?sum[u][a-1]:0);
        query(u+1,mid+1,r,mid+a-l-cnta+1,mid+b-l-cnt[u][b]+1,k-t);
    }
}
