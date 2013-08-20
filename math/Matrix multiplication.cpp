/*  Matrix multiplication  
  size为矩阵大小
  A为初始矩阵   */

const int 1000000007;
const int size=7;

struct Matrix{
    LL ma[size][size];
    Matrix friend operator * (const Matrix a,const Matrix b){
        Matrix ret;
        mem(ret.ma,0);
        int i,j,k;
        for(i=0;i<size;i++)
            for(j=0;j<size;j++)
                for(k=0;k<size;k++)
                    ret.ma[i][j]=(ret.ma[i][j]+a.ma[i][k]*b.ma[k][j]%MOD)%MOD;
        return ret;
    }
}A;

Matrix mutilpow(LL k)
{
    int i;
    Matrix ret;
    mem(ret.ma,0);
    for(i=0;i<size;i++)
        ret.ma[i][i]=1;
    for(;k;k>>=(1LL)){
        if(k&(1LL))ret=ret*A;
        A=A*A;
    }
    return ret;
}
