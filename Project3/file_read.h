#pragma once
#pragma comment(lib, "winmm")  
#pragma comment(lib, "comctl32")
#include <windows.h>
#include <stdio.h>
#include <Winbase.h>
#include <Winnt.h>
#include <stdio.h>
#include <commdlg.h>
#include "resource.h"
#include <WinUser.h>
#include <commctrl.h> 
#include <mmsystem.h>
#include <dsound.h>
#include <string.h>
	

BOOL openDlg(HWND hwnd, TCHAR* fullPath, TCHAR* fileName)
{
	static OPENFILENAME ofn;
	static TCHAR szFilter[] = TEXT(".wav(*.wav)\0*.wav\0")
		/*\TEXT(".mp3£¨*.mp3£©\0*.mp3\0")\
		TEXT("All Files(*.*)\0*.*\0\0")*/;

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = fullPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = fileName;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	ofn.Flags = OFN_HIDEREADONLY;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = TEXT("wav");
	ofn.lCustData = 0;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;
	return GetOpenFileName ( &ofn );
}
