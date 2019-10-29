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
		gotoxy(57, 2); cout << "������������������ \n";
		gotoxy(57, 3); cout << "��  ��� ��  \n";
		gotoxy(57, 4); cout << "������������������ ";

		gotoxy(54, 7);
		cout << "��Ÿ��  |  " << sumTa << "Ÿ";
		gotoxy(54, 9);
		cout << "��Ÿ��  |  " << typo << "Ÿ";
		gotoxy(54, 11);
		cout << "��Ȯ��  |  " << avg1 << "%";
		gotoxy(52, 13);
		cout << "���Ÿ��  |  " << avg2 << "Ÿ";
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
		cout << "������";
		gotoxy(54, 25);
		cout << "����ϱ�";

		choice = select(65, 23, 25);

		if (choice == 23)
			choice = 0;
		else
			choice = 1;
	}
};
