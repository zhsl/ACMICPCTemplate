/*    二分匹配-dfs   O(E)
  最小点集覆盖 = 最大匹配数
  最小路径覆盖 = n - 最大匹配数
  最大独立集 = n - 最大匹配数      */

/*   邻接表 - 对于稀疏图效果好   */
struct Edge{
    int u,v;
}e[N*N];

int vis[N],y[N],first[N],next[N*N];
int n,mt;

void adde(int a,int b)
{
    e[mt].u=a;e[mt].v=b;
    next[mt]=first[a];first[a]=mt++;
}

int dfs(int u)
{
    int i,v;
    for(i=first[u];i!=-1;i=next[i]){
        v=e[i].v;
        if(!vis[v]){
            vis[v]=1;
            if(y[v]==-1 || dfs(y[v])){
                y[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int match()
{
    int i,cnt=0;
    mem(y,-1);
    for(i=0;i<n;i++){
        mem(vis,0);
        if(dfs(i))cnt++;
    }
    return cnt;
}


/*   邻接矩阵   O(n^2)  */
int vis[N],y[N],g[N][N];
int n;

int dfs(int u)
{
    int v;
    for(v=0;v<n;v++){
        if(g[u][v] && !vis[v]){
            vis[v]=1;
            if(y[v]==-1 || dfs(y[v])){
                y[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int match()
{
    int i,cnt=0;
    mem(y,-1);
    for(i=0;i<n;i++){
        mem(vis,0);
        if(dfs(i))cnt++;
    }
    return cnt;
}
