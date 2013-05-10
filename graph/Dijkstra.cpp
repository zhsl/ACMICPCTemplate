/* Dijkstra O(E * log V)
  p[]为路径数组
  不能处理负权图     */

struct Edge{
    int u,v,w;
}e[2*N];
int first[N],next[2*N],p[N],d[N];
int T,n,m,mt;

void adde(int a,int b,int c)
{
    e[mt].u=a,e[mt].v=b;e[mt].w=c;
    next[mt]=first[a],first[a]=mt++;
    e[mt].u=b,e[mt].v=a;e[mt].w=c;
    next[mt]=first[b],first[b]=mt++;
}

int dijkstra(int s)   //s is start
{
    int i,u,cou=0;
    pii t;
    priority_queue<pii,vector<pii>,greater<pii> > q;
    mem(d,INF);d[s]=0;
    q.push(make_pair(d[s],s));
    while(!q.empty()){
        t=q.top();q.pop();
        u=t.second;
        if(t.first!=d[u])continue;
        cou++;
        for(i=first[u];i!=-1;i=next[i]){
            if(d[u]+e[i].w<d[e[i].v]){
                d[e[i].v]=d[u]+e[i].w;
                p[e[i].v]=i;
                q.push(make_pair(d[e[i].v],e[i].v));
            }
        }
    }
    return cou;
}
