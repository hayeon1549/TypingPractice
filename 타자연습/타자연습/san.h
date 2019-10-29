#include "same.h"

clock_t start_time; // ���� �ð�

#define KEY_SP 32
#define BELL 0x07 //�� �Ҹ��� ��

//���� �����ϴ��� ��� �ڵ带 �ٲ��� �ʵ��� ��
#define INPUTMAX 40
#define INPUTCAN 40 //�Է�ĭ x��ǥ
#define STAGECAN 77 //stageĭ x��ǥ
#define SCORECAN 95 //����ĭ x��ǥ
#define FAILCAN 110 //����ĭ x��ǥ
#define WORDSSIZE 258 //words �迭 ũ��

//����
string words[WORDSSIZE] = { };

//Ŭ����
class ScreenWord
{
public:
	int index;
	int x;
	int y;

	ScreenWord() : index(0), x(0), y(0) {}
	~ScreenWord() {}

	void Reset() {
		index = 0;
		x = 0;
		y = 0;
	}

};
ScreenWord scword[INPUTMAX]; //ȭ�鿡 ��Ÿ�� �ܾ�

//Ŭ����
class UserScore
{
public:
	static int fail; // ������ ����
	static int score; //����
};
int UserScore::fail = 3;
int UserScore::score = 0;

//�Լ�
void ReadFile2();
void RandomWord(int i); //�ܾ�� x���� �������� ����
int InputKey(int key, int &inlen, int stage_count, string &inword); //�Էµ� Ű�� � Ű���� ����
void CompareWords(string inword); //�Էµ� ���ڿ� ��µ� ���� ��
void UpdateScore(void); //���� ����
void ProcessInput(int key, int &inlen, string &inword); //Ű �Է��� ���� ��� ���� �Էµ� ���ڿ��� ���� ��
void Stage(double &fallspeed, int &stage_count, int &now); //stage�� ����
void StageBoard(int a, double &fallspeed, int &stage_count, int &now); //�������� ���Ž� ���
double GetDiffTime(clock_t start_time); // �ð� ���� �˾Ƴ���(�� ����)
void EraseWord(int a); //ȭ�鿡 ��µ� �� ����
void UpdateFailCount(void); //���� ���� ����
void DrawWord(int a); //ȭ�鿡 ���
void InitScreen(int stage_count); //Ʋ ���