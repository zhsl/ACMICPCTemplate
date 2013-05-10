/*  动态连续上升子序列   O( n*Logn ) 
   线段树维护
   update()修改数列中位置为a的数为b
   query()访问[a,b]区间的LCIS
   ans为询问后答案,anst为query()时,临时记录的最长长度,每次询问前要初始话ans=anst=0   */


struct Node{
    int maxl,max,maxr;
}ret[N<<2];
int num[N];
int n,m,a,b,ans,anst;

void pushup(int rt,int lnum,int rnum,int lenl,int lenr)
{
    ret[rt].max=max(ret[rt<<1].max,ret[rt<<1|1].max);
    ret[rt].maxl=ret[rt<<1].maxl;
    ret[rt].maxr=ret[rt<<1|1].maxr;
    if(lnum<rnum){
        ret[rt].max=max(ret[rt].max,ret[rt<<1].maxr+ret[rt<<1|1].maxl);
        if(ret[rt<<1].max==lenl)
            ret[rt].maxl+=ret[rt<<1|1].maxl;
        if(ret[rt<<1|1].max==lenr)
            ret[rt].maxr+=ret[rt<<1].maxr;
    }
}

void build(int l,int r,int rt)
{
    if(l==r){
        ret[rt].max=ret[rt].maxl=ret[rt].maxr=1;
        return;
    }
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
    pushup(rt,num[mid],num[mid+1],mid-l+1,r-mid);
}

void update(int l,int r,int rt)
{
    if(l==r){
        num[l]=b;
        return;
    }
    int mid=(l+r)>>1;
    if(a<=mid)update(lson);
    else update(rson);
    pushup(rt,num[mid],num[mid+1],mid-l+1,r-mid);
}

void query(int l,int r,int rt)
{
    if(a<=l && r<=b){
        if(ret[rt].max>ans)
            ans=ret[rt].max;
        if(anst){
            if(num[l]>num[l-1]){
                if(ret[rt].max==r-l+1)
                    anst+=ret[rt].max;
                else {
                    anst+=ret[rt].maxl;
                    if(anst>ans)ans=anst;
                    anst=ret[rt].maxr;
                }
            }
            if(anst>ans)
                ans=anst;
            if(num[l]<=num[l-1])
                anst=ret[rt].maxr;
        }
        else
            anst=ret[rt].maxr;
        return;
    }
    int mid=(l+r)>>1;
    if(a<=mid)query(lson);
    if(b>mid)query(rson);
}
