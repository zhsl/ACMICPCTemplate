/*   gauss_elimination  O(n^3) 
   要求系数矩阵可逆
   A[][]是增广矩阵,即A[i][n]是第i个方程右边的常数bi
   运行结束后A[i][n]是第i个未知数的值    */
   
double A[N][N];

void gauss(int n)
{
    int i,j,k,r;
    for(i=0;i<n;i++){
        //选一行与r与第i行交换，提高数据值的稳定性
        r=i;
        for(j=i+1;j<n;j++)
            if(fabs(A[j][i]) > fabs(A[r][i]))r=j;
        if(r!=i)for(j=0;j<=n;j++)swap(A[r][j],A[i][j]);
        //i行与i+1~n行消元
      /*  for(k=i+1;k<n;k++){   //从小到大消元，中间变量f会有损失
            double f=A[k][i]/A[i][i];
            for(j=i;j<=n;j++)A[k][j]-=f*A[i][j];
        }*/
        for(j=n;j>=i;j--){   //从大到小消元，精度更高
            for(k=i+1;k<n;k++)
                A[k][j]-=A[k][i]/A[i][i]*A[i][j];
        }
    }
    //回代过程
    for(i=n-1;i>=0;i--){
        for(j=i+1;j<n;j++)
            A[i][n]-=A[j][n]*A[i][j];
        A[i][n]/=A[i][i];
    }
}


/*  异或矩阵  O( n^3 )
   高斯-约当消元
   A[][]增光矩阵
   B[][]结果矩阵
   vis[]在有多解的情况下,判断元素解是否唯一
*/

int A[N][N],B[N],vis[N],num[N];

void getA(int n)
{
    /*  得到增光矩阵A[][]   */
}

int gauss(int n)
{
    int i,j,k,cnt,row,ok,ret,up,free;
    for(i=row=0;i<n;i++){
        if(!A[row][i]){
            for(j=row+1;j<n;j++){
                if(A[j][i]){
                    for(k=i;k<=n;k++)swap(A[row][k],A[j][k]);
                    break;
                }
            }
        }
        if(A[row][i]!=1)continue;    //保证为严格的阶梯矩阵
        for(j=0;j<n;j++){    //从0开始,高斯约当消元
            if(j!=row && A[j][i]){
                for(k=i;k<=n;k++)
                    A[j][k]^=A[row][k];
            }
        }
        row++;
    }
    for(i=n-1;i>=row;i--)
        if(A[i][n])return -1;   //无解
    if(row==n){    //唯一解
        for(i=ret=0;i<n;i++)if(A[i][n])ret++;
        return ret;
    }
    mem(vis,0);
    for(i=k=j=0;i<n;i++,j++){
        while(!A[i][j] && j<n){
            vis[j]=1;   //判断元素是否解唯一
            num[k++]=j++;
        }
    }
    ret=INF;free=n-row;   //自由变元个数
    up=1<<free;
    for(k=0;k<up;k++){    //枚举最小的变换个数
        for(i=0;i<free;i++)B[num[i]]=(k&(1<<i))?1:0;
        for(i=n-1;i>=0;i--){
            if(vis[i])continue;
            B[i]=0;
            for(j=row;j<n;j++)B[i]^=B[j]*A[i][j];
            B[i]^=A[i][n];
        }
        for(i=cnt=0;i<n;i++)if(B[i])cnt++;
        ret=Min(ret,cnt);
    }
    return ret;    //返回最小的变换个数
}
