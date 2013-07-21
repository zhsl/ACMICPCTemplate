/*   Kuhn-Munkers   O(n^3) | O(n^4)
   邻接矩阵实现       
   维护可行顶标 l(x)+l(y)>=w(x,y)
   S[]=T[]=1,是匈牙利树的点集合
   如果求最小权匹配,维护l(x)+l(y)<=w(x,y)即可  */

/*     O(n^3)   最大权匹配   */
int w[N][N],S[N],T[N],lx[N],ly[N],y[N];
int n,slack;

int match(int u)
{
    int v,t;
    S[u]=1;
    for(v=1;v<=n;v++){
        t=lx[u]+ly[v]-w[u][v];
        if(!t){
            if(!T[v]){
                T[v]=1;
                if(y[v]==-1 || match(y[v])){
                    y[v]=u;
                    return 1;
                }
            }
        }
        else if(t<slack)slack=t;
    }
    return 0;
}

void KM()
{
    int i,j,a;
    mem(y,-1);
    mem(ly,0);
    for(i=1;i<=n;i++){
        lx[i]=w[i][1];
        for(j=2;j<=n;j++)
            if(w[i][j]>lx[i])lx[i]=w[i][j];
    }
    for(i=1;i<=n;i++){
        while(1){
            slack=INF;
            mem(S,0);mem(T,0);
            if(match(i))break;
            for(j=1;j<=n;j++){
                if(S[j])lx[j]-=slack;
                if(T[j])ly[j]+=slack;
            }
        }
    }
}

/*   O(n^4) 最大权匹配  实际效果没这么遭   */
int w[N][N],lx[N],ly[N],S[N],T[N],y[N];
int n,m;

int dfs(int u)
{
    S[u]=1;
    int v;
    for(v=1;v<=n;v++){
        if(w[u][v]==lx[u]+ly[v] && !T[v]){
            T[v]=1;
            if(y[v]==-1 || dfs(y[v])){
                y[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

void update()
{
    int i,j,a;
    a=INF;
    for(i=1;i<=n;i++)if(S[i])
        for(j=1;j<=n;j++)if(!T[j])
            a=Min(a,lx[i]+ly[j]-w[i][j]);
    for(i=1;i<=n;i++){
        if(S[i])lx[i]-=a;
        if(T[i])ly[i]+=a;
    }
}

void KM()
{
    mem(y,-1);
    mem(ly,0);
    int i,j;
    for(i=1;i<=n;i++){
        lx[i]=w[i][1];
        for(j=2;j<=n;j++)
            if(w[i][j]>lx[i])lx[i]=w[i][j];
    }
    for(i=1;i<=n;i++){
        while(1){
            mem(S,0);mem(T,0);
            if(dfs(i))break;
            update();
        }
    }
}


