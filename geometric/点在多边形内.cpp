/*   点在多边形内   
   从点p做一条射线，看射线和多边形的交点有几个,奇数个为相交，偶数个不相交。。。  
   num_node为多边形点的个数
   nod[]为多边形点集
   p为多判断的点            */


int pinply(int num_node,Node nod[],Node &p)  
{  
    int i,j,cou=0;  
    Node ray;  
    ray.x=-1,ray.y=p.y;  
    for(i=0;i<num_node;i++){  
        j=(i+1)%num_node;  
        if(ponls(nod[i],nod[j],p))return 0;  
        if(nod[i].y!=nod[j].y){  
            if(ponls(p,ray,nod[i]) && nod[i].y==max(nod[i].y,nod[j].y))  
                cou++;  
            else if(ponls(p,ray,nod[j]) && nod[j].y==max(nod[i].y,nod[j].y))  
                cou++;  
            else if(quick(nod[i],nod[j],p,ray) && las(nod[i],nod[j],p,ray)  
                && las(p,ray,nod[i],nod[j]))  
                cou++;  
        }  
    }  
    return cou&1;  
}  
  
int ponls(Node &a,Node &b,Node &p)  
{  
    if( (p.x==a.x && p.y==a.y) || (p.x==b.x && p.y==b.y) )return 2;  
    Node r1,r2;  
    r1.x=a.x-b.x,r1.y=a.y-b.y;  
    r2.x=p.x-b.x,r2.y=p.y-b.y;  
    if(!chaji(r1,r2) && p.x>=min(a.x,b.x) && p.x<=max(a.x,b.x)   
        && p.y>=min(a.y,b.y) && p.y<=max(a.y,b.y))  
        return 1;  
    return 0;  
}  
  
int quick(Node &l1,Node &l2,Node &r1,Node &r2)  
{  
  
    if(min(l1.x,l2.x)>max(r1.x,r2.x)  
        || min(l1.y,l2.y)>max(r1.y,r2.y)  
        || max(l1.x,l2.x)<min(r1.x,r2.x)  
        || max(l1.y,l2.y)<min(r1.y,r2.y))  
        return 0;  
    return 1;  
}  
  
int las(Node &l1,Node &l2,Node &r1,Node &r2)  
{  
    Node a,b,c;  
    a.x=l1.x-r1.x;  
    a.y=l1.y-r1.y;  
    b.x=r2.x-r1.x;  
    b.y=r2.y-r1.y;  
    c.x=l2.x-r1.x;  
    c.y=l2.y-r1.y;  
    if( ((a.x*b.y)-(b.x*a.y))*((c.x*b.y)-(b.x*c.y))<0)return 1;  
    else return 0;  
}
