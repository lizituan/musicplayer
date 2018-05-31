/*case IDC_BUTTON4:
{
HWND	hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
LVITEM vitem;

vitem.mask = LVIF_TEXT;
wsprintf ( num , "%d" , ( lis [0].strp +0)->soundnum );
vitem.pszText = num;
vitem.iItem = j;
vitem.iSubItem = 0;
ListView_InsertItem ( hListview1 , &vitem );
// 设置子项
vitem.iSubItem = 1;
vitem.pszText =( lis [0].strp + 0 )->fileName;
ListView_SetItem ( hListview1 , &vitem );
vitem.iSubItem = 2;
vitem.pszText = ( lis [0].strp + 0 )->fullPath;
ListView_SetItem ( hListview1 , &vitem );
j++;

}
break;
/*case IDC_BUTTON6:
{
static TCHAR newname [MAX_PATH];
static TCHAR b [MAX_PATH];
HWND	hListview2 = GetDlgItem ( hWnd , IDC_LIST5 );
LVITEM vitem;
vitem.mask = LVIF_TEXT;
wsprintf ( newname , "新建列表%d" , listid );
add_list ( newname , listid , lis );
vitem.pszText = newname;
vitem.iItem = listid++;
vitem.iSubItem = 0;
ListView_InsertItem ( hListview2 , &vitem );
MessageBoxA ( hWnd , newname , newname , 0 );
}
break;
/*case IDC_BUTTON7:
{
HWND	hListview1 = GetDlgItem ( hWnd , IDC_LIST2 );
LVITEM vitem;
soundnum = lis [listnum].soundnum;
add_item ( fullPath , fileName , lis , listnum , soundnum);
LVITEM lvItem = { 0 };
vitem.mask = LVIF_TEXT;
wsprintf ( num , "%d" , ( lis [listnum].strp + j )->soundnum );
vitem.pszText = num;
vitem.iItem = j;
vitem.iSubItem = 0;
ListView_InsertItem  ( hListview1 , &vitem );
// 设置子项
vitem.iSubItem = 1;
vitem.pszText = ( lis [listnum].strp + j )->fileName;
ListView_SetItem ( hListview1 , &vitem );
vitem.iSubItem = 2;
vitem.pszText = ( lis [listnum].strp + j )->fullPath ;
ListView_SetItem ( hListview1 , &vitem );
j++;
soundnum++;
}
break;*/
