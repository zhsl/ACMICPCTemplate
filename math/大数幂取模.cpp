/*     大数幂取模   O(log n)
  公式：A^x = A^(x % Phi(C) + Phi(C)) (mod C)  &&  x >= Phi(C)   */

//  a^b%c   只有b为大数
#define nnum 1000005
#define nmax 31625
int flag[nmax], prime[nmax];
int plen;
void mkprime() {
    int i, j;
    memset(flag, -1, sizeof(flag));
    for (i = 2, plen = 0; i < nmax; i++) {
        if (flag[i]) {
            prime[plen++] = i;
        }
        for (j = 0; (j < plen) && (i * prime[j] < nmax); j++) {
            flag[i * prime[j]] = 0;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
int getPhi(int n) {
    int i, te, phi;
    te = (int) sqrt(n * 1.0);
    for (i = 0, phi = n; (i < plen) && (prime[i] <= te); i++) {
        if (n % prime[i] == 0) {
            phi = phi / prime[i] * (prime[i] - 1);
            while (n % prime[i] == 0) {
                n /= prime[i];
            }
        }
    }
    if (n > 1) {
        phi = phi / n * (n - 1);
    }
    return phi;
}
int cmpCphi(int p, char *ch) {
    int i, len;
    LL res;
    len = strlen(ch);
    for (i = 0, res = 0; i < len; i++) {
        res = (res * 10 + (ch[i] - '0'));
        if (res > p) {
            return 1;
        }
    }
    return 0;
}
int getCP(int p, char *ch) {
    int i, len;
    LL res;
    len = strlen(ch);
    for (i = 0, res = 0; i < len; i++) {
        res = (res * 10 + (ch[i] - '0')) % p;
    }
    return (int) res;
}
int modular_exp(int a, int b, int c) {
    LL res, temp;
    res = 1 % c, temp = a % c;
    while (b) {
        if (b & 1) {
            res = res * temp % c;
        }
        temp = temp * temp % c;
        b >>= 1;
    }
    return (int) res;
}
void solve(int a, int c, char *ch) {
    int phi, res, b;
    phi = getPhi(c);
    if (cmpCphi(phi, ch)) {
        b = getCP(phi, ch) + phi;
    } else {
        b = atoi(ch);
    }
    res = modular_exp(a, b, c);
    printf("%d\n", res);
}
int main() {
 //   freopen("data.in", "r", stdin);
    int a, c;
    char ch[nnum];
    mkprime();
    while (~scanf("%d %s %d", &a, ch, &c)) {
        solve(a % c, c, ch);
    }
    return 0;
}

//  a^b%c   a和b都为大数
#define nnum 1000005
#define nmax 31625
int flag[nmax], prime[nmax];
int plen;
void mkprime() {
    int i, j;
    memset(flag, -1, sizeof(flag));
    for (i = 2, plen = 0; i < nmax; i++) {
        if (flag[i]) {
            prime[plen++] = i;
        }
        for (j = 0; (j < plen) && (i * prime[j] < nmax); j++) {
            flag[i * prime[j]] = 0;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
int getPhi(int n) {
    int i, te, phi;
    te = (int) sqrt(n * 1.0);
    for (i = 0, phi = n; (i < plen) && (prime[i] <= te); i++) {
        if (n % prime[i] == 0) {
            phi = phi / prime[i] * (prime[i] - 1);
            while (n % prime[i] == 0) {
                n /= prime[i];
            }
        }
    }
    if (n > 1) {
        phi = phi / n * (n - 1);
    }
    return phi;
}
int cmpBigNum(int p, char *ch) {
    int i, len;
    LL res;
    len = strlen(ch);
    for (i = 0, res = 0; i < len; i++) {
        res = (res * 10 + (ch[i] - '0'));
        if (res > p) {
            return 1;
        }
    }
    return 0;
}
int getModBigNum(int p, char *ch) {
    int i, len;
    LL res;
    len = strlen(ch);
    for (i = 0, res = 0; i < len; i++) {
        res = (res * 10 + (ch[i] - '0')) % p;
    }
    return (int) res;
}
int modular_exp(int a, int b, int c) {
    LL res, temp;
    res = 1 % c, temp = a % c;
    while (b) {
        if (b & 1) {
            res = res * temp % c;
        }
        temp = temp * temp % c;
        b >>= 1;
    }
    return (int) res;
}
void solve(int a, int c, char *ch) {
    int phi, res, b;
    phi = getPhi(c);
    if (cmpBigNum(phi, ch)) {
        b = getModBigNum(phi, ch) + phi;
    } else {
        b = atoi(ch);
    }
    res = modular_exp(a, b, c);
    printf("%d\n", res);
}
int main() {
 // freopen("data.in", "r", stdin);
    int a, c;
    char cha[nnum], chb[nnum];
    mkprime();
    while (~scanf("%s %s %d", cha, chb, &c)) {
        a = getModBigNum(c, cha);
        solve(a, c, chb);
    }
    return 0;
}
