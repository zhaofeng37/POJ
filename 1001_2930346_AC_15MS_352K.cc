// POJ 1001 Exponentiation http://poj.org/problem?id=1001
/**
This is a high precision presented in literal format problem.
1. At First, we should translate the input base number into literal format.
 - 1.1 use input stream cin >> strBaseNumber as the operator and the std::string as the receiver.
       we could get the base number in literal format directly.
 - 1.2 we should trim meaningless leading and tailing zero in base number. RemoveLeftZero and RemoveRightZero
       using C++ STL syntactic sugar is provided to implement triming.
 - 1.3 [important] it's a better idea that removing the decimal point if have and treat the base
       number always as the INTEGER.

2. For the add and multiply operator is calculated from the low order to the high order, which imply
   the calculation sequence is from right to left. In contrast to literal format string we read and 
   stored in memory space.
 - 2.1 Another C++ STL syntactic sugar std::reverse(strInput.begin(), strInput.end()) fulfil the satisfaction.
 - 2.2 The second way to resolve the sequence problem is using const_reverse_iterator to fetch the element
       from the end one to begin.

3. The minimal step in this problem is single digit added or multiplyed.
 - 3.1 Carry-Over should be stored and reuesed in the step of next high order calculation or as the highest number.
 - 3.2 Do NOT forget to reverse the result literal string in the end.
*/
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <algorithm>

using namespace std ;

void RemoveLeftZero(string& strInput)
{
    string::size_type n = strInput.find_first_not_of('0');
    strInput.erase(remove(strInput.begin(), strInput.begin() + n, '0'), strInput.begin() + n);
}


//这个函数的是去掉lpos以后的无意义0
long RemoveRightZero(string& strInput, long lPos)
{
    if (lPos < 1)
        return 0;

    string::size_type l = strInput.length();
    string::size_type n = strInput.find_last_not_of('0') + 1;
    if (lPos > n)
        n = lPos;
    strInput.erase(std::remove(strInput.begin() + n, strInput.end(), '0'), strInput.end());
    return l - strInput.length();
}


void ReverseStdString(string& strInput)
{
    std::reverse(strInput.begin(), strInput.end());
}

string AddStdString(const string& strLeft, const string& strRight)
{
    string strFinalResult = "" ;
    long lToBeAdded = 0 ;       //相加以后的进位
    long lResultOne = 0 ;       //现在需要进行计算的被乘数结果的对应位
    string::const_reverse_iterator itReverseLeft = strLeft.rbegin() ;
    string::const_reverse_iterator itReverseRight = strRight.rbegin() ;
    bool bNoLeftToBeAdded = (itReverseLeft != strLeft.rend()) ? false : true ;
    bool bNoRightToBeAdded = (itReverseRight != strRight.rend()) ? false : true ;
    while (1)
    {
        if (bNoLeftToBeAdded && bNoRightToBeAdded)
        {
            break ;
        }
        if (bNoLeftToBeAdded)
        {
            while (itReverseRight != strRight.rend())
            {
                lResultOne = lToBeAdded + (*itReverseRight) - 48 ;
                strFinalResult += (lResultOne % 10) + 48 ;
                lToBeAdded = lResultOne / 10 ;
                ++itReverseRight ;
            }
            break ;
        }
        if (bNoRightToBeAdded)
        {
            while (itReverseLeft != strLeft.rend())
            {
                lResultOne = lToBeAdded + (*itReverseLeft) - 48 ;
                strFinalResult += (lResultOne % 10) + 48 ;
                lToBeAdded = lResultOne / 10 ;
                ++itReverseLeft ;
            }
            break ;
        }

        lResultOne = lToBeAdded + (*itReverseRight) - 48 + (*itReverseLeft) - 48 ;
        strFinalResult += (lResultOne % 10) + 48 ;
        lToBeAdded = lResultOne / 10 ;
        ++itReverseRight ;
        ++itReverseLeft ;
        if (itReverseRight == strRight.rend())
        {
            bNoRightToBeAdded = true ;
        }
        if (itReverseLeft == strLeft.rend())
        {
            bNoLeftToBeAdded = true ;
        }
    }
    if (lToBeAdded)
    {
        strFinalResult += lToBeAdded + 48 ;
    }
    ReverseStdString(strFinalResult) ;
    return strFinalResult ;
}

