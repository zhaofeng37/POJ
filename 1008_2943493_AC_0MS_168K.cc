// POJ 1008 Maya Calendar http://poj.org/problem?id=1008
/**
1. Get past days from month literal string.
2. Get days name in cTzolkinDate dictionary.
*/
#include <stdio.h>
#include <string.h>

int GetPastDaysFromMonth(char* pc)
{
	if (!strcmp("pop", pc))return 0 ;
	else if (!strcmp("no", pc)) return 20 ;
	else if (!strcmp("zip", pc)) return 40 ;
	else if (!strcmp("zotz", pc)) return 60 ;
	else if (!strcmp("tzec", pc)) return 80 ;
	else if (!strcmp("xul", pc)) return 100 ;
	else if (!strcmp("yoxkin", pc)) return 120 ;
	else if (!strcmp("mol", pc)) return 140 ;
	else if (!strcmp("chen", pc)) return 160 ;
	else if (!strcmp("yax", pc)) return 180 ;
	else if (!strcmp("zac", pc)) return 200 ;
	else if (!strcmp("ceh", pc)) return 220 ;
	else if (!strcmp("mac", pc)) return 240 ;
	else if (!strcmp("kankin", pc)) return 260 ;
	else if (!strcmp("muan", pc)) return 280 ;
	else if (!strcmp("pax", pc)) return 300 ;
	else if (!strcmp("koyab", pc)) return 320 ;
	else if (!strcmp("cumhu", pc)) return 340 ;
	else return 360 ;

	return 0 ;
}

char cTzolkinDate[20][10] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"} ;

int main()
{
	int iHaabDate,iHaabYear,iNo,iPastDays,iTzolkinYear,iTzolkinDateNo,iTzolkinDateStr ;
	char cHaabMonth[9] = { 0 } ;
	scanf("%d", &iNo) ;
	printf("%d\n", iNo) ;
	while (iNo-- > 0 && scanf("%d. %s %d", &iHaabDate, cHaabMonth, &iHaabYear))
	{
		iPastDays = iHaabYear * 365 + iHaabDate + GetPastDaysFromMonth(cHaabMonth) ;
		iTzolkinYear = iPastDays / 260 ;
		iTzolkinDateNo = (iPastDays + 1) % 260 ;
		iTzolkinDateStr = (iTzolkinDateNo % 20) - 1 ;
		iTzolkinDateStr = (iTzolkinDateStr + 20) % 20 ;
		iTzolkinDateNo %= 13 ;
		iTzolkinDateNo = (0 == iTzolkinDateNo) ? 13 : iTzolkinDateNo ;
		printf("%d %s %d\n", iTzolkinDateNo, cTzolkinDate[iTzolkinDateStr], iTzolkinYear) ;
	}
	return 0 ;
}