/*  POJ-1160   */
 
int ma[N][N];
LL f[2][1<<N];
int T,n,m;
 
int main()
{
 //   freopen("in.txt","r",stdin);
    int i,j,k,x,y,up,icase=0,p;
    scanf("%d",&T);
    while(T--)
    {
        mem(f,0);
        scanf("%d%d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                scanf("%d",&ma[i][j]);
        f[0][0]=p=1;
        up=1<<(m+1);
        for(i=0;i<n;i++,mem(f[p=!p],0)){
            for(j=0;j<m;j++,mem(f[p=!p],0)){
                x=1<<j;
                y=1<<(j+1);
                for(k=0;k<up;k++){
                    if(ma[i][j]){
                        f[p][k^x^y]+=f[!p][k];
                        if((k&x) && (k&y))continue;
                        if((k&x)^(k&y))f[p][k]+=f[!p][k];
                    }
                    else if(!(k&x) && !(k&y)){
                        f[p][k]+=f[!p][k];
                    }
                }
            }
            for(j=0;j<(1<<m);j++)f[p][j<<1]=f[!p][j];
        }
 
        printf("Case %d: There are %I64d ways to eat the trees.\n",++icase,f[!p][0]);
    }
    return 0;
}