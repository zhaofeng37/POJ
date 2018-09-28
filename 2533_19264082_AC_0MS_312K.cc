/* POJ2533 Longest Order Subsequence http://poj.org/problem?id=2533 
1. There are 2 ways to solve Longest Order Subsequence. Both of the
   2 algorithms need another array which length is equal to the array
   of the unordered input parameters to store the status of the
   intermidate length or last minimal value of the Order Subsequence
2. LOS method is an O(N * N) two level traverse algorithm.
3. LIS() method use array m[i] to store the minimal last value of ordered
   subsequence which length is i. If the fresh a[i] is greater than 
   m[size - 1] put the greatest a[i] in the next position of m, otherwise
   find the position of a[i] in the m use binary search.
*/

#include <stdio.h>

const int MAXN = 1000;
int N;
int a[MAXN + 5], m[MAXN + 5];

int LOS() {
  int longest = 1;
  m[0] = 1;
  for (int i = 1; i < N; ++i) {
    m[i] = 1;
    for (int j = 0; j < i; ++j) {
      if (a[j] < a[i] && m[j] + 1 > m[i])
        m[i] = m[j] + 1;
    }
    if (m[i] > longest) longest = m[i];
  }
  return longest;
}

int bsearch(int val, int l, int r) {
  int mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (val < m[mid]) r = mid;
    else if (val > m[mid]) l = mid + 1;
    else return mid;
  }
  return l;
}

//数组m[i]保留长度为i的上升串的末尾最小元素
int LIS() {
  int pos = 0, size = 1;
  m[0] = a[0];
  for (int i = 1; i < N; ++i) {
    if (a[i] > m[size - 1])
      pos = size++;
    else
      pos = bsearch(a[i], 0, size);

    m[pos] = a[i];
  }
  return size;
}

int main() {
  while (~scanf("%d", &N)) {
    for (int i = 0; i < N; ++i)
      scanf("%d", &a[i]);

    printf("%d\n", LIS());
  }
  return 0;
}