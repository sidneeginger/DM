// ccline.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <commctrl.h>

#include "../ExceptionReport/ExceptionReport.h"
CExceptionReport exceptionReport;

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		int *i = NULL;
		*i = 34;
	}
	catch (...)
	{
		
	}

	return 0;
}

