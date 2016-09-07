#include "stdafx.h"
#include "FileUtil.h"


FileUtil::FileUtil()
{
}


FileUtil::~FileUtil()
{
}

CString FileUtil::GetFileNameFromAbsPath(const CString& strFilePath)
{
	int nSplit = strFilePath.ReverseFind('/');
	if (nSplit == -1)
	{
		nSplit = strFilePath.ReverseFind('\\');
		if (nSplit == -1)
			return L"";
	}
	return strFilePath.Mid(nSplit+1);
}

BOOL FileUtil::ReadStringToUnicode(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1]; //数量要加1
	for (int i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (CHAR)str.GetAt(i);
	}
	szBuf[str.GetLength()] = '\0';   //这里，必须要加上，否则会在结尾片显示一个"铪"字。
	// USES_CONVERSION;
	//char * sz=W2A(str.GetBuffer());  //这些方法我都试过，不行的。
	BOOL bok = CharToUnicode(szBuf, &str);
	delete[]szBuf;
	return bok;
}

// 将Char型字符转换为Unicode字符
int FileUtil::CharToUnicode(char *pchIn, CString *pstrOut)
{
	int nLen;
	WCHAR *ptch;
	if (pchIn == NULL)
	{
		return 0;
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, pchIn, -1, NULL, 0);//取得所需缓存的多少
	ptch = new WCHAR[nLen];//申请缓存空间
	MultiByteToWideChar(CP_ACP, 0, pchIn, -1, ptch, nLen);//转码
	pstrOut->Format(_T("%s"), ptch);
	delete[] ptch;
	return nLen;
}

void FileUtil::ReadStringCharToUnicode(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1];//注意“+1”，char字符要求结束符，而CString没有
	memset(szBuf, '\0', str.GetLength());

	int i;
	for (i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//结束符。否则会在末尾产生乱码。

	int nLen;
	WCHAR *ptch;
	CString strOut;
	if (szBuf == NULL)
	{
		return;
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, szBuf, -1, NULL, 0);//获得需要的宽字符字节数
	ptch = new WCHAR[nLen];
	memset(ptch, '\0', nLen);
	MultiByteToWideChar(CP_ACP, 0, szBuf, -1, ptch, nLen);
	str.Format(_T("%s"), ptch);

	if (NULL != ptch)
		delete[] ptch;
	ptch = NULL;

	if (NULL != szBuf)
		delete[]szBuf;
	szBuf = NULL;
	return;
}