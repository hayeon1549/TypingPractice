#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream> //파일 입출력
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> //getch() 키 입력
#include <iomanip>
#include <mmsystem.h> //배경음악
using namespace std;

#pragma comment(lib,"winmm.lib") //배경음악 

#define SOUND_FILE_NAME "Bgm.wav" //배경음악
#define KEY_ENTER '\r' //처음으로 커서를 옮김
#define KEY_BS '\b' //백스페이스
#define KEY_ESC 27 //Esc 키
#define wo_len 115
#define ss_len 50
#define ls_len 20

//클래스
class FileInfo { //파일
public:
	string wo[wo_len]; //word
	string ss[ss_len]; //Short Sentence
	string ls[ls_len]; //Long Sentence
};

//함수
void SanRun(void); //산성비
void WordRun(string texts[], int &tempAcc, int &tmepTa, int a); //낱말연습, 짧은 글 연습

void gotoxy(int x, int y); // 커서 위치 이동
void textcolor(int foreground, int background); //콘솔 색상 설정
void SetCursorVisible(BOOL tf); // 커서 안보이게 하기
void line(void); //라인 출력
void move(int key, int *x, int *y, int y_min, int y_max);
int select(int x, int min, int max);