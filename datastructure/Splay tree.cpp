/*  Spaly tree   O(log n)   */


int pre[N],key[N],ch[N][2],root,tot;  //分别表示父结点，键值，左右孩子(0为左孩子，1为右孩子),根结点，结点数量
int n;
//新建一个结点
void addn(int &r,int fa,int k)
{
    r=++tot;
    pre[r]=fa;
    key[r]=k;
    ch[r][0]=ch[r][1]=0;  //左右孩子为空
}
//旋转，kind为1为右旋，kind为0为左旋
int Rotate(int x,int kind)
{
    int y=pre[x],z=pre[y];
    //类似SBT，要把其中一个分支先给父节点
    ch[y][!kind]=ch[x][kind];
    pre[ch[x][kind]]=y;
    //如果父节点不是根结点，则要和父节点的父节点连接起来
    if(z)ch[z][ch[z][1]==y]=x;
    pre[x]=z;
    ch[x][kind]=y;
    pre[y]=x;
}
//Splay调整，将根为r的子树调整为goal
int Splay(int r,int goal)
{
    int y,kind;
    while(pre[r]!=goal){
        //父节点即是目标位置，goal为0表示，父节点就是根结点
        y=pre[r];
        if(pre[y]==goal){
            Rotate(r,ch[y][0]==r);
        }
        else {
            kind=ch[pre[y]][0]==y;
            //两个方向不同，则先左旋再右旋
            if(ch[y][kind]==r){
                Rotate(r,!kind);
                Rotate(r,kind);
            }
            //两个方向相同，相同方向连续两次
            else {
                Rotate(y,kind);
                Rotate(r,kind);
            }
        }
    }
    //更新根结点
    if(goal==0)root=r;
}

int Insert(int k)
{
    int r=root;
    while(ch[r][k>key[r]]){
        //不重复插入
        if(key[r]==k){
            Splay(r,0);
            return 0;
        }
        r=ch[r][k>key[r]];
    }
    addn(ch[r][k>key[r]],r,k);
    //将新插入的结点更新至根结点
    Splay(ch[r][k>key[r]],0);
    return 1;
}
//找前驱，即左子树的最右结点
int getpre(int x)
{
    if(!ch[x][0])return -INF;
    x=ch[x][0];
    while(ch[x][1])x=ch[x][1];
    return key[x];
}
//找后继，即右子树的最左结点
int getsuf(int x)
{
    if(!ch[x][1])return INF;
    x=ch[x][1];
    while(ch[x][0])x=ch[x][0];
    return key[x];
}
