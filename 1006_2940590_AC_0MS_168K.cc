// POJ 1006 Biorhythms http://poj.org/problem?id=1006
/**
Find the lowest common multiple
*/
#include <stdio.h>
int main(int argc, char** argv)
{
    int x,y,z,a,c,d ;
    int b = 1 ;
    while (scanf("%d %d %d %d", &x, &y, &z, &a) && -1 != x)
    {
        x = (23 - (x % 23)) % 23 ;
        y = (28 - (y % 28)) % 28 ;
        z = (33 - (z % 33)) % 33 ;
        c = 0 ;
        c += 33 - z ;
        x += 33 - z ;
        y += 33 - z ;
        if (!x && !y)
        {
            d = c - a ;
            if (d < 1)
            {
                d += 21252 ;
            }
            else if (d > 21252)
            {
                d -= 21252 ;
            }
            printf("Case %d: the next triple peak occurs in %d days.\n", b++, d) ;
            continue ;
        }
        while (1)
        {
            c += 33 ;
            x += 33 ;
            y += 33 ;
            if (y %= 28)
                continue ;
            if (x %= 23)
                continue ;
            break ;
        }
        d = c - a ;
        if (d < 1)
            d += 21252 ;
        else if (d > 21252)
            d -= 21252 ;
        printf("Case %d: the next triple peak occurs in %d days.\n", b++, d) ;
    }
    return 0 ;
}