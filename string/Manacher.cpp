/*  Manacher 求最长回文串 O(n)
  getstr预处理: abc -> $#a#b#c#
  len=strlen(s) , n=2*len+2  */

char str[N<<1],s[N];
int p[N<<1];
int n,len;

void Manacher(char *str,int *p)
{
    int i,j,id,mx;
    id=1,mx=1;
    p[0]=p[1]=1;
    for(i=2;i<n;i++){
        p[i]=1;
        if(mx>i){
            p[i]=Min(p[(id<<1)-i],mx-i);
        }
        while(str[i+p[i]]==str[i-p[i]])p[i]++;
        if(i+p[i]>mx){
            id=i;
            mx=i+p[i];
        }
    }
}

void getstr(char *s)
{
    int i;
    str[0]='$';str[1]='#';
    for(i=0;i<len;i++){
        str[(i<<1)+2]=s[i];
        str[(i<<1)+3]='#';
    }
    str[n]=0;
}
