#ifndef _COMMON_UTIL_H_
#define _COMMON_UTIL_H_

#include <string>

#ifndef INT64
#ifdef WIN32
typedef __int64				INT64;
#else
typedef signed long long	INT64;
#endif
#endif//INT64

//#ifndef UINT64
//#ifdef WIN32
//typedef unsigned __int64    UINT64;
//#else
//typedef unsigned long long  UINT64;
//#endif
//
//#endif//

int StringToInt(std::string strValue);
INT64 StringToInt64(std::string strValue);
std::string IntToString(int nValue);
std::string Int64ToString(INT64 nValue);


bool IntToBool(int nValue);
std::string BoolToString(bool bValue);
bool StringToBool(std::string strValue);

std::string DirFromFile(std::string strFilePath);
wchar_t* DirFromFileW(const wchar_t* szFilePath, wchar_t* szDir);

#ifdef WIN32
int AutoStart(bool bAutoStart);
#endif//WIN32

std::string EnsureSlashEnd(std::string strDir);

std::string EnsureSameSlash(std::string strPath);

//change windows path from C:/1/1.txt  to C:\1\1.txt
std::string ChangeIfWindowsPath(std::string strPath);

#endif //_COMMON_UTIL_H_
