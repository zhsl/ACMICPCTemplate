/*  Trie   */

/*  静态化,注意内存开辟大小    */

const int wide=26;  //每个节点的最大子节点数

struct Trie {
    int ch[1<<13][wide];    //内存开辟尽量最大
    int val[1<<13];
    int sz;

    void init(){sz=1;mem(ch[0],0);}
    inline int idx(char c){return c-'a';}   //字母映射
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
    int find(char *s){  //查找
        int i,len=strlen(s),c,u=0;
        for(i=0;i<len;i++){
            c=idx(s[i]);
            if(!ch[u][c])return 0;
            u=ch[u][c];
        }
        for(i=0;i<wide;i++)
            if(ch[u][c])return 1;   //存在prefix
        return 2;  //存在
    }
}trie;

/*  动态建立,注意释放内存  */

const int wide=26;  //每个节点的最大子节点数

struct Trie {
    struct Node{
        Node(){mem(ch,0);val=0;}
        Node *ch[wide];
        int val;
    };
    Node *head;

    void init(){head=new Node;}
    inline int idx(char c){return c-'a';}
    void insert(char *s,int v){   //插入
        int i,len=strlen(s),c;
        Node *p=head,*q;
        for(i=0;i<len;i++){
            c=idx(s[i]);   //求对应编号
            if(!p->ch[c]){
                q=new Node;
                p->ch[c]=q;
            }
            p=p->ch[c];
        }
        p->val=v;
    }
    int find(char *s){    //查找
        int i,len=strlen(s),c;
        Node *p=head;
        for(i=0;i<len;i++){
            c=idx(s[i]);
            if(!p->ch[c])return 0;
            p=p->ch[c];
        }
        for(i=0;i<wide;i++)
            if(p->ch[i])return 1;   //存在prefix
        return 2; //存在
    }
    void free(Node *p){   //释放内存
        int i;
        for(i=0;i<wide;i++)
            if(p->ch[i])free(p->ch[i]);
        delete p;
    }
}trie;
