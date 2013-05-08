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
