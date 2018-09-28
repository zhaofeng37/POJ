// POJ3597 Polygon Division http://poj.org/problem?id=3597
/*
1. Dynamic planning problem.
2. Array u store the intermediate result calculated in processing triangle.
3. Array u will be used in calculating the quardangle.
4. Array u could decrease the complexity from O(N * N * N) to O(N * N).
*/
#include <stdio.h>

unsigned long long u[5001], t[5001];
void Init()
{
  u[0] = u[1] = u[2] = 1;
  t[0] = t[1] = t[2] = 1;
  for (int i = 3; i < 5001; ++i)
  {
      u[i] = 0;
      for (int j = 2; j < i; ++j)
          u[i] += t[j] * t[i - j + 1];
      
      t[i] = u[i];
      for (int j = 2; j < i - 1; ++j)
          t[i] += t[j] * u[i - j + 1];
  }
}

int main()
{
  Init();
  int N;
  while (~scanf("%d", &N))
    printf("%llu\n", t[N]);
  return 0;
}