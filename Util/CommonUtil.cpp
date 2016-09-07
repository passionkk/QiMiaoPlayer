#include "stdafx.h"
#include "CommonUtil.h"

#ifdef WIN32
#include <tchar.h>
#include <shlwapi.h>
#endif//WIN32

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int StringToInt(std::string strValue)
{
    return atoi(strValue.c_str());
}

INT64 StringToInt64(std::string strValue)
{
#ifdef WIN32
    return _atoi64(strValue.c_str());
#else
    return strtoull(strValue.c_str(), NULL, 10); 
#endif
}

std::string IntToString(int nValue)
{
    char szValue[1024];
    memset(szValue, 0, 1024);
    sprintf(szValue, "%d", nValue);
    return std::string(szValue);
}

std::string Int64ToString(INT64 nValue)
{
    char szValue[1024];
    memset(szValue, 0, 1024);
#ifdef WIN32
    sprintf(szValue, "%I64d", nValue);
#else
    sprintf(szValue, "%lld", nValue);
#endif
    return std::string(szValue);
}

bool IntToBool(int nValue)
{
    if (nValue == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::string BoolToString(bool bValue)
{
    if (bValue)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

bool StringToBool(std::string strValue)
{
    if (strValue == "true")
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string DirFromFile(std::string strFilePath)
{
#ifdef WIN32
    char cFind = '\\';
#else
    char cFind = '/';
#endif
    return strFilePath.substr(0, strFilePath.rfind(cFind)+1);
}

wchar_t* DirFromFileW(const wchar_t* szFilePath, wchar_t* szDir)
{
    int nPosition;

    if (szFilePath != NULL && szDir != NULL)
    {
        wcscpy(szDir, szFilePath);
        nPosition = wcslen(szFilePath) - 1;
        while (
            (nPosition > 0)
            && (szDir[nPosition] != L'\\')
            && (szDir[nPosition] != L'/')
            )
        {
            szDir[nPosition] = L'\0';
            nPosition --;
        }
        if (nPosition > 0)
        {
            szDir[nPosition] = L'\0';
            return szDir;
        }
    }

    return NULL;
}

#ifdef WIN32
int AutoStart(bool bAutoStart)
{
    HKEY    hKey;
    DWORD   dwDisposition;
    TCHAR   szKeyName[1024];
    TCHAR   szProgramPath[1024];

    GetModuleFileName(NULL, szKeyName, MAX_PATH);
    PathStripPath(szKeyName);
    GetModuleFileName(NULL, szProgramPath, MAX_PATH);
    if (
        ::RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, NULL, 
        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition) == ERROR_SUCCESS
        )
    {
        if (bAutoStart)
        {
            ::RegSetValueEx(hKey, szKeyName, 0, REG_SZ, (LPBYTE)szProgramPath, _tcslen(szProgramPath)*sizeof(TCHAR));
        }
        else
        {
            ::RegDeleteValue(hKey, szKeyName);
        }
        ::RegFlushKey(hKey);
        ::RegCloseKey(hKey);
    }

    return 0;
}
#endif//WIN32

std::string EnsureSlashEnd(std::string strDir)
{
    if (strDir.length() >= 2 && strDir.at(1) == ':')
    {//windows path, replace / to \;
        if (strDir.rfind("\\") != (strDir.length()-1))
        {
            return strDir + "\\";
        }
    }
    else if (strDir.length() >= 1 && strDir.at(0) == '/')
    {
        if (strDir.rfind("/") != (strDir.length()-1))
        {
            return strDir + "/";
        }
    }

    return strDir;
}

std::string EnsureSameSlash(std::string strPath)
{
    if (strPath.length() >= 2 && strPath.at(1) == ':')
    {//windows path, replace / to \;
        std::string strDest;
        for (size_t i = 0; i < strPath.length(); i ++)
        {
            if (strPath.at(i) == '/')
            {
                strDest.push_back('\\');
            }
            else
            {
                strDest.push_back(strPath.at(i));
            }
        }
        return strDest;
    }
    else if (strPath.length() >= 1 && strPath.at(0) == '/')
    {//linux path, replace \ to /
        std::string strDest;
        for (size_t i = 0; i < strPath.length(); i ++)
        {
            if (strPath.at(i) == '\\')
            {
                strDest.push_back('/');
            }
            else
            {
                strDest.push_back(strPath.at(i));
            }
        }
        return strDest;
    }
    else
    {
        return strPath;
    }
}

std::string ChangeIfWindowsPath(std::string strPath)
{
    if (strPath.length() >= 2 && strPath.at(1) == ':')
    {//windows path, replace / to \;
        std::string strDest;
        for (size_t i = 0; i < strPath.length(); i ++)
        {
            if (strPath.at(i) == '/')
            {
                strDest.push_back('\\');
            }
            else
            {
                strDest.push_back(strPath.at(i));
            }
        }
        return strDest;
    }

    return strPath;
}

