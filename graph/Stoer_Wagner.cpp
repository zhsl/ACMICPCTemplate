/*    Stoer_Wagner  O(n^3)  (POJ 2914)
   求无向图的最小割,把图分为两个子图的最小花费
   邻接矩阵建图,w[][]点从0开始
   算法流程:
     1.min=MAXINT，固定一个顶点P
     2.从点P用“类似”prim的s算法扩展出“最大生成树”，记录最后扩展的顶点和最后扩展的边
     3.计算最后扩展到的顶点的切割值（即与此顶点相连的所有边权和），若比min小更新min
     4.合并最后扩展的那条边的两个端点为一个顶点（当然他们的边也要合并，这个好理解吧？）
     5.转到2，合并N-1次后结束
     6.min即为所求，输出min
   prim本身复杂度是O(n^2)，合并n-1次，算法复杂度即为O(n^3)
   如果在prim中加堆优化，复杂度会降为O((n^2)logn)            */

int w[N][N];
int v[N], dis[N];
bool vis[N];
int n,m;

int Stoer_Wagner(int n){
    int i, j, res = INF;
    for(i = 0; i < n; i ++)
        v[i] = i;
    while(n > 1){
        int k = 1, pre = 0;
        for(i = 1; i < n; i ++){
            dis[v[i]] = w[v[0]][v[i]];
            if(dis[v[i]] > dis[v[k]])
                k = i;
        }
        memset(vis, 0, sizeof(vis));
        vis[v[0]] = true;
        for(i = 1; i < n; i ++){
            if(i == n-1){
                res = min(res, dis[v[k]]);
                for(j = 0; j < n; j ++){
                    w[v[pre]][v[j]] += w[v[j]][v[k]];
                    w[v[j]][v[pre]] += w[v[j]][v[k]];
                }
                v[k] = v[-- n];
            }
            vis[v[k]] = true;
            pre = k;
            k = -1;
            for(j = 1; j < n; j ++)
                if(!vis[v[j]]){
                    dis[v[j]] += w[v[pre]][v[j]];
                    if(k == -1 || dis[v[k]] < dis[v[j]])
                        k = j;
                }
        }
    }
    return res;
}
