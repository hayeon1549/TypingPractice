#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream> //���� �����
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> //getch() Ű �Է�
#include <iomanip>
#include <mmsystem.h> //�������
using namespace std;

#pragma comment(lib,"winmm.lib") //������� 

#define SOUND_FILE_NAME "Bgm.wav" //�������
#define KEY_ENTER '\r' //ó������ Ŀ���� �ű�
#define KEY_BS '\b' //�齺���̽�
#define KEY_ESC 27 //Esc Ű
#define wo_len 115
#define ss_len 50
#define ls_len 20

//Ŭ����
class FileInfo { //����
public:
	string wo[wo_len]; //word
	string ss[ss_len]; //Short Sentence
	string ls[ls_len]; //Long Sentence
};

//�Լ�
void SanRun(void); //�꼺��
void WordRun(string texts[], int &tempAcc, int &tmepTa, int a); //��������, ª�� �� ����

void gotoxy(int x, int y); // Ŀ�� ��ġ �̵�
void textcolor(int foreground, int background); //�ܼ� ���� ����
void SetCursorVisible(BOOL tf); // Ŀ�� �Ⱥ��̰� �ϱ�
void line(void); //���� ���
void move(int key, int *x, int *y, int y_min, int y_max);
int select(int x, int min, int max);