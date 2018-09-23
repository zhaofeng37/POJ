// POJ 1004 Financial Management http://poj.org/problem?id=1004
/**
No more technical skill but use .2f to show the nearest penny result.
*/
#include <iostream>
#include <stdlib.h>

using namespace std ;

int main(int argc, char** argv)
{
	float fInput ;
	float fAll = 0 ;
	for (int i = 0; i < 12; ++i)
	{
		cin >> fInput ;
		fAll += fInput ;
	}

	printf("$%.2f\n", float(fAll / 12)) ;

	return 0 ;
}