/*    HASH
   数字HASH,开散列,邻接表   */

const int MOD=4001,STA=1000010;

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
}hs;
