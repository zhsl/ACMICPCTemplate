/*  KMP  */

int next[N];
int T,n,m,len;
 
void getnext(char *a,int len)
{
    int j=0,k=-1;
    next[0]=-1;
    while(j<len){
        if(k==-1 || a[k]==a[j])
            next[++j]=++k;
        else k=next[k];
    }
}