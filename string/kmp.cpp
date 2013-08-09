/*  KMP  

        0 1 2 3 4 5 6 7 8
 s：    a b a b a b c d
 next: -1 0 0 1 2 3 4 0 0    */


int next[N];
int T,n,m,len;
 
void getnext(char *s,int len)
{
    int j=0,k=-1;
    next[0]=-1;
    while(j<len){
        if(k==-1 || s[k]==s[j])
            next[++j]=++k;
        else k=next[k];
    }
}
