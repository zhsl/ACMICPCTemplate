/*  插头DP 最小表示法 求哈密顿回路数
   g[][]为图
   如果TLE，可调节Hash表大小    */

const int N=15,INF=0x3f3f3f3f,MOD=4001,STA=1000010;

int g[N][N],code[N],ma[N];
int n,m,ex,ey;

struct Hash{     //Hash表,MOD为表长,STA为表大小
    int first[MOD],next[STA],size;
    LL f[STA],sta[STA];
    void init(){
        size=0;
        mem(first,-1);
    }
    void add(LL st,LL ans){
        int i,u=st%MOD;
        for(i=first[u];i!=-1;i=next[i]){
            if(sta[i]==st){
                f[i]+=ans;
                return;
            }
        }
        sta[size]=st;
        f[size]=ans;
        next[size]=first[u];
        first[u]=size++;
    }
}hs[2];

void shift(int p)    //换行移位
{
    int k;
    LL sta;
    for(k=0;k<hs[!p].size;k++){
        sta=hs[!p].sta[k]<<3;
        hs[p].add(sta,hs[!p].f[k]);
    }
}

LL getsta()   //最小表示法
{
    LL i,cnt=1,sta=0;
    mem(ma,-1);
    ma[0]=0;
    for(i=0;i<=m;i++){
        if(ma[code[i]]==-1)ma[code[i]]=cnt++;
        code[i]=ma[code[i]];
        sta|=(LL)code[i]<<(3*i);
    }
    return sta;
}

void getcode(LL sta)
{
    int i;
    for(i=0;i<=m;i++){
        code[i]=sta&7;
        sta>>=3;
    }
}

void unblock(int i,int j,int p)
{
    int k,t;
    LL cnt,x,y;
    for(k=0;k<hs[!p].size;k++){
        getcode(hs[!p].sta[k]);
        x=code[j],y=code[j+1];
        cnt=hs[!p].f[k];
        if(x && y){     //合并连通分量
            code[j]=code[j+1]=0;
            if(x!=y){
                for(t=0;t<=m;t++)
                    if(code[t]==y)code[t]=x;
                hs[p].add(getsta(),cnt);
            }
            else if(i==ex && j==ey){   //最后一个点特殊处理
                hs[p].add(getsta(),cnt);
            }
        }

        else if(x&&!y || !x&&y){   //延续连通分量
            t=x?x:y;
            if(g[i+1][j]){
                code[j]=t;code[j+1]=0;
                hs[p].add(getsta(),cnt);
            }
            if(g[i][j+1]){
                code[j]=0;code[j+1]=t;
                hs[p].add(getsta(),cnt);
            }
        }
        else if(g[i+1][j] && g[i][j+1]){  //创建新连通分量
            code[j]=code[j+1]=8;
            hs[p].add(getsta(),cnt);
        }
    }
}

void block(LL j,int p)
{
    int k;
    for(k=0;k<hs[!p].size;k++){
        getcode(hs[!p].sta[k]);
        code[j]=code[j+1]=0;
        hs[p].add(getsta(),hs[!p].f[k]);
    }
}

LL slove()
{
    int i,j,p;
    hs[0].init();
    hs[p=1].init();
    hs[0].add(0,1);
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(g[i][j])unblock(i,j,p);
            else block(j,p);
            hs[p=!p].init();
        }
        shift(p);   //换行移位
        hs[p=!p].init();
    }
    for(i=0;i<hs[!p].size;i++)
        if(hs[!p].sta[i]==0)return hs[!p].f[i];
    return 0;
}
