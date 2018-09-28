// POJ 3579 Median poj.org/problem?id=3579
/**
1. Traditional sort and lower bound O(N*logN) algorithm
2. Sort the input array
3. Calculate the minimal difference value as l and maximal as r
4. Calculate the final median difference position is (N - 1) * N / 4
5. If l and r is neighbour, the l is the final median difference value
6. One possible final median difference value we predicate is the
   average of the l and r, shortened as mid.
7. Find the amount of the difference less than mid. Take care of 
   std::lower_bound return the less than amount, we do need the amount
   that greater than mid.
8. If the amount that more mid overflow (N - 1) * N / 4, it means the
   mid we predicate is less than the actual one. so let l = mid instead,
   vice versa.
*/
#include <stdio.h>
#include <algorithm>

int32_t arr[100005] = { 0 };
int32_t m = 0, l = 0, mid = 0, r = 0, N = 0;

bool test(int32_t v) 
{
    int32_t c = 0;
    for (int i = 0; i < N; ++i)
        c += N - (std::lower_bound(arr + i, arr + N, arr[i] + v) - arr);
    return c > m;
}

int main() {
    int32_t x, i;
    while (~scanf("%d", &N))
    {
        i = 0;
        while (N--) {
            scanf("%d", &x);
            arr[i++] = x;
        }
        N = i;
        std::sort(arr, arr + N);
        l = 0; r = arr[N - 1] - arr[0]; m = (N - 1) * N / 4;
        while (r - l > 1) 
        {
            mid = (l + r) >> 1;
            test(mid) ? l = mid : r = mid;
        }
        printf("%d\n", l);
    }
    return 0;
}