string MultiplyStdString(const string& strLeft, const string& strRight)
{
    string strFinalResult = "" ;
    string strResult ;          //每一次的结果
    string strMedia ;           //每一次的中间结果
    long lToBeAdded = 0 ;       //相乘以后的进位
    long lRightOne = 0 ;        //现在需要进行计算的乘数
    long lResultOne = 0 ;       //现在需要进行计算的被乘数结果的对应位
    long lMultiplyOne = 0 ;     //真实的结果
    long lNewResultOne = 0 ;    //这一位的结果
    long lPower = 0 ;           //这一位的权重,即后面需添加几个0
    int i = 0 ;

    long lRightNum = strRight.length() ;

    string::const_reverse_iterator itReverseRight = strRight.rbegin() ;
    for (i = 0; itReverseRight != strRight.rend(); ++itReverseRight, ++i)
    {
        lToBeAdded = 0 ;
        lRightOne = (*itReverseRight) - 48 ;
        strMedia = strLeft ;
        ReverseStdString(strMedia) ;
        string::iterator itResult = strMedia.begin() ;
        for (; itResult != strMedia.end(); ++itResult)
        {
            lResultOne = (*itResult) - 48 ;
            lMultiplyOne = lResultOne * lRightOne + lToBeAdded ;
            lNewResultOne = lMultiplyOne % 10 ;
            lToBeAdded = lMultiplyOne / 10 ;
            *itResult = (lNewResultOne + 48) ;
        }
        if (lToBeAdded > 0 && lToBeAdded < 10)
        {
            strMedia += lToBeAdded + 48 ;
        }
        ReverseStdString(strMedia) ;
        for (int j = 0; j < i; ++j)
        {
            strMedia += "0" ;
        }
        strFinalResult = AddStdString(strFinalResult, strMedia) ;
    }

    return strFinalResult ;
}

int main(int argc, char** argv)
{
    string strInput ;
    string strResult ;
    string strFinalResult ;
    int iN = 1 ;
    int iIntegerNum = 0 ;
    int iFloatNum = 0 ;
    int iResultFloatNum = 0 ;
    bool bFindPoint = false ;
    
    while (cin >> strInput >> iN)
    {
        strFinalResult = "" ;
        strResult = "" ;
        iIntegerNum = 0 ;
        iFloatNum = 0 ;
        iResultFloatNum = 0 ;
        bFindPoint = false ;
        string::iterator it = strInput.begin() ;
        for (; it != strInput.end(); ++it)
        {
            if (!bFindPoint)
            {
                if ('.' != *it)
                {
                    ++iIntegerNum ;
                }
                else
                {
                    bFindPoint = true ;
                    strInput.erase(it) ;
                    --it ;
                }
            }
            else
            {
                ++iFloatNum ;
            }
        }
        iFloatNum -= RemoveRightZero(strInput, iIntegerNum) ;
        strResult = strInput ;
        iResultFloatNum = iFloatNum ;

        strFinalResult = strInput ;
        string::size_type nFinalLength = string::npos ;

        for (int i = 0; i < iN - 1; ++i)
        {
            strFinalResult = MultiplyStdString(strFinalResult, strInput) ;
            iResultFloatNum += iFloatNum ;
        }

        if (iResultFloatNum > 0)
        {
            nFinalLength = strFinalResult.length() - iResultFloatNum ;
            strFinalResult.insert(nFinalLength, 1, '.') ;
        }

        RemoveLeftZero(strFinalResult) ;

        cout << strFinalResult << endl ;
    }

    return 0 ;
}