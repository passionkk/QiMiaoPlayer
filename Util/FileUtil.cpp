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
	char *szBuf = new char[str.GetLength() + 1]; //����Ҫ��1
	for (int i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (CHAR)str.GetAt(i);
	}
	szBuf[str.GetLength()] = '\0';   //�������Ҫ���ϣ�������ڽ�βƬ��ʾһ��"��"�֡�
	// USES_CONVERSION;
	//char * sz=W2A(str.GetBuffer());  //��Щ�����Ҷ��Թ������еġ�
	BOOL bok = CharToUnicode(szBuf, &str);
	delete[]szBuf;
	return bok;
}

// ��Char���ַ�ת��ΪUnicode�ַ�
int FileUtil::CharToUnicode(char *pchIn, CString *pstrOut)
{
	int nLen;
	WCHAR *ptch;
	if (pchIn == NULL)
	{
		return 0;
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, pchIn, -1, NULL, 0);//ȡ�����軺��Ķ���
	ptch = new WCHAR[nLen];//���뻺��ռ�
	MultiByteToWideChar(CP_ACP, 0, pchIn, -1, ptch, nLen);//ת��
	pstrOut->Format(_T("%s"), ptch);
	delete[] ptch;
	return nLen;
}

void FileUtil::ReadStringCharToUnicode(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1];//ע�⡰+1����char�ַ�Ҫ�����������CStringû��
	memset(szBuf, '\0', str.GetLength());

	int i;
	for (i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//���������������ĩβ�������롣

	int nLen;
	WCHAR *ptch;
	CString strOut;
	if (szBuf == NULL)
	{
		return;
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, szBuf, -1, NULL, 0);//�����Ҫ�Ŀ��ַ��ֽ���
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