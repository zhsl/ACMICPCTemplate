/*  Trie   */

/*  静态化,注意内存开辟大小    */
struct Trie {
    int ch[1<<16][10];    //内存开辟尽量最大
    int val[1<<16];
    int sz;

    void init(){sz=1;mem(ch[0],0);}
    void insert(char *s,int v){      //插入
        int i,len=strlen(s),id,u=0;
        for(i=0;i<len;i++){
            id=s[i]-'0';
            if(!ch[u][id]){
                mem(ch[sz],0);
                val[sz]=0;
                ch[u][id]=sz++;
            }
            u=ch[u][id];
        }
        val[u]=v;
    }
    int find(char *s){  //查找
        int i,len=strlen(s),id,u=0;
        for(i=0;i<len;i++){
            id=s[i]-'0';
            if(!ch[u][id])return 0;
            u=ch[u][id];
        }
        for(i=0;i<10;i++)
            if(ch[u][id])return 1;   //存在prefix
        return 2;  //存在
    }
}trie;

/*  动态建立,注意释放内存  */
struct Trie {
    struct Node{
        Node(){mem(ch,0);val=0;}
        Node *ch[10];   //根据情况开大小啦
        int val;
    };
    Node *head;

    void init(){head=new Node;}
    void insert(char *s,int v){   //插入
        int i,len=strlen(s),id;
        Node *p=head,*q;
        for(i=0;i<len;i++){
            id=s[i]-'0';   //求对应编号
            if(!p->ch[id]){
                q=new Node;
                p->ch[id]=q;
            }
            p=p->ch[id];
        }
        p->val++;
    }
    int find(char *s){    //查找
        int i,len=strlen(s),id;
        Node *p=head;
        for(i=0;i<len;i++){
            id=s[i]-'0';
            if(!p->ch[id])return 0;
            p=p->ch[id];
        }
        for(i=0;i<10;i++)
            if(p->ch[i])return 1;   //存在prefix
        return 2; //存在
    }
    void free(Node *p){   //释放内存
        int i;
        for(i=0;i<10;i++)
            if(p->ch[i])free(p->ch[i]);
        delete p;
    }
}trie;
