/*    Twosat    */


/*   dfs  O(VE)   */
int first[N],next[N*N*2],vis[N],S[N];
int n,mt,cnt;

struct Edge{
    int u,v;
}e[N*N*2];

void adde(int a,int b)
{
    e[mt].u=a,e[mt].v=b;
    next[mt]=first[a];first[a]=mt++;
}

int dfs(int u)
{
    if(vis[u^1])return 0;
    if(vis[u])return 1;
    int i;
    vis[u]=1;
    S[cnt++]=u;
    for(i=first[u];i!=-1;i=next[i]){
        if(!dfs(e[i].v))return 0;
    }
    return 1;
}

int Twosat()
{
    int i,j;
    for(i=0;i<n;i+=2){
        if(vis[i] || vis[i^1])continue;
        cnt=0;
        if(!dfs(i)){
            while(cnt)vis[S[--cnt]]=0;
            if(!dfs(i^1))return 0;
        }
    }
    return 1;
}

void init(double limt)
{
    int i,j;
    mt=0;mem(vis,0);
    mem(first,-1);
  /* 
    建图
  */
}


