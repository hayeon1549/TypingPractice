#include "same.h"

clock_t start_time; // 기준 시각

#define KEY_SP 32
#define BELL 0x07 //삑 소리를 냄

//값을 조절하더라도 모든 코드를 바꾸지 않도록 함
#define INPUTMAX 40
#define INPUTCAN 40 //입력칸 x좌표
#define STAGECAN 77 //stage칸 x좌표
#define SCORECAN 95 //점수칸 x좌표
#define FAILCAN 110 //실패칸 x좌표
#define WORDSSIZE 258 //words 배열 크기

//전역
string words[WORDSSIZE] = { };

//클래스
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
ScreenWord scword[INPUTMAX]; //화면에 나타날 단어

//클래스
class UserScore
{
public:
	static int fail; // 실패한 개수
	static int score; //점수
};
int UserScore::fail = 3;
int UserScore::score = 0;

//함수
void ReadFile2();
void RandomWord(int i); //단어와 x축을 랜덤으로 설정
int InputKey(int key, int &inlen, int stage_count, string &inword); //입력된 키가 어떤 키인지 구별
void CompareWords(string inword); //입력된 문자와 출력된 문자 비교
void UpdateScore(void); //점수 증가
void ProcessInput(int key, int &inlen, string &inword); //키 입력이 있을 경우 현재 입력된 문자열에 합쳐 줌
void Stage(double &fallspeed, int &stage_count, int &now); //stage에 갱신
void StageBoard(int a, double &fallspeed, int &stage_count, int &now); //스테이지 갱신시 출력
double GetDiffTime(clock_t start_time); // 시간 간격 알아내기(초 단위)
void EraseWord(int a); //화면에 출력된 글 지움
void UpdateFailCount(void); //실패 점수 증가
void DrawWord(int a); //화면에 출력
void InitScreen(int stage_count); //틀 출력