\subsection{区间筛素数}
    \begin{verbatim}
/*  区间筛素数
 -对于小区间(百万级),移位筛素数法,O(R-L)
 -对于大区间(千万/亿级),http://hi.baidu.com/czyuan_acm/item/0cbe522c3c9e4bcaa5275a12  (待补)    */
 
/*   小区间(百万级),移位筛素数法,O(R-L)   */

const int maxn = 100000;
int PrimeList[maxn];
int PrimeNum;
bool IsNotPrime[maxn]; // IsNotPrime[i] = 1表示i + L这个数是素数.
void SegmentPrime(int L, int U)
{ // 求区间[L, U]中的素数.
     int i, j;
     int SU = sqrt(1.0 * U);
     int d = U - L + 1;
     for (i = 0; i < d; i++) IsNotPrime[i] = 0; // 一开始全是素数.
     for (i = (L % 2 != 0); i < d; i += 2) IsNotPrime[i] = 1; // 把偶数的直接去掉.
     for (i = 3; i <= SU; i += 2)
     {
           if (i > L && IsNotPrime[i - L]) continue; // IsNotPrime[i - L] == 1说明i不是素数.
           j = (L / i) * i; // j为i的倍数，且最接近L的数.
           if (j < L) j += i;
           if (j == i) j += i; // i为素数，j = i说明j也是素数，所以直接 + i.
          j = j - L;
          for (; j < d; j += i) IsNotPrime[j] = 1; // 说明j不是素数(IsNotPrime[j - L] = 1).
     }
     if (L <= 1) IsNotPrime[1 - L] = 1;
     if (L <= 2) IsNotPrime[2 - L] = 0;
     PrimeNum = 0;
     for (i = 0; i < d; i++) if (!IsNotPrime[i]) PrimeList[PrimeNum++] = i + L;
}
        \end{verbatim}
