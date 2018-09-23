// POJ 1007 DNA Sorting http://poj.org/problem?id=1007
/**
Use a O(N * N) algorithm to count every DNA's number of pairs of entries that are out of order with respect to each other.
Use a O(N * N) algorithm to sort and print the DNA.
Both of the upper 2 steps could be optimized.
*/
#include <stdio.h>
char cDNA[55] = { 0 } ;
char cALL[105][55] = { 0 } ;
int iOrder[105] = { 0 } ;
int main()
{
    int iNo,iLen,iNowUn,iAllUn,iNowch,iMin,iCount = 0 ;
    scanf("%d %d", &iLen, &iNo) ;
    while (iCount < iNo && scanf("%s", cDNA))
    {
        iNowUn = 0 ;
        iAllUn = 0 ;
        iNowch = 0 ;
        for (int i = 0; i < iLen - 1; ++i)
        {
            if (cDNA[i] == iNowch)
            {
                iAllUn += iNowUn ;
                continue ;
            }
            else
            {
                iNowch = cDNA[i] ;
                iNowUn = 0 ;
            }
            for (int j = i + 1; j < iLen; ++j)
            {
                if (cDNA[i] > cDNA[j])
                {
                    ++iNowUn ;
                }
            }
            iAllUn += iNowUn ;
        }
        iOrder[iCount] = iAllUn ;
        for (int i = 0; i < iLen; ++i)
        {
            cALL[iCount][i] = cDNA[i] ;
        }
        iCount++ ;
    }
    for (int i = 0; i < iNo; ++i)
    {
        iCount = 0 ;
        iMin = iOrder[0] ;
        for (int j = 1; j < iNo; ++j)
        {
            if (iMin > iOrder[j])
            {
                iCount = j ;
                iMin = iOrder[j] ;
            }
        }
        iOrder[iCount] = 0x40000000 ;
        printf("%s\n", cALL[iCount]) ;
    }
    return 0 ;
}