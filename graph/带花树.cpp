/*    带花树    O(n^3)
  Edmonds's matching algorithm  Code by Amber   
  邻接矩阵建图，n为顶点个数，编号为1-n
  Edmonds()返回最大的匹配点数          
  如果图要删除节点，直接在3个for循环里添加标记即可   */
  
int n;
int head,tail,Start,Finish;
int link[N];     //表示哪个点匹配了哪个点
int Father[N];   //这个就是增广路的Father……但是用起来太精髓了
int Base[N];     //该点属于哪朵花
int Q[N];
bool mark[N];
bool map[N][N];
bool InBlossom[N];
bool in_Queue[N];

void BlossomContract(int x,int y)
{
    fill(mark,mark+n+1,false);
    fill(InBlossom,InBlossom+n+1,false);
    #define pre Father[link[i]]
    int lca,i;
    for (i=x;i;i=pre) {i=Base[i]; mark[i]=true; }
    for (i=y;i;i=pre) {i=Base[i]; if (mark[i]) {lca=i; break;} }  //寻找lca之旅……一定要注意i=Base[i]
    for (i=x;Base[i]!=lca;i=pre){
        if (Base[pre]!=lca) Father[pre]=link[i]; //对于BFS树中的父边是匹配边的点，Father向后跳
        InBlossom[Base[i]]=true;
        InBlossom[Base[link[i]]]=true;
    }
    for (i=y;Base[i]!=lca;i=pre){
        if (Base[pre]!=lca) Father[pre]=link[i]; //同理
        InBlossom[Base[i]]=true;
        InBlossom[Base[link[i]]]=true;
    }
    #undef pre
    if (Base[x]!=lca) Father[x]=y;     //注意不能从lca这个奇环的关键点跳回来
    if (Base[y]!=lca) Father[y]=x;
    for (i=1;i<=n;i++){
        if (InBlossom[Base[i]]){
            Base[i]=lca;
            if (!in_Queue[i]){
                Q[++tail]=i;
                in_Queue[i]=true;     //要注意如果本来连向BFS树中父结点的边是非匹配边的点，可能是没有入队的
            }
        }
    }
}

void Change()
{
    int x,y,z;
    z=Finish;
    while (z){
        y=Father[z];
        x=link[y];
        link[y]=z;
        link[z]=y;
        z=x;
    }
}

void FindAugmentPath()
{
    fill(Father,Father+n+1,0);
    fill(in_Queue,in_Queue+n+1,false);
    for (int i=1;i<=n;i++) Base[i]=i;  //Init属于同一花朵
    head=0; tail=1;
    Q[1]=Start; //当前节点进入队列
    in_Queue[Start]=1;
    while (head!=tail){
        int x=Q[++head];
        for (int y=1;y<=n;y++){
            if (map[x][y] && Base[x]!=Base[y] && link[x]!=y){   //无意义的边
                if ( Start==y || link[y] && Father[link[y]] )    //精髓地用Father表示该点是否
                    BlossomContract(x,y);
                else if (!Father[y]){
                    Father[y]=x;
                    if (link[y]){
                        Q[++tail]=link[y];
                        in_Queue[link[y]]=true;
                    }
                    else{
                        Finish=y;
                        Change();
                        return;
                    }
                }
            }
        }
    }
}

int Edmonds()
{
    int i,cnt=0;
    memset(link,0,sizeof(link));
    memset(Father,0,sizeof(Father));
    for (Start=1;Start<=n;Start++){
        if (link[Start]==0)
            FindAugmentPath();   //如果点没有匹配，那么找BFS增广路
    }

    for(i=1;i<=n;i++)
        if(link[i])cnt++;
    return cnt;
}
