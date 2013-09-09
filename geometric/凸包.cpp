/*   凸包  O(n*lgn)
 Graham算法
 p[]为初始点集
 res[]为凸包点集，逆时针排序  */

struct Point{
    double x, y;
}p[N],res[N];

bool mult(Point sp, Point ep, Point op)
{
    return (sp.x - op.x) * (ep.y - op.y)>= (ep.x - op.x) * (sp.y - op.y);
}

bool operator < (const Point &l, const Point &r)
{
    return l.y < r.y || (l.y == r.y && l.x < r.x);
}

int graham(Point pnt[], int n, Point res[])
{
    int i, len, k = 0, top = 1;
    sort(pnt, pnt + n);
    if (n == 0) return 0;
    res[0] = pnt[0];
    if (n == 1) return 1;
    res[1] = pnt[1];
    if (n == 2) return 2;
    res[2] = pnt[2];
    for (i = 2; i < n; i++){
        while (top && mult(pnt[i], res[top], res[top-1]))top--;
        res[++top] = pnt[i];
    }
    len = top;
    res[++top] = pnt[n - 2];
    for (i = n - 3; i >= 0; i--){
        while (top!=len && mult(pnt[i], res[top], res[top-1])) top--;
        res[++top] = pnt[i];
    }
    return top; // 返回凸包中点的个数
}
