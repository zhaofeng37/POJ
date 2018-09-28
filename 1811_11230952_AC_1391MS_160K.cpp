// POJ 1811 Prime Test http://poj.org/problem?id=1811
// Please see introduction to algorithm
#include <vector>
#include <algorithm>

__int64 gcd(__int64 a, __int64 b)
{
    if (0 == b)
        return a ;
    __int64 g = gcd(b, a % b) ;
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

bool witness(__int64 a, __int64 n)
{
    __int64 t = 0 ;
    __int64 u = n - 1 ;
    while (0 == u % 2)
    {
        ++t ;
        u >>= 1 ;
    }
    __int64 y = 0, x = expmod(a, u, n) ;
    for (__int64 i = 0; i < t; ++i)
    {
        y = expmod(x, 2, n) ;
        if ((1 == y) && (1 != x) && (n - 1 != x))
            return false ;
        x = y ;
    }
    if (1 == y)
        return true ;
    return false ;
}

bool mr(__int64 p)
{
    if (2 == p || 3 == p || 5 == p || 7 == p || 11 == p || 13 == p)
        return true ;
    if ((0 == (p % 2)) || 9 == p)
        return false ;
    int m[16] = {2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584} ;
    for (int i = 0; i < 16; ++i)
    {
        if (m[i] >= p)
            break ;
        if (false == witness(m[i], p))
            return false ;
    }
    return true ;
}

__int64 rho(__int64 x, __int64 n)
{
    int i = 1, k = 2 ;
    __int64 y = x, d = 0, t = 0 ;
    while (1)
    {
        ++i ;
        x = (mulmod(x, x, n) + 240) % n ;
        t = (y - x) >= 0 ? (y - x) : (x - y) ;
        d = gcd(t, n) ;
        if (1 != d && n != d)
            return d ;
        if (y == x)
            return n ;
        if (i == k)
        {
            k <<= 1 ;
            y = x ;
        }
    }
}

__int64 pt(__int64 n)
{
    if (mr(n))
        return n ;
    else
    {
        if (0 == (n % 2))
            return 2 ;
        __int64 f1 = n ;
        __int64 c = 240 ;
        while (f1 == n)
            f1 = rho(c--, n) ;
        __int64 f2 = n / f1 ;
        bool b1 = mr(f1), b2 = mr(f2) ;
        if (b1 && b2)
            return (f1 < f2) ? f1 : f2 ;
        else
        {
            if (false == b1)
                f1 = pt(f1) ;
            if (false == b2)
                f2 = pt(f2) ;
            return (f1 < f2) ? f1 : f2 ;
        }
    }
}

int main()
{
    int n = 2 ;
    __int64 a = 0 ;
    scanf("%d", &n) ;

    while(scanf("%I64d", &a)!=EOF)
    {
        __int64 r = pt(a) ;
        if (a == r)
            printf("Prime\n") ;
        else
            printf("%I64d\n", r) ;
    }
    return 0 ;
}