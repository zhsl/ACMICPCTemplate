/*   二进制数中1的个数
 -朴素方法   O(n)
 -快速法     O(k) 1的个数
 -查表法
   -动态建表   O(n/8)
   -静态表-4bit   O(n/4)
   -静态表-8bit   O(n/8)
 -平行算法   O(logn)
 -完美法  O(1)常数有点大
 -指令法  O(1)

/*   朴素方法   O(n) */
int BitCount1(unsigned int n)
{
    unsigned int c =0 ; // 计数器
    for (c =0; n; n >>=1) // 循环移位
        c += n &1 ; // 如果当前位是1，则计数器加1
    return c ;
}

/*   快速法    O(k) 1的个数    */
int BitCount2(unsigned int n)
{
    unsigned int c =0 ;
    for (c =0; n; ++c)
    {
        n &= (n -1) ; // 清除最低位的1
    }
    return c ;
}

//--------------------------------------我是分割线><
/*     动态建表
先说一下填表的原理，根据奇偶性来分析，对于任意一个正整数n
1.如果它是偶数，那么n的二进制中1的个数与n/2中1的个数是相同的，比如4和2的二进制中都有一个1，6和3的二进制中都有两个1。为啥？因为n是由n/2左移一位而来，而移位并不会增加1的个数。
2.如果n是奇数，那么n的二进制中1的个数是n/2中1的个数+1，比如7的二进制中有三个1，7/2 = 3的二进制中有两个1。为啥？因为当n是奇数时，n相当于n/2左移一位再加1。
再说一下查表的原理
对于任意一个32位无符号整数，将其分割为4部分，每部分8bit，对于这四个部分分别求出1的个数，再累加起来即可。而8bit对应2^8 = 256种01组合方式，这也是为什么表的大小为256的原因。
注意类型转换的时候，先取到n的地址，然后转换为unsigned char*，这样一个unsigned int（4 bytes）对应四个unsigned char（1 bytes），分别取出来计算即可。举个例子吧，以87654321（十六进制）为例，先写成二进制形式-8bit一组，共四组，以不同颜色区分，这四组中1的个数分别为4，4，3，2，所以一共是13个1，如下面所示。
10000111 01100101 01000011 00100001 = 4 + 4 + 3 + 2 = 13                 */
int BitCount3(unsigned int n) 
{ 
    // 建表
    unsigned char BitsSetTable256[256] = {0} ; 

    // 初始化表 
    for (int i =0; i <256; i++) 
    { 
        BitsSetTable256[i] = (i &1) + BitsSetTable256[i /2]; 
    } 

    unsigned int c =0 ; 

    // 查表
    unsigned char* p = (unsigned char*) &n ; 

    c = BitsSetTable256[p[0]] + 
        BitsSetTable256[p[1]] + 
        BitsSetTable256[p[2]] + 
        BitsSetTable256[p[3]]; 

    return c ; 
}

/*    静态表-4bit 
原理和8-bit表相同，详见8-bit表的解释    */
int BitCount4(unsigned int n)
{
    unsigned int table[16] = 
    {
        0, 1, 1, 2, 
        1, 2, 2, 3, 
        1, 2, 2, 3, 
        2, 3, 3, 4
    } ;

    unsigned int count =0 ;
    while (n)
    {
        count += table[n &0xf] ;
        n >>=4 ;
    }
    return count ;
}

/*    静态表-8bit
首先构造一个包含256个元素的表table，table[i]即i中1的个数，这里的i是[0-255]之间任意一个值。然后对于任意一个32bit无符号整数n，我们将其拆分成四个8bit，然后分别求出每个8bit中1的个数，再累加求和即可，这里用移位的方法，每次右移8位，并与0xff相与，取得最低位的8bit，累加后继续移位，如此往复，直到n为0。所以对于任意一个32位整数，需要查表4次。以十进制数2882400018为例，其对应的二进制数为10101011110011011110111100010010，对应的四次查表过程如下：红色表示当前8bit，绿色表示右移后高位补零。
第一次( n & 0xff)         10101011110011011110111100010010
第二次((n >> 8) & 0xff)   00000000101010111100110111101111
第三次((n >> 16) & 0xff)  00000000000000001010101111001101
第四次((n >> 24) & 0xff)  00000000000000000000000010101011    */
int BitCount7(unsigned int n)
{ 
    unsigned int table[256] = 
    { 
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 
    }; 

    return table[n &0xff] +
        table[(n >>8) &0xff] +
        table[(n >>16) &0xff] +
        table[(n >>24) &0xff] ;
}
//当然也可以搞一个16bit的表，或者更极端一点32bit的表，速度将会更快！


