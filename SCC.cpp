/*   SCC   O(E)
   tarjan算法
   sccno[]强连通集合,用编号标示    */

struct Edge{
    int u,v;
}e[N*N];
int first[N],next[N*N],pre[N],sccno[N],low[N];
int n,mt,dfs_clock,scnt;
stack<int> s;

void adde(int a,int b)
{
    e[mt].u=a;e[mt].v=b;
    next[mt]=first[a],first[a]=mt++;
}

void dfs(int u)
{
    int i,j,v;
    pre[u]=low[u]=++dfs_clock;
    s.push(u);
    for(i=first[u];i!=-1;i=next[i]){
        v=e[i].v;
        if(!pre[v]){
            dfs(v);
            low[u]=Min(low[u],low[v]);
        }
        else if(!sccno[v]){    //反向边更新
            low[u]=Min(low[u],low[v]);
        }
    }
    if(low[u]==pre[u]){   //存在强连通分量
        int x=-1;
        scnt++;
        while(x!=u){
            x=s.top();s.pop();
            sccno[x]=scnt;
        }
    }
}

void find_scc()
{
    int i;
    mem(pre,0);mem(sccno,0);
    scnt=dfs_clock=0;
    for(i=1;i<=n;i++){
        if(!pre[i])dfs(i);
    }
}
