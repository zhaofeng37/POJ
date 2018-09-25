// POJ 1061 Date of Forg http://poj.org/problem?id=1061
/**
    x + am ≡ y + an (mod L)
==> a(m - n) ≡ y - x (mod L)
==> a(m - n) + L * k = y - x
==> use exgcd a(m - n) + L * k = gcd(m - n, L) = y - x
==> let d = gcd(m - n, L), c = y - x
==> if (c % d) != 0 Impossible 
==> the final result is (a * c / d) mod (L / d)
*/
#include <stdio.h>

__int64 X = 0, Y = 0 ;
__int64 gcd(__int64 a, __int64 b)
{
    if (0 == b)
    {
        X = 1 ; Y = 0 ;
        return a ;
    }
    __int64 g = gcd(b, a % b) ;
    __int64 t = X ;
    X = Y ;
    Y = t - (a / b) * Y ;
    return g ;
}

__int64 frog(__int64 x, __int64 y, __int64 m, __int64 n, __int64 l)
{
    __int64 a = n - m, b = l, c = x - y ;
    __int64 r = gcd(a, b) ;
    if (c % r)
        return -1 ;
    b /= r ; c /= r ;
    __int64 t = c * X /b ;
    X = c * X - t * b ;
    if (X < 0)
        X += l ;
    return X ;
}

int main()
{
    __int64 x, y, m, n, l, f ;
    while(scanf("%I64d %I64d %I64d %I64d %I64d", &x, &y, &m, &n, &l)!=EOF)
    {
        f = frog(x, y, m, n, l) ;
        if (f > 0)
            printf("%I64d\n", f) ;
        else
            printf("Impossible\n") ;
    }
    return 0 ;
}