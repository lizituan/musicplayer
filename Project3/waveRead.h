#pragma once
#include "file_read.h"
/*typedef struct  waveformat_tag
{
	WORD wFormatTag; //采样数据格式，目前只能用PCM格式 
	WORD nChannels; //通道数目（1或2） 
	DWORD nSamplesPerSec; //采样速率 
	DWORD nAvgBytesPerSec;//每秒采样得到的数据 
	WORD nBlockAlign; //记录区块对齐的单位。此值为nChannels*wBitsPerSample/8 
}WAVEFORMAT;
typedef struct pcmwaveformat_tag
{
	WAVEFORMAT wf; //有关PCM格式设置的另外一种数据结构 
	WORD wBitsPerSample; //量化位数 
}PCMWAVEFORMAT;
typedef struct WAVEFILEHEADER
{
	char chRIFF [4];			//00H 4 char "RIFF"标志
	DWORD dwRIFFLen;			//04H 4 long int 文件长度			
	char chWAVE [4];			//08H 4 char "WAVE"标志
	char chFMT [4];				//0CH 4 char "fmt"标志
	DWORD dwFMTLen;				//10H 4 　 过渡字节（不定）
	PCMWAVEFORMAT pwf;			//14H 2 int 格式类别（10H为PCM形式的声音数据)
								//16H 2 int 通道数，单声道为1，双声道为2
								//18H 2 int 采样率（每秒样本数），表示每个通道的播放速度，
								//1CH 4 long int 波形音频数据传送速率，
								//其值为通道数×每秒数据位数×每样本的数据位数／8。
								//播放软件利用此值可以估计缓冲区的大小。
								//20H 2 int 数据块的调整数（按字节算的），
								//其值为通道数×每样本的数据位值／8。
								//播放软件需要一次处理多个该值大小的字节数据，以便将其值用于缓冲区的调整。
								//22H 2 　 每样本的数据位数，表示每个声道中各个样本的数据位数。
								//如果有多个声道，对每个声道而言，样本大小都一样。	
	char chDATA [4];			//24H 4 char 数据标记符＂data"
	DWORD dwDATALen;			//28H 4 long int 语音数据的长度
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
Music mu [MAX_PATH] = { { 1,"小苹果", "筷子","《555》" }, { 2 ,"王子鸣","嘿嘿黑","《666》" }, { 3,"成龙","中国","《777》" }, { 4, "哈哈","足球","《888》" }, { 5," 呵呵 ","还好"," 《999》" }, { 6 ,"金额","进而文件","《666》" } };
Music mu2 [MAX_PATH] = { { 2 ,"王子鸣","嘿嘿黑","《666》" }, { 3,"成龙","中国","《777》" }, { 4, "哈哈","足球","《888》" }, { 5," 呵呵 ","还好"," 《999》" }, { 6 ,"金额","进而文件","《666》" } };



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
