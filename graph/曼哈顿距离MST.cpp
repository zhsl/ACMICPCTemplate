/*   曼哈顿   O(n*logn)
  性质：对于某个点，以他为中心的区域分为8个象限，对于每一个象限，只会取距离最近的一个点连边。
坐标变化：
   R1->R2：关于y=x对称，swap(x,y)
   R2->R3：考虑到代码的方便性，我们考虑R2->R7，x=-x。
   R7->R4：因为上面求的是R2->R7，因此这里还是关于y=x对称。   */
  

const int INF=0x3f3f3f3f;
   
struct Point{
    int x,y,id;
    bool operator<(const Point p)const{
        return x!=p.x?x<p.x:y<p.y;
    }
}p[N];
struct BIT{
    int min_val,pos;
    void init(){
        min_val=INF;
        pos=-1;
    }
}bit[N];
struct Edge{
    int u,v,d;
    bool operator<(const Edge e)const{
        return d<e.d;
    }
}e[N<<2];
int T[N],hs[N];
int n,mt,pre[N];

void adde(int u,int v,int d)
{
    e[mt].u=u,e[mt].v=v;
    e[mt++].d=d;
}

int find(int x)
{
    return pre[x]=(x==pre[x]?x:find(pre[x]));
}
int dist(int i,int j)
{
    return abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y);
}

inline int lowbit(int x)
{
    return x&(-x);
}

void update(int x,int val,int pos)
{
    for(int i=x;i>=1;i-=lowbit(i))
        if(val<bit[i].min_val)
            bit[i].min_val=val,bit[i].pos=pos;
}

int query(int x,int m)
{
    int min_val=INF,pos=-1;
    for(int i=x;i<=m;i+=lowbit(i))
        if(bit[i].min_val<min_val)
            min_val=bit[i].min_val,pos=bit[i].pos;
    return pos;
}

int Manhattan_minimum_spanning_tree(int n,Point *p,int K)
{
    int i,w,dir,fa,fb,pos,m;
    //Build graph
    mt=0;
    for(dir=0;dir<4;dir++){
        //Coordinate transform - reflect by y=x and reflect by x=0
        if(dir==1||dir==3){
            for(i=0;i<n;i++)
                swap(p[i].x,p[i].y);
        }
        else if(dir==2){
            for(i=0;i<n;i++){
                p[i].x=-p[i].x;
            }
        }
        //Sort points according to x-coordinate
        sort(p,p+n);
        //Discretize
        for(i=0;i<n;i++){
            T[i]=hs[i]=p[i].y-p[i].x;
        }
        sort(hs,hs+n);
        m=unique(hs,hs+n)-hs;
        //Initialize BIT
        for(i=1;i<=m;i++)
            bit[i].init();
        //Find points and add edges
        for(i=n-1;i>=0;i--){
            pos=lower_bound(hs,hs+m,T[i])-hs+1;   //BIT中从1开始'
            w=query(pos,m);
            if(w!=-1)
                adde(p[i].id,p[w].id,dist(i,w));
            update(pos,p[i].x+p[i].y,i);
        }
    }
    //Kruskal - 找到第K小的边
    sort(e,e+mt);
    for(i=0;i<n;i++)pre[i]=i;
    for(i=0;i<mt;i++){
        fa=find(e[i].u),fb=find(e[i].v);
        if(fa!=fb){
            K--;pre[fa]=fb;
            if(K==0)return e[i].d;
        }
    }
}
