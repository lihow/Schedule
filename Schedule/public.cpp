#include "stdafx.h"
#include <direct.h>
#include <io.h>
#include "public.h"

int CreatMultiDir(CString strDir){
	int i = 0;
	int iRet;
	int iLen;
	char* pszDir;

	if (strDir.IsEmpty())
	{
		return 0;
	}

	USES_CONVERSION;
	pszDir = T2A(strDir.GetBuffer(0));
	iLen = strlen(pszDir);

	// 创建中间目录
	for (i = 0; i < iLen; i++)
	{
		if (pszDir[i] == '\\' || pszDir[i] == '/')
		{
			pszDir[i] = '\0';

			//如果不存在,创建
			iRet = _access(pszDir, 0);
			if (iRet != 0)
			{
				iRet = _mkdir(pszDir);
				if (iRet != 0)
				{
					return -1;
				}
			}
			//支持linux,将所有\换成/
			pszDir[i] = '/';
		}
	}

	iRet = _mkdir(pszDir);
	return iRet;
}
string encode(string str){
	string res = "";
	for (int i = 0; i < str.size(); i++){
		res += str[i] + i;
	}
	char temp = res[0];
	res[0] = res[str.size() - 1];
	res[str.size() - 1] = temp;
	return res;
}
string decode(string str){
	char temp = str[0];
	str[0] = str[str.size() - 1];
	str[str.size() - 1] = temp;
	string res = "";
	for (int i = 0; i < str.size(); i++){
		res += str[i] - i;
	}
	return res;
}