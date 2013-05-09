/*   Kruskal   O( n*logn )
  求MST和次小生成树
  mst[][]生成树中的边
  d[][]生成树中两点的路径上的最长边  */


struct Edge{
    int u,v,w;
}e[N*N];
int p[N],vis[N],mst[N][N],d[N][N],w[N][N];
int n,m,mt;

int cmp(const Edge& a,const Edge& b)
{
    return a.w<b.w;
}

int find(int x){return p[x]==x?x:p[x]=find(p[x]);}

int Kruskal()
{
    int i,j,x,y,sum=0;
    for(i=1;i<=n;i++)p[i]=i;
    sort(e,e+m,cmp);
    mem(mst,0);
    for(i=0;i<m;i++){
        x=find(e[i].u);
        y=find(e[i].v);
        if(x!=y){
            sum+=e[i].w;
            p[y]=x;
        //    mst[e[i].u][e[i].v]=mst[e[i].v][e[i].u]=1;  //MST中的边
        }
    }
    return sum;
}

int dfs(int& s,int u,int max)   //求任意两点路径的最长边
{
    int v;
    for(v=1;v<=n;v++){
        if(mst[u][v] && !vis[v]){
            vis[v]=1;
            d[s][v]=Max(max,w[u][v]);
            dfs(s,v,d[s][v]);
        }
    }
    return 0;
}

int Second_MST()    //求次小生成树  O(n^2)
{
    int i,j,ret,t;
    sort(e,e+m,cmp);
    ret=Kruskal();
    for(i=0;i<=n;i++){
        mem(vis,0);vis[i]=1;
        dfs(i,i,0);
    }
    t=ret;
    for(i=0;i<m;i++){
        if(d[e[i].u][e[i].v]==e[i].w && !mst[e[i].u][e[i].v])
            ret=Min(ret,t+e[i].w-d[e[i].u][e[i].v]);
    }
    return ret;
}
