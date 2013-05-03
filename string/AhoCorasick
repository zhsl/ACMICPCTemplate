/*  Aho Corasick 
   静态建立Trie   */


struct Aho_Corasick{
    int ch[N][26];
    int val[N],f[N],last[N];
    int sz,n,m,w;

    void init(){sz=1;mem(ch[0],0);}
    inline int idx(char c){return c-'A';}   //字母映射
    void insert(char *s,int v){     //建立Trie树
        int i,len=strlen(s),c,u=0;
        for(i=0;i<len;i++){
            c=idx(s[i]);
            if(!ch[u][c]){
                mem(ch[sz],0);
                val[sz]=0;
                ch[u][c]=sz++;
            }
            u=ch[u][c];
        }
        val[u]=v;
    }
    
    void print(int u)   //输出找到的字符串,可修改为相应操作
    {
        if(u){
            printf("%d %d\n",u,val[u]);
            print(last[u]);
        }
    }

    void getFail()   //建立失配数组
    {
        int u,c,r;
        queue<int> q;
        f[0]=0;
        for(c=0;c<26;c++){
            u=ch[0][c];
            if(u){f[u]=0;last[u]=0;q.push(u);}
        }
        while(!q.empty()){
            r=q.front();q.pop();
            for(c=0;c<26;c++){
                u=ch[r][c];
                //改变了ch[r][c],使得空指针为非空,不改变ch[r][c]
                //if(!u){continue;}
                if(!u){ch[r][c]=ch[f[r]][c];continue;}   //不修改ch[][]与上面替换
                q.push(u);
                //如果ch[][]空指针没有改变，应顺着失配边走
                /*
                int v=f[r];
                while(v && !ch[v][c])v=f[v];
                f[u]=ch[v][c];
                */
                f[u]=ch[f[r]][c];   //不修改ch[][]与上面替换
                last[u]=val[f[u]]?f[u]:last[f[u]];
            }
        }
    }

    void find(char *T)
    {
        int i,c,u=0,len=strlen(T);
        for(i=0;i<len;i++){
            c=idx(T[i]);
            //如果getFail()中ch[][]空指针没有改变，应顺着失配边走
            //while(u && !ch[u][c])u=f[u];
            u=ch[u][c];  //不修改ch[][],不注销上面一句
            if(val[u]){print(u);}
            else if(last[u]){print(last[u]);}
        }
    }
}
