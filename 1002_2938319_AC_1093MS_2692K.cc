// POJ 1002 487-3279 http://poj.org/problem?id=1002
/**
*/

#include <iostream>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <list>
#include <algorithm>

using namespace std ;

void TranslateKeyboardToTelNo(char& cInput)
{
	switch(cInput)
	{
	case 65:
	case 66:
	case 67:
	case 97:
	case 98:
	case 99:
		{
			cInput = '2' ;
		}
		break;
	case 68:
	case 69:
	case 70:
	case 100:
	case 101:
	case 102:
		{
			cInput = '3' ;
		}
		break;
	case 71:
	case 72:
	case 73:
	case 103:
	case 104:
	case 105:
		{
			cInput = '4' ;
		}
		break;
	case 74:
	case 75:
	case 76:
	case 106:
	case 107:
	case 108:
		{
			cInput = '5' ;
		}
		break;
	case 77:
	case 78:
	case 79:
	case 109:
	case 110:
	case 111:
		{
			cInput = '6' ;
		}
		break;
	case 80:
	case 82:
	case 83:
	case 112:
	case 114:
	case 115:
		{
			cInput = '7' ;
		}
		break;
	case 84:
	case 85:
	case 86:
	case 116:
	case 117:
	case 118:
		{
			cInput = '8' ;
		}
		break;
	case 87:
	case 88:
	case 89:
	case 119:
	case 120:
	case 121:
		{
			cInput = '9' ;
		}
		break;
	default:
		break;
	}
}
int main(int argc, char** argv)
{
	int iN = 0 ;
	string strInput = "" ;
	string strRegularTelNo = "" ;
	string::iterator itStr ;
	long lTelNo = 0 ;
	char szBuffer[64] = { 0 } ;
	list<long> listTelAllNo ;
	cin >> iN ;
	while (iN-- > 0 && /*cin >> strInput*/scanf("%s", szBuffer) )
	{
		lTelNo = 0 ;
		strInput = szBuffer ;
		itStr = strInput.begin() ;
		for (; itStr != strInput.end();)
		{
			if ('-' == *itStr)
			{
				strInput.erase(itStr) ;
				continue ;
			}
			if (47 < *itStr && 58 > *itStr)
			{
				lTelNo *= 10 ;
				lTelNo += (*itStr) - 48 ;
				++itStr ;
				continue ;
			}
			TranslateKeyboardToTelNo(*itStr) ;
			lTelNo *= 10 ;
			lTelNo += (*itStr) - 48 ;
			++itStr ;
		}
		listTelAllNo.push_back(lTelNo) ;
	}

	long lNowTelNo = 0 ;
	long lThisTelNoCount = 0 ;
	bool bNoDuplicated = true ;
	listTelAllNo.sort() ;
	list<long>::iterator it = listTelAllNo.begin() ;
	for (; it != listTelAllNo.end(); ++it)
	{
		if (lNowTelNo != *it)
		{
			if (lThisTelNoCount > 1)
			{
				printf("%03d-%04d %d\n", lNowTelNo / 10000, lNowTelNo % 10000, lThisTelNoCount);
				bNoDuplicated = false ;
			}
			lNowTelNo = *it ;
			lThisTelNoCount = 1 ;
		}
		else
		{
			lThisTelNoCount++ ;
		}
	}

	//最后的时候还要处理一次
	if (lThisTelNoCount > 1)
	{
		printf("%03d-%04d %d\n", lNowTelNo / 10000, lNowTelNo % 10000, lThisTelNoCount);
		bNoDuplicated = false ;
	}
	if (bNoDuplicated)
	{
		cout << "No duplicates." << endl ;
	}

	return 0 ;
}