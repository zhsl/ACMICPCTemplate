/*   平面最近点对   O( n*logn*logn )
  应用G++提交，G++提交速度一倍！
  分治法求平面最近点对   */
  
  
struct Node{  //id为nod排序后的编号值，index为排序前的标号值(随便自己定义)
    double x,y;
    int id,index;
    Node(){}
    Node(double _x,double _y,int _index):x(_x),y(_y),index(_index){}
}nod[N],temp[N];

int n;

double dist(Node &a,Node &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

bool cmpxy(Node a,Node b)  //先按x排序,然后按y排序
{
    return a.x!=b.x?a.x<b.x:a.y<b.y;
}

bool cmpy(Node a,Node b)  //按y排序
{
    return a.y<b.y;
}

pii Closest_Pair(int l,int r)  //返回排序后点的编号
{
    if(l==r || l+1==r)return pii(l,r);   //只有一个点或者两个点
    double d,d1,d2;
    int i,j,k,mid=(l+r)/2;
    //左右两边最小距离点的编号
    pii pn1=Closest_Pair(l,mid);
    pii pn2=Closest_Pair(mid+1,r);
    //左右两遍的最小距离
    d1=(pn1.first==pn1.second?OO:dist(nod[pn1.first],nod[pn1.second]));
    d2=(pn2.first==pn2.second?OO:dist(nod[pn2.first],nod[pn2.second]));
    pii ret;
    d=Min(d1,d2);
    ret=d1<d2?pn1:pn2;
    //找出在mid-d,mid+d之间的点
    for(i=l,k=0;i<=r;i++){
        if(fabs(nod[mid].x-nod[i].x)<=d){
            temp[k++]=nod[i];
        }
    }
    //合并两边,求最小距离
    sort(temp,temp+k,cmpy);
    for(i=0;i<k;i++){
        for(j=i+1;j<k && fabs(temp[j].y-temp[i].y)<d;j++){
            if(dist(temp[i],temp[j])<d){
                d=dist(temp[i],temp[j]);
                ret=make_pair(temp[i].id,temp[j].id);
            }
        }
    }

    return ret;
}

void Init()   //初始化点
{
    int i;
    double x,y;
    scanf("%d",&n);
    for(i=0;i<t;i++){
        scanf("%lf%lf",&x,&y);
        nod[i]=Node(x,y,i);
    }
    sort(nod,nod+n,cmpxy);
    for(i=0;i<n;i++)nod[i].id=i;  //排序后节点编号
}
