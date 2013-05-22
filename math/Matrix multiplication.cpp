/*  Matrix multiplication  
  size为矩阵大小
  mta为初始矩阵
  ans为结果矩阵  */

const int size=10;

struct Matrix{
    LL ma[size][size];
    Matrix friend operator * (const Matrix a,const Matrix b){
        Matrix ret;
        mem(ret.ma,0);
        int i,j,k;
        for(k=0;k<size;k++)
            for(i=0;i<size;i++)
                for(j=0;j<size;j++)
                    ret.ma[i][j]=(ret.ma[i][j]+a.ma[i][k]*b.ma[k][j])%MOD;
        return ret;
    }
}ans,mta;

void mutilpow(LL k)
{
    int i,j;
    mem(ans.ma,0);
    for(i=0;i<size;i++)
        ans.ma[i][i]=1;
    for(;k;k>>=1){
        if(k&1)ans=ans*mta;
        mta=mta*mta;
    }
}
