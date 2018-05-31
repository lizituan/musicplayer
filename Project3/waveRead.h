#pragma once
#include "file_read.h"
/*typedef struct  waveformat_tag
{
	WORD wFormatTag; //�������ݸ�ʽ��Ŀǰֻ����PCM��ʽ 
	WORD nChannels; //ͨ����Ŀ��1��2�� 
	DWORD nSamplesPerSec; //�������� 
	DWORD nAvgBytesPerSec;//ÿ������õ������� 
	WORD nBlockAlign; //��¼�������ĵ�λ����ֵΪnChannels*wBitsPerSample/8 
}WAVEFORMAT;
typedef struct pcmwaveformat_tag
{
	WAVEFORMAT wf; //�й�PCM��ʽ���õ�����һ�����ݽṹ 
	WORD wBitsPerSample; //����λ�� 
}PCMWAVEFORMAT;
typedef struct WAVEFILEHEADER
{
	char chRIFF [4];			//00H 4 char "RIFF"��־
	DWORD dwRIFFLen;			//04H 4 long int �ļ�����			
	char chWAVE [4];			//08H 4 char "WAVE"��־
	char chFMT [4];				//0CH 4 char "fmt"��־
	DWORD dwFMTLen;				//10H 4 �� �����ֽڣ�������
	PCMWAVEFORMAT pwf;			//14H 2 int ��ʽ���10HΪPCM��ʽ����������)
								//16H 2 int ͨ������������Ϊ1��˫����Ϊ2
								//18H 2 int �����ʣ�ÿ��������������ʾÿ��ͨ���Ĳ����ٶȣ�
								//1CH 4 long int ������Ƶ���ݴ������ʣ�
								//��ֵΪͨ������ÿ������λ����ÿ����������λ����8��
								//����������ô�ֵ���Թ��ƻ������Ĵ�С��
								//20H 2 int ���ݿ�ĵ����������ֽ���ģ���
								//��ֵΪͨ������ÿ����������λֵ��8��
								//���������Ҫһ�δ�������ֵ��С���ֽ����ݣ��Ա㽫��ֵ���ڻ������ĵ�����
								//22H 2 �� ÿ����������λ������ʾÿ�������и�������������λ����
								//����ж����������ÿ���������ԣ�������С��һ����	
	char chDATA [4];			//24H 4 char ���ݱ�Ƿ���data"
	DWORD dwDATALen;			//28H 4 long int �������ݵĳ���
};
*/
typedef struct musicName
{
	TCHAR fullPath [MAX_PATH];
	TCHAR fileName [MAX_PATH];
}MSN;


struct Musiclist;
struct lsit;
typedef struct list list;
typedef struct Musiclist Music;

struct Musiclist
{
	INT ID;
	char name [MAX_PATH];
	char songname [MAX_PATH];
	char album [MAX_PATH];
	TCHAR fullPath [MAX_PATH];
	TCHAR fileName [MAX_PATH];
};
struct List
{
	char name [MAX_PATH];
	struct Musiclist * strp;
	INT soundnum;
};

typedef struct List List;
typedef struct Musiclist Music;
Music mu [MAX_PATH] = { { 1,"Сƻ��", "����","��555��" }, { 2 ,"������","�ٺٺ�","��666��" }, { 3,"����","�й�","��777��" }, { 4, "����","����","��888��" }, { 5," �Ǻ� ","����"," ��999��" }, { 6 ,"���","�����ļ�","��666��" } };
Music mu2 [MAX_PATH] = { { 2 ,"������","�ٺٺ�","��666��" }, { 3,"����","�й�","��777��" }, { 4, "����","����","��888��" }, { 5," �Ǻ� ","����"," ��999��" }, { 6 ,"���","�����ļ�","��666��" } };



void add_list ( char name [MAX_PATH] , int listnum , struct List lis [MAX_PATH] )
{
	Music lista [MAX_PATH];
	strcpy_s ( lis [listnum].name , MAX_PATH , name );
	lis [listnum].strp = lista;
	lis [listnum].soundnum = 0;
}
void add_item ( TCHAR fullPath [MAX_PATH] , TCHAR fileName [MAX_PATH] ,
	struct List lis [MAX_PATH] , int listnum , int soundnum )
{
	( lis [listnum].strp + soundnum )->ID = ( soundnum + 1 );
	strcpy_s ( ( lis [listnum].strp + soundnum )->fileName , MAX_PATH , fileName );
	strcpy_s ( ( lis [listnum].strp + soundnum )->fullPath , MAX_PATH , fullPath );
	lis [listnum].soundnum++;
}

void delet_list ( )
{

}


int CheckDuplicates (int listnum ,TCHAR Path [MAX_PATH]  ,struct List lis [MAX_PATH] )
{
	int cmp = 0;
	for ( int i = 0; i < lis [listnum].strp->ID; i++ )
		if ( !strcmp ( Path , ( lis [listnum].strp + i )->fullPath ) )
			return 1;
	return cmp;
}
