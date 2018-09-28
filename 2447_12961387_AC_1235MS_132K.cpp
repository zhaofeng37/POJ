// POJ 2447 Prime Test http://poj.org/problem?id=2447
// Please see introduction to algorithm
#include <algorithm>

__int64 x = 0, y = 0 ;
__int64 gcd(__int64 a, __int64 b)
{
    if (0 == b)
    {
        x = 1 ; y = 0 ;
        return a ;
    }
    __int64 g = gcd(b, a % b) ;
    __int64 t = x ;
    x = y ;
    y = t - (a / b) * y ;
    return g ;
}
__int64 mulmod(__int64 a,__int64 b,__int64 p)
{
    __int64 d = 0 ;
    while (b)
    {
        if (b % 2)
            d += a ;
        d %= p ;
        b >>= 1 ;
        a <<= 1 ;
        a %= p ;
    }
    return d ;
}
__int64 expmod(__int64 a, __int64 b, __int64 n)
{
    __int64 d = 1 ;
    __int64 t = a ;
    while (b)
    {
        if (b % 2)
            d = mulmod(t, d, n) ;
        b >>= 1 ;
        t = mulmod(t, t, n) ;
    }

    return d ;
}

__int64 rho(__int64 n)
{
    __int64 d = 0, t = 0, c = 240 ;
    while (1)
    {
        int i = 1, k = 2 ;
        __int64 mmx = 2, mmy = mmx ;
        while (1)
        {
            ++i ;
            mmx = (mulmod(mmx, mmx, n) + c) % n ;
            t = (mmy - mmx) >= 0 ? (mmy - mmx) : (mmx - mmy) ;
            d = gcd(t, n) ;
            if (1 != d && n != d)
                break ;
            if (mmy == mmx)
                break ;
            if (i == k)
            {
                k <<= 1 ;
                mmy = mmx ;
            }
        }
        if (1 != d && n != d)
            return d ;
        --c ;
    }
}

__int64 T(__int64 n)
{
    __int64 p = rho(n) ;
    __int64 q = n / p ;
    return (p - 1) * (q - 1) ;
}

__int64 D(__int64 e, __int64 t)
{
    gcd(e, t) ;
    return (x >= 0) ? x : (x + t) ;
}

__int64 M(__int64 c, __int64 d, __int64 n)
{
    return expmod(c, d, n) ;
}

int main()
{
    __int64 c, e, n, t, d ;

    while(scanf("%I64d %I64d %I64d", &c, &e, &n)!=EOF)
    {
        t = T(n) ;
        d = D(e, t) ;
        printf("%I64d\n", M(c, d, n)) ;
    }
}