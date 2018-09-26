// POJ 3280 Cheapest Palindrome http://poj.org/problem?id=3280
/**
0. Traditional Dynamic Planning
1. No matter how exactly the add or delete cost value, we only
   choose the minimal value. The reason is that if we should add
   a letter to form palindrome, delete the correspond char could
   generate another palindrome also.
2. The cost for the generation of the palindrome in [i, j] is
 - 2.1 cost([i + 1][j]) + cost(char in i)
 - 2.2 cost([i][j - 1]) + cost(char in j)
 - 2.3 choose the minimal value of 2.1 and 2.2
 - 2.4 char in i and char in j is the same luckly in case, we
       should compare the cost of [i, j] and [i + 1, j - 1]
*/
#include <stdio.h>
#include <string.h>

#define Min(a,b) ((a < b) ? a : b)

char cTag[2002];
int dp[2002][2002];
int nCost[26];
int N, M;

int main()
{
    while (~scanf("%d%d", &N, &M))
    {
        scanf("%s", cTag);
        char c[2];
        int i, j;
        while (N--)
        {
            scanf("%s %d %d", c, &i, &j);
            nCost[c[0] - 'a'] = Min(i, j);
        }
        memset(dp, 0, sizeof(dp));

        for (int j = 1; j < M; ++j)
        {
            for (int i = j - 1; i >= 0; --i)
            {
                dp[i][j] = Min(dp[i + 1][j] + nCost[cTag[i] - 'a'], dp[i][j - 1] + nCost[cTag[j] - 'a']);

                if (cTag[i] == cTag[j])
                    dp[i][j] = Min(dp[i][j], dp[i + 1][j - 1]);
            }
        }
        printf("%d\n", dp[0][M - 1]);
    }
    return 0;
}
