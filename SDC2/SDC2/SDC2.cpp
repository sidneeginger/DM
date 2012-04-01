// SDC2.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "SDC2.h"
#include <ShellAPI.h>
#include <windows.h>   
#include <tlhelp32.h>    

#define MAX_LOADSTRING 100

// ȫ�ֱ���:

// �˴���ģ���а����ĺ�����ǰ������:

void Getprocess(LPCWSTR PsName);   // ��ȡ��Ӧ����   
void OnStop(HANDLE m_hPro);   // ��ɱ��Ӧ����    


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	//ShellExecute(NULL,_T("open"),_T("calc.exe"),NULL,NULL,SW_SHOWNORMAL); 
	Getprocess( _T("HModemSvr.exe") );
	HINSTANCE hInst = 0;
	hInst = ShellExecute(NULL,_T("open"), _T(".\\HModemSvr.exe"), NULL, NULL, SW_SHOWNORMAL); 
	if (ERROR_FILE_NOT_FOUND == (long)hInst)
	{
		MessageBox(NULL, _T("Can not find HModemSvr.exe"), _T("Error"), MB_OK);    
	}

	hInst = ShellExecute(NULL,_T("open"), _T(".\\SDC625.exe"), NULL, NULL, SW_SHOWMAXIMIZED); 
	if (ERROR_FILE_NOT_FOUND == (long)hInst)
	{
		MessageBox(NULL, _T("Can not find SDC625.exe"), _T("Error"), MB_OK);    
	}

	return 0;
}

void Getprocess(LPCWSTR PsName)   
{   
	HANDLE hProcessSnap = NULL;   
	PROCESSENTRY32 pe32 = {0};   
	//��þ��   
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);   
	if(hProcessSnap == (HANDLE)-1)   
	{   
		MessageBox(NULL,_T("CreateToolhelp32Snapshot()����ʧ��:%d"),_T("title"),MB_OK);    
		/*AfxMessageBox("CreateToolhelp32Snapshot()����ʧ��:%d",GetLastError());*/  
		/*  return;*/  
	}   
	pe32.dwSize = sizeof(PROCESSENTRY32);   
	//�о����н�������   
	if (Process32First(hProcessSnap, &pe32))   
	{   
		do  
		{      

			if(_tcscmp(pe32.szExeFile,PsName)==0)   
			{   
				//��������IDָ���Ļ�ô��ڵ�һ�����̵ľ��    

				HANDLE       ProcessHandle;    

				ProcessHandle=OpenProcess(PROCESS_TERMINATE,FALSE,pe32.th32ProcessID);    

				OnStop(ProcessHandle);   

			}   
			else  
			{   
				/*MessageBox(NULL,_T("ʧ��"),_T("title"),MB_OK); */  
			}   

			//cout<<pe32.th32ProcessID<<endl;   
			//pe32.dwSize = sizeof(PROCESSENTRY32);   

		}   
		while (Process32Next(hProcessSnap, &pe32));//ֱ���о����   
	}   
	else  
	{   
		MessageBox(NULL,_T("Process32Firstt()����ִ��ʧ��:%d"),_T("title"),MB_OK);    
		/*AfxMessageBox("Process32Firstt()����ִ��ʧ��:%d",GetLastError());*/  
	}   
	//�رվ��   
	CloseHandle (hProcessSnap);      

}  

void OnStop(HANDLE m_hPro)    
{   
	//�жϽ��̾���Ƿ�Ϸ�   
	if(m_hPro)   
	{   
		//���ݾ������ֹ�ղŴ򿪵ļ��±�����   
		if(!TerminateProcess(m_hPro,0))   
		{   
			//��ֹ���ִ�����ʾ������Ϣ   
			LPVOID lpMsgBuf;   
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |    
				FORMAT_MESSAGE_FROM_SYSTEM |    
				FORMAT_MESSAGE_IGNORE_INSERTS,   
				NULL,   
				GetLastError(),   
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),    
				(LPTSTR) &lpMsgBuf,   
				0,   
				NULL );   
			MessageBox(NULL,(LPCTSTR)lpMsgBuf,_T("title"),MB_OK);    
			LocalFree( lpMsgBuf );   
		}   
		else  
		{   
			/*AfxMessageBox("���ٽ��̳ɹ�");*/  
			//MessageBox(NULL,_T("���ٽ��̳ɹ�"),_T("title"),MB_OK);    
		}   
		m_hPro=NULL;   
	}   
	else  
	{   
		/*AfxMessageBox("���̾��Ϊ��");*/  
		//MessageBox(NULL,_T("���̾��Ϊ��"),_T("title"),MB_OK);    
	}   
}    