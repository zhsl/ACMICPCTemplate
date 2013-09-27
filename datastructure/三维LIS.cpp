/*   三维LIS  O(n*lognlogn)
  (x,y,z)<=(x,y,z)
  分治算法
  ans.first为长度，ans.second为方法数    */
  
const int N=100010;

struct Node{
    int x,y,z,id;
    bool operator <(const Node& a)const{
        return x!=a.x?x<a.x:(y!=a.y?y<a.y:z<a.z);
    }
}a[N],b[N];
pii f[N],bit[N];
int z[N];
int T,n,m;

#define lowbit(x) (x&-x)

void update(pii& a,pii& b)
{
    if(b.first>a.first)a=b;
    else if(b.first==a.first){
        a.second+=b.second;
    }
}

void add(int x,pii& b)
{
    for(;x<=m;x+=lowbit(x)){
        update(bit[x],b);
    }
}

pii query(int x)
{
    pii ret=make_pair(0,0);
    for(;x>0;x-=lowbit(x)){
        update(ret,bit[x]);
    }
    return ret;
}

void clear(int x)
{
    for(;x<=m;x+=lowbit(x)){
        bit[x]=make_pair(0,0);
    }
}

void solve(int l,int r)
{
    if(l==r)return;
    int i,j,k,mid,cnt=0;
    mid=(l+r)>>1;
    solve(l,mid);
    for(i=l;i<=r;i++){
        b[cnt]=a[i];
        b[cnt++].x=0;
    }
    sort(b,b+cnt);
    for(i=0;i<cnt;i++){
        if(b[i].id<=mid){
            add(b[i].z,f[b[i].id]);
        }
        else {
            pii t=query(b[i].z);
            t.first++;
            update(f[b[i].id],t);
        }
    }
    for(i=0;i<cnt;i++){
        if(b[i].id<=mid)
            clear(b[i].z);
    }
    solve(mid+1,r);
}

int main()
{
    freopen("in.txt","r",stdin);
    int i,j;
    pii ans;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++){
            scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
            z[i]=a[i].z;
        }

        sort(a,a+n);
        sort(z,z+n);
        m=unique(z,z+n)-z;
        for(i=0;i<n;i++){
            f[i]=make_pair(1,1);
            a[i].id=i;
            a[i].z=lower_bound(z,z+m,a[i].z)-z+1;
        }
        solve(0,n-1);
        ans=make_pair(0,0);
        for(i=0;i<n;i++){
            update(ans,f[i]);
        }

        printf("%d %d\n",ans.first,ans.second);
    }
    return 0;
}
