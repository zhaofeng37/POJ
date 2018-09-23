// POJ 1005 I Think I Need a Houseboat http://poj.org/problem?id=1005
/**
Shrinking by 50 square miles each year. Semicircle's area calculation fomula is PI / 2 * radius * radius.
radius * radius = X * X + Y * Y
*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    float fInputX ;
    float fInputY ;
    float fR2 ;
    int iN = 0 ;
    scanf("%d", &iN) ;
    for (int i = 0; i < iN; ++i)
    {
        scanf("%f %f", &fInputX, &fInputY) ;
        fR2 = fInputX * fInputX + fInputY * fInputY ;
        printf("Property %d: This property will begin eroding in year %d.\n", i + 1, long(((fR2 * 1.57075) / 50) + 1)) ;
    }

    printf("END OF OUTPUT.\n") ;

    return 0 ;
}