/*   Kuhn-Munkers   O(n^3) | O(n^4)
  邻接矩阵实现          */




/*   O(n^4) 实际效果没这么遭   */
int w[N][N],lx[N],ly[N],S[N],T[N],y[N];
int n,m;

int dfs(int u)
{
    S[u]=1;
    int v;
    for(v=0;v<n;v++){
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
}
void update()
{
    int i,j,min;
    min=INF;
    for(i=0;i<n;i++)if(S[i])
        for(j=0;j<n;j++)if(!T[j])
            min=Min(min,w[i][j]-lx[i]-ly[j]);
    for(i=0;i<n;i++){
        if(S[i])lx[i]-=min;
        if(T[i])ly[i]+=min;
    }
}
}
void KM()
{
    mem(y,-1);
    mem(ly,0);
    int i,j;
    for(i=0;i<n;i++){
        lx[i]=0;
        for(j=0;j<n;j++)
            if(w[i][j]>lx[i])lx[i]=w[i][j];
    }
    for(i=0;i<n;i++){
        while(1){
            mem(S,0);mem(T,0);
            if(dfs(i))break;
            update();
        }
    }
}
