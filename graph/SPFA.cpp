/*   SPFA  O(k*E)
   对于一般稀疏图,k=2~3.稠密图最坏情况可达到O(V^2)
   如果存在负权环返回1,否则返回0    */

struct Edge{
  int u,v,w;
}e[N*N];

int first[N],next[N*N],inq[N],d[N],cnt[N];
int n,m,mt;

int spfa(int s)
{
	int i,u,v,t;
	queue<int> q;
	mem(d,INF);
	mem(cnt,0);
	q.push(s);
	d[s]=0;cnt[s]=1;
	while(!q.empty()){
		u=q.front();q.pop();
		inq[u]=0;
		for(i=first[u];i!=-1;i=next[i]){
			v=e[i].v;t=d[u]+e[i].w;
			if(t<d[v]){
				d[v]=t;
				if(!inq[v]){
					if(++cnt[v]>=n)return 1;
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
	return 0;
}

