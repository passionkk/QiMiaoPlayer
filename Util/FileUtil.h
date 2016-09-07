#pragma once
class FileUtil
{
public:
	FileUtil();
	virtual ~FileUtil();

public:
	static CString GetFileNameFromAbsPath(const CString& strFilePath);
	static BOOL ReadStringToUnicode(CString &str);
	static int CharToUnicode(char *pchIn, CString *pstrOut);
	static void ReadStringCharToUnicode(CString &str);
};

