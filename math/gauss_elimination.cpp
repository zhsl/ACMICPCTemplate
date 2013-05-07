/*   gauss_elimination   */

double A[N][N];

void gauss(int A[][],int n)
{
    int i,j,k,r;
    for(i=0;i<n;i++){
        r=i;
        for(j=i+1;j<n;j++)
            if(fabs(A[j][i]) > fabs(A[r][i]) )r=j;
        if(r!=i)for(j=0;j<=n;j++)swap(A[r][j],A[i][j]);

        for(k=i+1;k<n;k++){
            double f=A[k][i]/A[i][i];
            for(j=i;j<=n;j++)A[k][j]-=f*A[i][j];
        }
      /*  for(j=n;j>=i;j--){
            for(k=i+1;k<n;k++)
                A[k][j]-=A[k][i]/A[i][i]*A[i][j];
        }*/
    }
    for(i=n-1;i>=0;i--){
        for(j=i+1;j<n;j++)
            A[i][n]-=A[j][n]*A[i][j];
        A[i][n]/=A[i][i];
    }
}
