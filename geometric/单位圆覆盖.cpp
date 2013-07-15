/*   单位圆覆盖  O(n^2*lg n)
  将每个点扩展为单位圆，依次枚举每个单位圆，枚举剩下的单位圆
  如果有交点，每个圆产生两个交点
  然后对产生的2n个交点极角排序，判断被覆盖最多的弧
  被覆盖相当于这个弧上的点为圆心的圆可以覆盖到覆盖它的那些点，所以被覆盖最多的弧就是答案了。  */
  
struct Node{  //点
    double x,y;
}nod[N];
struct Point{  //极角
    double angle;
    int id;   //交点方向
    bool operator < (const Point& a)const{
        return angle!=a.angle?angle<a.angle:id>a.id;
    }
}p[N*2];
int n;

double dist(Node &a,Node &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int slove()
{
    int i,j,ans,tot,k,cnt;
    ans=1;
    for(i=0;i<n;i++){
        for(j=k=0;j<n;j++){
            if(j==i || dist(nod[i],nod[j])>2.0)continue;
            double angle=atan2(nod[i].y-nod[j].y,nod[i].x-nod[j].x);  //注意为i-j的向量方向
            double phi=acos(dist(nod[i],nod[j])/2);
            p[k].angle=angle-phi;p[k++].id=1;
            p[k].angle=angle+phi;p[k++].id=-1;
        }
        sort(p,p+k);
        for(tot=1,j=0;j<k;j++){  //累计答案
            tot+=p[j].id;
            ans=Max(ans,tot);
        }
    }
    return ans;
}
