/*   Dinic    O(min(n^(2/3)*m, m^(1/2)) * m)
   对于二分图,复杂度O(n^(1/2) * m)
   构造层次图,然后在层次图上DFS找增光路,路径 d[u]=d[v]+1
   加当前弧优化,效率提高           */

struct Edge{
    int u,v,cap;
}e[N*N];

int first[N],next[N*N],d[N],cur[N];
int n,m,s,t,mt;

void adde(int a,int b,int val)
{
    e[mt].u=a;e[mt].v=b;
    e[mt].cap=val;
    next[mt]=first[a];first[a]=mt++;
    e[mt].u=b;e[mt].v=a;
    e[mt].cap=0;
    next[mt]=first[b];first[b]=mt++;
}

int bfs()
{
    int x,i,j;
    queue<int> q;
    mem(d,0);
    q.push(s);
    d[s]=1;
    while(!q.empty()){
        x=q.front();q.pop();
        for(i=first[x];i!=-1;i=next[i]){
            if(e[i].cap && !d[e[i].v]){
                d[e[i].v]=d[x]+1;
                q.push(e[i].v);
            }
        }
    }
    return d[t];
}

int dfs(int x,int a)
{
    if(x==t || a==0)return a;
    int f,flow=0;
    for(int& i=cur[x];i!=-1;i=next[i]){      //当前弧优化,从上次的弧考虑
        if(d[x]+1==d[e[i].v] && (f=dfs(e[i].v,Min(a,e[i].cap)))){
            e[i].cap-=f;
            e[i^1].cap+=f;
            flow+=f;
            a-=f;
            if(!a)break;
        }
    }
    return flow;
}

int dinic()
{
    int i,flow=0;
    while(bfs()){
        for(i=0;i<=t;i++)cur[i]=first[i];
        flow+=dfs(s,INF);
    }
    return flow;
}
