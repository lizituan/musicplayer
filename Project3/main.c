#include "resource.h"
#include "file_read.h"
#include "waveRead.h"

// 全局变量:
#define MAX_LOADSTRING 1000
#define AFX_TARG_CHS
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle [MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass [MAX_LOADSTRING];            // 主窗口类名
HWND hListBox = 0;
int playState = -1;
static TCHAR num [MAX_PATH];
static TCHAR fullPath [MAX_PATH];
static TCHAR fileName [MAX_PATH];		//全路径和文件名
TCHAR nowPath [MAX_PATH];
char playpathstring [MAX_PATH] = { 0 };
TCHAR cmd [MAX_PATH] = { 0 };
TCHAR texts [MAX_PATH] = { 0 };
HWND hwndList = NULL;
HWND hwndTrackBar1 = NULL;
HWND hwndTrackBar2 = NULL;
HWND dialog1 = NULL;
static int listid = 0;
static int cxChar , cyChar , cxCaps , cxClient , cyClient , iMaxWidth , iMaxLine;
static HBRUSH hBrush;
static HWND hScrollBar , hTip;
static HWND hwndEdit;
static INT listnum = 0;
static INT soundnum = 0;
static INT listsum = 0;
static INT nowList = 0;
static INT nowSound = 0;

List lis [MAX_PATH];
// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass ( HINSTANCE hInstance );
BOOL                InitInstance ( HINSTANCE , int );
LRESULT CALLBACK    WndProc ( HWND , UINT , WPARAM , LPARAM );
INT_PTR CALLBACK    About ( HWND , UINT , WPARAM , LPARAM );


int WINAPI WinMain ( _In_ HINSTANCE hInstance , _In_opt_ HINSTANCE hPrevInstance ,
	_In_ LPWSTR lpCmdLine , _In_ int nCmdShow )
{
	UNREFERENCED_PARAMETER ( hPrevInstance );
	UNREFERENCED_PARAMETER ( lpCmdLine );

	// TODO: 在此放置代码。


	// 初始化全局字符串
	LoadStringW ( hInstance , IDS_APP_TITLE , szTitle , MAX_LOADSTRING );
	LoadStringW ( hInstance , IDC_MUSICPLAYER , szWindowClass , MAX_LOADSTRING );


	MyRegisterClass ( hInstance );
	hInst = hInstance;

	// 执行应用程序初始化: 
	if ( !InitInstance ( hInstance , nCmdShow ) )
	{
		return FALSE;
	}

	MSG Msg;
	HACCEL hAccelTable = LoadAccelerators ( hInstance , MAKEINTRESOURCE ( IDC_MUSICPLAYER ) );

	// 主消息循环: 
	while ( GetMessage ( &Msg , NULL , 0 , 0 ) )
	{
		if ( !TranslateAccelerator ( Msg.hwnd , hAccelTable , &Msg ) )
		{
			TranslateMessage ( &Msg );
			DispatchMessage ( &Msg );
		}
	}
	return ( int ) Msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass ( HINSTANCE hInstance )
{
	WNDCLASSEXW wc;
	wc.cbSize = sizeof ( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon ( hInstance , MAKEINTRESOURCE ( IDI_ICON3 ) );
	wc.hCursor = LoadCursor ( NULL , IDC_ARROW );
	wc.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 );
	wc.lpszMenuName = MAKEINTRESOURCE ( IDR_MENU1 );
	wc.lpszClassName = szWindowClass;
	wc.hIconSm = ( HICON ) LoadImage ( GetModuleHandle ( NULL ) ,
		MAKEINTRESOURCE ( IDI_ICON3 ) , IMAGE_ICON , 16 , 16 , 0 );
	return RegisterClassExW ( &wc );
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//

BOOL InitInstance ( HINSTANCE hInstance , int nCmdShow )
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW ( szWindowClass , "MusicPlayer" , WS_OVERLAPPEDWINDOW , CW_USEDEFAULT , CW_USEDEFAULT , 1000 , 618 , NULL , NULL , hInstance , NULL );



	if ( !hWnd )
	{
		return FALSE;
	}
	ShowWindow ( hWnd , nCmdShow );
	//SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"E:\\特典01.千年幻想交响祭.wav");



	UpdateWindow ( hWnd );


	return TRUE;
}
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LPCSTR filename;
int x = 0 , j = 0;
LRESULT CALLBACK WndProc ( HWND hWnd , UINT message , WPARAM wParam , LPARAM	lParam )
{
	switch ( message )
	{
		case WM_CREATE:
		{
			// 创建对话框  
			HWND hdlg = CreateDialog ( hInst , MAKEINTRESOURCE ( IDD_FORMVIEW ) , hWnd , ( DLGPROC ) WndProc );
			// 显示对话框  
			ShowWindow ( hdlg , SW_SHOWNA );
		}
		break;
		case WM_INITDIALOG:
		{
			HWND	hSlider1 = GetDlgItem ( hWnd , IDC_SLIDER1 );
			HWND	hSlider2 = GetDlgItem ( hWnd , IDC_SLIDER2 );
			SendMessage ( hSlider2 , TBM_SETRANGE , ( WPARAM ) 1 , ( LPARAM ) MAKELONG ( 0 , 100 ) );
			SendMessage ( hSlider2 , TBM_SETPOS , 0 , 100 );
			HWND	hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
			HWND	hListview2 = GetDlgItem ( hWnd , IDC_LIST5 );
			SetFocus ( hListview1 );   //获得焦点
			ListView_SetItemState ( hListview1 , 0 , LVIS_SELECTED , LVIS_SELECTED );       //使第一行处于选择中状态
			ListView_SetExtendedListViewStyle ( hListview1 , LVS_EX_FULLROWSELECT );      //设置整行选择风格
			SetFocus ( hListview2 );   //获得焦点
			ListView_SetItemState ( hListview2 , 0 , LVIS_SELECTED , LVIS_SELECTED );       //使第一行处于选择中状态
			ListView_SetExtendedListViewStyle ( hListview2 , LVS_EX_FULLROWSELECT );      //设置整行选择风格


			LVCOLUMN vc1;
			LVCOLUMN vc2;
			LVITEM vitem;

			vc1.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
			vc1.pszText = TEXT ( "序号" );//列标题  
			vc1.cx = 50;//列宽  
			vc1.iSubItem = 0;//子项索引，第一列无子项  
			ListView_InsertColumn ( hListview1 , 0 , &vc1 );

			vc1.pszText = TEXT ( "标题" );
			vc1.cx = 90;
			vc1.iSubItem = 1;//子项索引  
			ListView_InsertColumn ( hListview1 , 1 , &vc1 );

			vc1.pszText = TEXT ( "位置" );
			vc1.cx = 200;
			vc1.iSubItem = 2;
			ListView_InsertColumn ( hListview1 , 2 , &vc1 );

			vc2.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
			vc2.pszText = TEXT ( "歌单列表" );
			vc2.cx = 140;
			vc2.iSubItem = 0;
			ListView_InsertColumn ( hListview2 , 0 , &vc2 );

			add_list ( "本地列表" , listsum , lis );
			vitem.mask = LVIF_TEXT;
			vitem.pszText = lis [listsum].name;
			vitem.iItem = listsum;
			vitem.iSubItem = 0;
			ListView_InsertItem ( hListview2 , &vitem );
			listsum++;

			return 0;
		}
		break;
		case WM_SETFOCUS:
		{
			SetFocus ( hListBox );
		}
		break;
		case WM_HSCROLL:
		{

		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint ( hWnd , &ps );
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			EndPaint ( hWnd , &ps );
		}
		break;
		/*case WM_CONTEXTMENU:							//右键菜单
		{
			RECT rect;
			POINT pt;
			GetCursorPos ( &pt );
			//获取客户区域大小
			GetClientRect ( ( HWND ) wParam , &rect );
			//把屏幕坐标转为客户区坐标
			ScreenToClient ( ( HWND ) wParam , &pt );
			//判断点是否位于客户区域内
			if ( PtInRect ( &rect , pt ) )
			{
				//加载菜单资源
				HMENU hroot = LoadMenu ( ( HINSTANCE ) GetWindowLongPtr ( hWnd , GWLP_HINSTANCE ) , MAKEINTRESOURCE ( IDR_MENU2 ) );
				if ( hroot )
				{
					// 获取第一个弹出菜单
					HMENU hpop = GetSubMenu ( hroot , 0 );
					// 把客户区坐标还原为屏幕坐标
					ClientToScreen ( ( HWND ) wParam , &pt );
					//显示快捷菜单
					TrackPopupMenu ( hpop ,	TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON ,
						pt.x ,pt.y ,0 ,( HWND ) wParam ,NULL );
					// 用完后要销毁菜单资源
					DestroyMenu ( hroot );
				}
			}
			else
			{
				return DefWindowProc ( hWnd , message , wParam , lParam );
			}
		}
		break;*/
		case WM_COMMAND:
		{
			int wmId = LOWORD ( wParam );
			switch ( wmId )
			{
				case ID_40009:
				{
					DialogBox ( hInst , MAKEINTRESOURCE ( IDD_ABOUTBOX ) , hWnd , About );
				}
				break;
				case IDC_BUTTON4:
				{

					openDlg ( hWnd , fullPath , fileName );
					HWND hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
					LVITEM vitem;

					if ( !CheckDuplicates ( nowList , fullPath , lis ) )
					{
						( lis [nowList].strp + nowSound )->ID = ( nowSound + 1 );
						strcpy_s ( ( lis [nowList].strp + nowSound )->fileName , MAX_PATH , fileName );
						strcpy_s ( ( lis [nowList].strp + nowSound )->fullPath , MAX_PATH , fullPath );
						vitem.mask = LVIF_TEXT;
						wsprintf ( num , "%d" , lis [nowList].soundnum + 1 );
						vitem.pszText = num;
						vitem.iItem = lis [nowList].soundnum;
						vitem.iSubItem = 0;
						ListView_InsertItem ( hListview1 , &vitem );
						// 设置子项  
						vitem.iSubItem = 1;
						vitem.pszText = fileName;
						ListView_SetItem ( hListview1 , &vitem );
						vitem.iSubItem = 2;
						vitem.pszText = fullPath;
						ListView_SetItem ( hListview1 , &vitem );
						MessageBoxA ( hWnd , ( lis [nowList].strp + nowSound )->fileName 
							, (lis [nowList].strp + nowSound )->fullPath , MB_OK);
						TCHAR qwe [MAX_PATH];
						TCHAR asd [MAX_PATH];
						wsprintf ( qwe , "%d" , lis [nowList].soundnum);
						wsprintf ( asd , "%d" , lis [nowList].soundnum + 1 );
						MessageBoxA ( hWnd , asd,qwe, MB_OK );
						lis [nowList].soundnum++;
					}
				}
				break;
				case IDC_BUTTON5:
				{
					HWND hListview2 = GetDlgItem ( hWnd , IDC_LIST5 );
					LVITEM vitem;

					wsprintf ( texts , "resume %d" , listsum );
					add_list ( texts , listsum , lis );
					vitem.mask = LVIF_TEXT;
					vitem.pszText = lis [listsum].name;
					vitem.iItem = listsum;
					vitem.iSubItem = 0;
					ListView_InsertItem ( hListview2 , &vitem );
					listsum++;
				}
				break;

				case ID_40002:
				{
					DestroyWindow ( hWnd );
				}
				break;

				case IDC_BUTTON2:
				{

					int num = j;
					if ( playState == -1 )
					{
						wsprintf ( cmd , "play %s" , fullPath );
						mciSendString ( cmd , "" , 0 , NULL );
						playState = 0;//转换为播放状态
					}
					else if ( playState == 0 )
					{
						wsprintf ( cmd , "pause %s" , fullPath );
						mciSendString ( cmd , "" , 0 , NULL );
						playState = 1; //转换为暂停状态
					}
					else if ( playState == 1 )
					{
						wsprintf ( cmd , "resume %s" , fullPath );
						mciSendString ( cmd , "" , 0 , NULL );
						playState = 0;//转换为播放状态
					}
				}
				break;
			}
			break;
		}
		break;
		case WM_NOTIFY:
		{
			switch ( wParam )
			{
				HWND	hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
				HWND	hListview2 = GetDlgItem ( hWnd , IDC_LIST5 );
				case IDC_LIST2://ID为listview的ID  
				{
					LPNMITEMACTIVATE now;
					now = ( LPNMITEMACTIVATE ) lParam;//得到NMITEMACTIVATE结构指针  
					char a [50];
					
					wsprintf ( a , "%d" , now->iItem );//now->iItem项目序号 
					switch ( now->hdr.code )
					{//判断通知码  
						case NM_CLICK:
						{
							//MessageBoxA ( hWnd , a , "单击" , 0 );
							//SendMessage ( hListview1 , LVM_DELETEITEM , now->iItem , 0 );
							hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
							MessageBoxA ( hWnd , a , "单击" , 0 );
							int Listnum = SendMessage ( hListview1 , LVM_GETHOTITEM , 0 , 0 );
							//SendMessage ( hListview1 , LVM_DELETEITEM , now->iItem , 0 );
							//MessageBoxA ( hWnd , fullPath , lis [Listnum].strp->fullPath  , 0 );
							//strcpy (fullPath , ( lis [listnum].strp + now->iItem )->fullPath);
						}
						break;
						case NM_DBLCLK:
							//MessageBoxA ( hWnd , a , "双击" , 0 );
							//hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
							//strcpy_s ( fileName , MAX_PATH , ( lis [listnum].strp + now->iItem )->fullPath );
							//wsprintf ( cmd , "resume %s" , fullPath );
							//mciSendString ( cmd , "" , 0 , NULL );
							//playState = 0;//转换为播放状态
							break;
						case NM_RCLICK:
							MessageBoxA ( hWnd , a , "右击" , 0 );
							break;
					}
				}
				break;


				case IDC_LIST5: //ID为listview的ID  
				{
					LPNMITEMACTIVATE now;
					now = ( LPNMITEMACTIVATE ) lParam;//得到NMITEMACTIVATE结构指针  
					char a [50];
					wsprintf ( a , "%d" , now->iItem );//now->iItem项目序号
					int Listnum = now->iItem;
					switch ( now->hdr.code )
					{//判断通知码  
						case NM_CLICK:
						{
							hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
							hListview2 = GetDlgItem ( hWnd , IDC_LIST5 );
							//MessageBoxA ( hWnd , a , "单击12" , 0 );
							ListView_DeleteAllItems ( hListview1 );
							int soundnum = lis [Listnum].soundnum;
							char x [50];
							wsprintf ( x , "%d" , lis [Listnum].soundnum );
							nowList = now->iItem;
							MessageBoxA ( hWnd ,x,a, 0 );
							for ( int i = 0; i < soundnum; i++ )
							{
								LVITEM vitem;
								vitem.mask = LVIF_TEXT;
								wsprintf ( num , "%d" , lis [nowList].soundnum + 1 );
								vitem.pszText = num;
								vitem.iItem = lis [nowList].soundnum;
								vitem.iSubItem = 0;
								ListView_InsertItem ( hListview1 , &vitem );
								// 设置子项  
								vitem.iSubItem = 1;
								vitem.pszText = ( lis [nowList].strp + nowSound )->fileName;
								ListView_SetItem ( hListview1 , &vitem );
								vitem.iSubItem = 2;
								vitem.pszText = ( lis [nowList].strp + nowSound )->fullPath;
								ListView_SetItem ( hListview1 , &vitem );
								MessageBoxA ( hWnd , ( lis [nowList].strp + nowSound )->fileName
									, ( lis [nowList].strp + nowSound )->fullPath , MB_OK );
								TCHAR qwe [MAX_PATH];
								TCHAR asd [MAX_PATH];
								wsprintf ( qwe , "%d" , lis [nowList].soundnum );
								wsprintf ( asd , "%d" , lis [nowList].soundnum + 1 );
								MessageBoxA ( hWnd , asd , qwe , MB_OK );
								lis [nowList].soundnum++;
							}
						}
						break;
						case NM_DBLCLK:
							MessageBoxA ( hWnd , a , "双击" , 0 );
							break;
						case NM_RCLICK:
							MessageBoxA ( hWnd , a , "右击" , 0 );
							break;
					}
				}
				break;
			}
		}
		break;
		case WM_DESTROY:
			PostQuitMessage ( 0 );
			break;
		default:
			return DefWindowProc ( hWnd , message , wParam , lParam );
	}
	return 0;

}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About ( HWND hDlg , UINT message , WPARAM wParam , LPARAM lParam )
{
	UNREFERENCED_PARAMETER ( lParam );
	switch ( message )
	{
		case WM_INITDIALOG:
			return ( INT_PTR ) TRUE;

		case WM_COMMAND:
			if ( LOWORD ( wParam ) == IDOK || LOWORD ( wParam ) == IDCANCEL )
			{
				EndDialog ( hDlg , LOWORD ( wParam ) );
				return ( INT_PTR ) TRUE;
			}
			break;
	}
	return ( INT_PTR ) FALSE;
}
