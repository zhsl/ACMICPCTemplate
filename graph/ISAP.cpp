/*
张浩是个二货。。。。
*/
/*  ISAP-当前弧优化+距离标号    O(V2E ?)
   n为图点的个数
   mt为边的条数，初始化0   */
   

struct Edge{
    int u,v,cap;
}e[N*N];

int first[N],next[N*N],d[N],cur[N],fa[N],num[N];
int n,m,S,T,mt;   //s,t分别为源点和汇点

void adde(int a,int b,int val)  //对于一条边，需建立双向边，一个容量为cap，反向边容量为0!
{
    e[mt].u=a;e[mt].v=b;
    e[mt].cap=val;
    next[mt]=first[a];first[a]=mt++;
    e[mt].u=b;e[mt].v=a;
    e[mt].cap=0;
    next[mt]=first[b];first[b]=mt++;
}
/*
void bfs()    // 初始化d[]，多次求解规模较小的网络流是，效率会有明显提升，注意注销掉isap()中的mem(d,0);!
{
    int x,i,j;
    queue<int> q;
    mem(d,-1);
    q.push(T);
    d[T]=0;
    while(!q.empty()){
        x=q.front();q.pop();
        for(i=first[x];i!=-1;i=next[i]){
            if(d[e[i].v]<0){
                d[e[i].v]=d[x]+1;
                q.push(e[i].v);
            }
        }
    }
}
*/

int augment()
{
    int x=T,a=INF;
    while(x!=S){
        a=Min(a,e[fa[x]].cap);
        x=e[fa[x]].u;
    }
    x=T;
    while(x!=S){
        e[fa[x]].cap-=a;
        e[fa[x]^1].cap+=a;
        x=e[fa[x]].u;
    }
    return a;
}

int isap()
{
    int i,x,ok,min,flow=0;
    mem(d,0);
    mem(num,0);
    num[0]=n;
    for(i=0;i<=n;i++)cur[i]=first[i];   //注意这里的边界 i<=n
    x=S;
    while(d[S]<n){
        if(x==T){
            flow+=augment();
            x=S;
        }
        ok=0;
        for(i=cur[x];i!=-1;i=next[i]){
            if(e[i].cap && d[x]==d[e[i].v]+1){
                ok=1;
                fa[e[i].v]=i;
                cur[x]=i;
                x=e[i].v;
                break;
            }
        }
        if(!ok){
            min=n-1;
            for(i=first[x];i!=-1;i=next[i])
                if(e[i].cap && d[e[i].v]<min)min=d[e[i].v];
            if(--num[d[x]]==0)break;
            num[d[x]=min+1]++;
            cur[x]=first[x];
            if(x!=S)x=e[fa[x]].u;
        }
    }
    return flow;
}
