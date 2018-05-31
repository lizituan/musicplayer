#include "resource.h"
#include "file_read.h"
#include "waveRead.h"

// ȫ�ֱ���:
#define MAX_LOADSTRING 1000
#define AFX_TARG_CHS
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle [MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass [MAX_LOADSTRING];            // ����������
HWND hListBox = 0;
int playState = -1;
static TCHAR num [MAX_PATH];
static TCHAR fullPath [MAX_PATH];
static TCHAR fileName [MAX_PATH];		//ȫ·�����ļ���
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
// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass ( HINSTANCE hInstance );
BOOL                InitInstance ( HINSTANCE , int );
LRESULT CALLBACK    WndProc ( HWND , UINT , WPARAM , LPARAM );
INT_PTR CALLBACK    About ( HWND , UINT , WPARAM , LPARAM );


int WINAPI WinMain ( _In_ HINSTANCE hInstance , _In_opt_ HINSTANCE hPrevInstance ,
	_In_ LPWSTR lpCmdLine , _In_ int nCmdShow )
{
	UNREFERENCED_PARAMETER ( hPrevInstance );
	UNREFERENCED_PARAMETER ( lpCmdLine );

	// TODO: �ڴ˷��ô��롣


	// ��ʼ��ȫ���ַ���
	LoadStringW ( hInstance , IDS_APP_TITLE , szTitle , MAX_LOADSTRING );
	LoadStringW ( hInstance , IDC_MUSICPLAYER , szWindowClass , MAX_LOADSTRING );


	MyRegisterClass ( hInstance );
	hInst = hInstance;

	// ִ��Ӧ�ó����ʼ��: 
	if ( !InitInstance ( hInstance , nCmdShow ) )
	{
		return FALSE;
	}

	MSG Msg;
	HACCEL hAccelTable = LoadAccelerators ( hInstance , MAKEINTRESOURCE ( IDC_MUSICPLAYER ) );

	// ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//

BOOL InitInstance ( HINSTANCE hInstance , int nCmdShow )
{
	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	HWND hWnd = CreateWindowW ( szWindowClass , "MusicPlayer" , WS_OVERLAPPEDWINDOW , CW_USEDEFAULT , CW_USEDEFAULT , 1000 , 618 , NULL , NULL , hInstance , NULL );



	if ( !hWnd )
	{
		return FALSE;
	}
	ShowWindow ( hWnd , nCmdShow );
	//SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"E:\\�ص�01.ǧ����뽻���.wav");



	UpdateWindow ( hWnd );


	return TRUE;
}
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
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
			// �����Ի���  
			HWND hdlg = CreateDialog ( hInst , MAKEINTRESOURCE ( IDD_FORMVIEW ) , hWnd , ( DLGPROC ) WndProc );
			// ��ʾ�Ի���  
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
			SetFocus ( hListview1 );   //��ý���
			ListView_SetItemState ( hListview1 , 0 , LVIS_SELECTED , LVIS_SELECTED );       //ʹ��һ�д���ѡ����״̬
			ListView_SetExtendedListViewStyle ( hListview1 , LVS_EX_FULLROWSELECT );      //��������ѡ����
			SetFocus ( hListview2 );   //��ý���
			ListView_SetItemState ( hListview2 , 0 , LVIS_SELECTED , LVIS_SELECTED );       //ʹ��һ�д���ѡ����״̬
			ListView_SetExtendedListViewStyle ( hListview2 , LVS_EX_FULLROWSELECT );      //��������ѡ����


			LVCOLUMN vc1;
			LVCOLUMN vc2;
			LVITEM vitem;

			vc1.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
			vc1.pszText = TEXT ( "���" );//�б���  
			vc1.cx = 50;//�п�  
			vc1.iSubItem = 0;//������������һ��������  
			ListView_InsertColumn ( hListview1 , 0 , &vc1 );

			vc1.pszText = TEXT ( "����" );
			vc1.cx = 90;
			vc1.iSubItem = 1;//��������  
			ListView_InsertColumn ( hListview1 , 1 , &vc1 );

			vc1.pszText = TEXT ( "λ��" );
			vc1.cx = 200;
			vc1.iSubItem = 2;
			ListView_InsertColumn ( hListview1 , 2 , &vc1 );

			vc2.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
			vc2.pszText = TEXT ( "�赥�б�" );
			vc2.cx = 140;
			vc2.iSubItem = 0;
			ListView_InsertColumn ( hListview2 , 0 , &vc2 );

			add_list ( "�����б�" , listsum , lis );
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
			// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
			EndPaint ( hWnd , &ps );
		}
		break;
		/*case WM_CONTEXTMENU:							//�Ҽ��˵�
		{
			RECT rect;
			POINT pt;
			GetCursorPos ( &pt );
			//��ȡ�ͻ������С
			GetClientRect ( ( HWND ) wParam , &rect );
			//����Ļ����תΪ�ͻ�������
			ScreenToClient ( ( HWND ) wParam , &pt );
			//�жϵ��Ƿ�λ�ڿͻ�������
			if ( PtInRect ( &rect , pt ) )
			{
				//���ز˵���Դ
				HMENU hroot = LoadMenu ( ( HINSTANCE ) GetWindowLongPtr ( hWnd , GWLP_HINSTANCE ) , MAKEINTRESOURCE ( IDR_MENU2 ) );
				if ( hroot )
				{
					// ��ȡ��һ�������˵�
					HMENU hpop = GetSubMenu ( hroot , 0 );
					// �ѿͻ������껹ԭΪ��Ļ����
					ClientToScreen ( ( HWND ) wParam , &pt );
					//��ʾ��ݲ˵�
					TrackPopupMenu ( hpop ,	TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON ,
						pt.x ,pt.y ,0 ,( HWND ) wParam ,NULL );
					// �����Ҫ���ٲ˵���Դ
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
						// ��������  
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
						playState = 0;//ת��Ϊ����״̬
					}
					else if ( playState == 0 )
					{
						wsprintf ( cmd , "pause %s" , fullPath );
						mciSendString ( cmd , "" , 0 , NULL );
						playState = 1; //ת��Ϊ��ͣ״̬
					}
					else if ( playState == 1 )
					{
						wsprintf ( cmd , "resume %s" , fullPath );
						mciSendString ( cmd , "" , 0 , NULL );
						playState = 0;//ת��Ϊ����״̬
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
				case IDC_LIST2://IDΪlistview��ID  
				{
					LPNMITEMACTIVATE now;
					now = ( LPNMITEMACTIVATE ) lParam;//�õ�NMITEMACTIVATE�ṹָ��  
					char a [50];
					
					wsprintf ( a , "%d" , now->iItem );//now->iItem��Ŀ��� 
					switch ( now->hdr.code )
					{//�ж�֪ͨ��  
						case NM_CLICK:
						{
							//MessageBoxA ( hWnd , a , "����" , 0 );
							//SendMessage ( hListview1 , LVM_DELETEITEM , now->iItem , 0 );
							hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
							MessageBoxA ( hWnd , a , "����" , 0 );
							int Listnum = SendMessage ( hListview1 , LVM_GETHOTITEM , 0 , 0 );
							//SendMessage ( hListview1 , LVM_DELETEITEM , now->iItem , 0 );
							//MessageBoxA ( hWnd , fullPath , lis [Listnum].strp->fullPath  , 0 );
							//strcpy (fullPath , ( lis [listnum].strp + now->iItem )->fullPath);
						}
						break;
						case NM_DBLCLK:
							//MessageBoxA ( hWnd , a , "˫��" , 0 );
							//hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
							//strcpy_s ( fileName , MAX_PATH , ( lis [listnum].strp + now->iItem )->fullPath );
							//wsprintf ( cmd , "resume %s" , fullPath );
							//mciSendString ( cmd , "" , 0 , NULL );
							//playState = 0;//ת��Ϊ����״̬
							break;
						case NM_RCLICK:
							MessageBoxA ( hWnd , a , "�һ�" , 0 );
							break;
					}
				}
				break;


				case IDC_LIST5: //IDΪlistview��ID  
				{
					LPNMITEMACTIVATE now;
					now = ( LPNMITEMACTIVATE ) lParam;//�õ�NMITEMACTIVATE�ṹָ��  
					char a [50];
					wsprintf ( a , "%d" , now->iItem );//now->iItem��Ŀ���
					int Listnum = now->iItem;
					switch ( now->hdr.code )
					{//�ж�֪ͨ��  
						case NM_CLICK:
						{
							hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
							hListview2 = GetDlgItem ( hWnd , IDC_LIST5 );
							//MessageBoxA ( hWnd , a , "����12" , 0 );
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
								// ��������  
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
							MessageBoxA ( hWnd , a , "˫��" , 0 );
							break;
						case NM_RCLICK:
							MessageBoxA ( hWnd , a , "�һ�" , 0 );
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

// �����ڡ������Ϣ�������
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
