/*  Trie   */


/*  动态建立,释放内存要写递归函数  */
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
}trie;