//--------------------------------------我是分割线><
/*      平行算法    O(logn)
先将n写成二进制形式，然后相邻位相加，重复这个过程，直到只剩下一位。
以217（11011001）为例，有图有真相，下面的图足以说明一切了。217的二进制表示中有5个1
   1 1 0 1 1 0 0 1
    2 + 1   1 + 1
      3   +   2
          5
*/

int BitCount4(unsigned int n) 
{ 
    n = (n &0x55555555) + ((n >>1) &0x55555555) ; 
    n = (n &0x33333333) + ((n >>2) &0x33333333) ; 
    n = (n &0x0f0f0f0f) + ((n >>4) &0x0f0f0f0f) ; 
    n = (n &0x00ff00ff) + ((n >>8) &0x00ff00ff) ; 
    n = (n &0x0000ffff) + ((n >>16) &0x0000ffff) ; 

    return n ; 
}

/*      完美法
第一行代码的作用
先说明一点，以0开头的是8进制数，以0x开头的是十六进制数，上面代码中使用了三个8进制数。
将n的二进制表示写出来，然后每3bit分成一组，求出每一组中1的个数，再表示成二进制的形式。比如n = 50，其二进制表示为110010，分组后是110和010，这两组中1的个数本别是2和3。2对应010，3对应011，所以第一行代码结束后，tmp = 010011，具体是怎么实现的呢？由于每组3bit，所以这3bit对应的十进制数都能表示为2^2 * a + 2^1 * b + c的形式，也就是4a + 2b + c的形式，这里a,b,c的值为0或1，如果为0表示对应的二进制位上是0，如果为1表示对应的二进制位上是1，所以a + b + c的值也就是4a + 2b + c的二进制数中1的个数了。举个例子，十进制数6（0110）= 4 * 1 + 2 * 1 + 0，这里a = 1, b = 1, c = 0, a + b + c = 2，所以6的二进制表示中有两个1。现在的问题是，如何得到a + b + c呢？注意位运算中，右移一位相当于除2，就利用这个性质！
4a + 2b + c 右移一位等于2a + b
4a + 2b + c 右移量位等于a
然后做减法
4a + 2b + c –(2a + b) – a = a + b + c，这就是第一行代码所作的事，明白了吧。
第二行代码的作用
在第一行的基础上，将tmp中相邻的两组中1的个数累加，由于累加到过程中有些组被重复加了一次，所以要舍弃这些多加的部分，这就是&030707070707的作用，又由于最终结果可能大于63，所以要取模。
需要注意的是，经过第一行代码后，从右侧起，每相邻的3bit只有四种可能，即000, 001, 010, 011，为啥呢？因为每3bit中1的个数最多为3。所以下面的加法中不存在进位的问题，因为3 + 3 = 6，不足8，不会产生进位。
tmp + (tmp >> 3)-这句就是是相邻组相加，注意会产生重复相加的部分，比如tmp = 659 = 001 010 010 011时，tmp >> 3 = 000 001 010 010，相加得
001 010 010 011
000 001 010 010
---------------------
001 011 100 101

011 + 101 = 3 + 5 = 8。（感谢网友Di哈指正。）注意，659只是个中间变量，这个结果不代表659这个数的二进制形式中有8个1。
注意我们想要的只是第二组和最后一组（绿色部分），而第一组和第三组（红色部分）属于重复相加的部分，要消除掉，这就是&030707070707所完成的任务（每隔三位删除三位），最后为什么还要%63呢？因为上面相当于每次计算相连的6bit中1的个数，最多是111111 = 77（八进制）= 63（十进制），所以最后要对63取模。
*/
int BitCount5(unsigned int n) 
{
    unsigned inttmp = n - ((n >>1) &033333333333) - ((n >>2) &011111111111);
    return ((tmp + (tmp >>3)) &030707070707) %63;
}

/*    指令法
使用微软提供的指令，首先要确保你的CPU支持SSE4指令，用Everest和CPU-Z可以查看是否支持。  */
unsigned int n =127 ;
unsigned int bitCount = _mm_popcnt_u32(n) ;

