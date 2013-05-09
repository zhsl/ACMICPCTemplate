/*   最小树形-朱刘算法  O( VE )  
   mt为边数                
   题目:POJ3146 
   http://www.cnblogs.com/zhsl/archive/2013/02/01/2888834.html  */


struct Edge{
    int u,v,w;
}e[N*N];
int pre[N],id[N],vis[N],minw[N];
int n,mt;

void adde(int a,int b,int c)
{
    e[mt].u=a,e[mt].v=b;e[mt].w=c;
    mt++;
}

int zhu_liu(int root)
{
    int i,cou,u,v,k;
    int ans=0;
    while(1)
    {
        //init
        mem(pre,-1);
        for(i=1;i<=n;i++)minw[i]=INF;
        for(i=0;i<mt;i++){
            u=e[i].u;
            v=e[i].v;
            if(e[i].w<minw[v] && u!=v){
                pre[v]=u;
                minw[v]=e[i].w;
            }
        }
        pre[root]=-1;minw[root]=0;
        for(cou=0,i=1;i<=n;i++)
            if(pre[i]==-1 && i!=root)cou++;
            else ans+=minw[i];
        if(cou)return -1;    //不存在最小树形图
        //cheack the circle
        mem(vis,0);
        mem(id,0);
        for(i=1,k=0;i<=n;i++){
            if(id[i])continue;
            u=i;
            while(u!=-1 && !id[u] && vis[u]!=i){
                vis[u]=i;
                u=pre[u];
            }
            if(u!=-1 && !id[u] && vis[u]==i){
                k++;
                while(id[u]!=k){
                    id[u]=k;
                    u=pre[u];
                }
            }
        }
        if(!k)break;
        for(i=1;i<=n;i++)if(!id[i])id[i]=++k;
        //eliminate circle
        for(i=0;i<mt;i++){
            e[i].w-=minw[e[i].v];
            e[i].u=id[e[i].u];
            e[i].v=id[e[i].v];
        }
        n=k;
        root=id[root];
    }
    return ans;
}
