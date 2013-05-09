/*   最小费用流   O(k*E)
   每次用SPFA扩展     */

struct Edge{
    int u,v,cap,w;
}e[N*N];

int d[N],first[N],next[N*N],inq[N],p[N];
int n,m,s,t,mt;

void adde(int a,int b,int c,int val){
    e[mt].u=a,e[mt].v=b,e[mt].cap=c,e[mt].w=val;
    next[mt]=first[a],first[a]=mt++;
    e[mt].u=b,e[mt].v=a,e[mt].cap=0,e[mt].w=-val;
    next[mt]=first[b],first[b]=mt++;
}

int Mincost()
{
    int i,j,x,a,cost=0;
    queue<int> q;
    p[s]=-1;
    while(1){
        a=INF;
        mem(d,0x3f);
        mem(inq,0);
        d[s]=0;
        q.push(s);
        while(!q.empty()){
            x=q.front();q.pop();
            inq[x]=0;
            for(i=first[x];i!=-1;i=next[i]){
                if(e[i].cap && d[e[i].u]+e[i].w<d[e[i].v]){
                    d[e[i].v]=d[e[i].u]+e[i].w;
                    p[e[i].v]=i;
                    if(!inq[e[i].v]){
                        q.push(e[i].v);
                        inq[e[i].v]=1;
                    }
                }
            }
        }
        if(d[t]==INF)break;
        for(i=p[t];i!=-1;i=p[e[i].u])
            if(e[i].cap<a)a=e[i].cap;
        for(i=p[t];i!=-1;i=p[e[i].u]){
            e[i].cap-=a;
            e[i^1].cap+=a;
        }
        cost+=d[t]*a;
    }
    return cost;
}
