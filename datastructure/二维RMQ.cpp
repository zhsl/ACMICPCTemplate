/*   二维RMQ    */

int val[N][N],dp[N][N][9][9];
int n,m;

void init()
{
	for(int row = 1; row <= n; row++)
		for(int col = 1; col <=m; col++)
			dp[row][col][0][0] = val[row][col];
    int mx = log(double(n)) / log(2.0);
    int my = log(double(m)) / log(2.0);
    for(int i=0; i<= mx; i++)
	{
        for(int j = 0; j<=my; j++)
        {
			if(i == 0 && j ==0) continue;
            for(int row = 1; row+(1<<i)-1 <= n; row++)
			{
				for(int col = 1; col+(1<<j)-1 <= m; col++)
				{
					if(i == 0)//y轴二分
						dp[row][col][i][j]=max(dp[row][col][i][j-1],dp[row][col+(1<<(j-1))][i][j-1]);
					else//x轴二分
						dp[row][col][i][j]=max(dp[row][col][i-1][j],dp[row+(1<<(i-1))][col][i-1][j]);
				}
            }
		}
	}
}

int RMQ2D(int x1,int y1,int x2,int y2)
{
	int kx = log(double(x2-x1+1)) / log(2.0);
    int ky = log(double(y2-y1+1)) / log(2.0);
	int m1 = dp[x1][y1][kx][ky];
	int m2 = dp[x2-(1<<kx)+1][y1][kx][ky];
	int m3 = dp[x1][y2-(1<<ky)+1][kx][ky];
	int m4 = dp[x2-(1<<kx)+1][y2-(1<<ky)+1][kx][ky];
    return max( max(m1,m2) , max(m3,m4));
}
