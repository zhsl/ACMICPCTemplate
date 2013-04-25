#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>
using namespace std;
//define
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define PI acos(-1.0)
//typedef
typedef __int64 LL;
typedef unsigned __int64 ULL;
//const
const int N=200010;
const int INF=0x3f3f3f3f;
const int MOD=1000007,STA=8000010;
const LL LNF=1LL<<60;
const double EPS=1e-8;
const double DNF=1e13;
const double OO=1e15;

//Daily Use ...
template<class T> inline T Min(T a,T b){return a<b?a:b;}
template<class T> inline T Max(T a,T b){return a>b?a:b;}
template<class T> inline T Min(T a,T b,T c){return min(min(a, b),c);}
template<class T> inline T Max(T a,T b,T c){return max(max(a, b),c);}
template<class T> inline T Min(T a,T b,T c,T d){return min(min(a,b),min(c,d));}
template<class T> inline T Max(T a,T b,T c,T d){return max(max(a,b),max(c,d));}
void swap(int& a,int& b){int t=a;a=b;b=t;}
void swap(LL& a,LL& b){LL t=a;a=b;b=t;}
//

int main()
{
 //   freopen("in.txt","r",stdin);
    LL a=-1235161423512355,b=123615412;
    printf("%I64d\n",Min(a,b));


    return 0;
}
