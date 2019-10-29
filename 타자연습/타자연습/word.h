#include "same.h"
#include <cmath>

void WordPrint(string printword, int size, int i, int typo, int acc, string title, int x, int y);
int InputKeyW(int key, int &inlen, string &inword, string printword, int num, int x, int y1, int y2);
void AccuracyWords(string inword, string printword, int & typo, int &acc);
void ProcessInputW(int key, int &inlen, string &inword, int x, int y);
void CompareWordsW(string inword, string printword, int inlen, int num, int x, int y);

class ScreenBasic {
public:
	void Screen(int &avg1, int &avg2, int sum1, int sum2, int i, int sumTa, int typo, int &choice)
	{
		avg1 = sum2 / i;
		avg2 = sum1 / i;

		system("cls");
		gotoxy(57, 2); cout << "┌───────┐ \n";
		gotoxy(57, 3); cout << "│  결과 │  \n";
		gotoxy(57, 4); cout << "└───────┘ ";

		gotoxy(54, 7);
		cout << "총타수  |  " << sumTa << "타";
		gotoxy(54, 9);
		cout << "오타수  |  " << typo << "타";
		gotoxy(54, 11);
		cout << "정확도  |  " << avg1 << "%";
		gotoxy(52, 13);
		cout << "평균타수  |  " << avg2 << "타";
	}
};

class ScreenUP : public ScreenBasic{
public:
	void Screen(int &avg1, int &avg2, int sum1, int sum2, int i, int sumTa, int typo, int &choice)
	{
		ScreenBasic::Screen(avg1, avg2, sum1, sum2, i, sumTa, typo, choice);

		gotoxy(0, 18);
		line();

		gotoxy(54, 23);
		cout << "나가기";
		gotoxy(54, 25);
		cout << "계속하기";

		choice = select(65, 23, 25);

		if (choice == 23)
			choice = 0;
		else
			choice = 1;
	}
};
