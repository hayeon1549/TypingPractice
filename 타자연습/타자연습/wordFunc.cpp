#include "word.h"

void WordRun(string texts[], int &tempAcc, int &tempTa, int a) 
{
	ScreenBasic myScreen1;
	ScreenUP myScreen2;

	const int size = wo_len;
	if (a == 2)
		const int size = ss_len; //�迭�� ����� ���� Ȯ��
	else if(a == 3)
		const int size = ls_len;

	string inword; //����� �Է�
	int index[size] = { 0 }; //���ݱ��� ����� �ܾ���� �ε����� �����Ͽ� ��ġ�� �ʵ��� ����
	int sum1 = 0; //�� ��Ȯ��
	int sum2 = 0; //��Ÿ��
	int avg1 = 0; //�����Ȯ�� 
	int avg2= 0; //���Ÿ��
	int arr[size] = { 0 }; //ǥ�� ������ ���� ��� Ÿ�� ����
	int key = 0; //�Էµ� Ű
	int inlen = 0; //�Է��� Ÿ�ڼ��� ����
	int num = 0; //��µ� ��ġ
	int sumTa = 0; //���ݱ��� �Ϸ��� ��Ÿ��
	int typo = 0; //��Ÿ��
	int acc = 100; //��Ȯ��
	int forStop = 0; //escŰ�� ������ break
	int esc = 0; //inputkey ��ȯ��
	int i = 0; //for��
	int five = 5; //�� �� ������ �̸� 5���� ����س��� �� �� 5������ ����� ���� �ʴ´�.
	int choice = 1; //�� �� ���� ����
	int choice1 = 1; //�ε����� ���ڰ� ��ġ������ Ȯ��

	SetCursorVisible(0);

	for (i = 0; i < size; i++) {
		choice1 = 1;
		inlen = 0;
		inword = "";

		if (num == 5) {
			num = 0;
			system("cls");
		}
		num++;

		
		
		if (a == 1)
			WordPrint(texts[i], size, i, typo, acc, "��������", num * 20 - 5, 17);
		else if (a == 2)
			WordPrint(texts[i], size, i, typo, acc, "ª�� �� ����", 1, 10 + num * 3);
		else {
			if (five == 5) {
				for (int j = 0; j < 5; j++) {
					WordPrint(texts[j], size, i, typo, acc, "�� �� ����", 1, 10 + num * 3);
					num++;
				}

				num -= 5;
			}
		}

		unsigned int time = timeGetTime(); //���� �ð��� time�� ����

		while (true) {
			if (_kbhit()) { //Ű������ �Է��� �ִٸ�
				key = getch();

				if (a == 1)
					esc = InputKeyW(key, inlen, inword, texts[i], num, num * 20 - 5, 17, 19);
				else
					esc = InputKeyW(key, inlen, inword, texts[i], num, 1, 10 + num * 3, 11 + num * 3);


				if (esc == 0) {//� Ű�� �Էµƴ��� �Ǻ�
					AccuracyWords(inword, texts[i], typo, acc);
					break;
				}
				else if (esc == 1) {
					forStop = 1;
					break;
				}
			}
		}

		if (forStop == 1)
			break;

		time = timeGetTime() - time; //������ �ð����� ���� �ð��� ��

		float n = (float)60 / (time / 1000); //���۽ð��� �̿� 1�� ������ ���
		arr[i] = (int)n * inlen; //�ð����� �Է��� Ÿ�ڼ��� ����
		sum1 += arr[i];
		sum2 += acc;
		sumTa += texts[i].length();
		five--;
		if (a == 3) {
			if (five == 0) {
				myScreen2.Screen(avg1, avg2, sum1, sum2, i, sumTa, typo, choice);

				if (choice == 0)
					break;
				else
					five = 5;
			}
		}
	}
	if (a != 3) {
		myScreen1.Screen(avg1, avg2, sum1, sum2, i, sumTa, typo, choice);
		Sleep(3000);
	}

	tempAcc = avg1;
	tempTa = avg2;
}

void WordPrint(string printword, int size, int i, int typo, int acc, string title, int x, int y)
{
	gotoxy(0, 2);
	line();
	gotoxy(56, 4);
	cout << title;
	gotoxy(0, 6);
	line();

	gotoxy(23, 8);
	cout << "���൵  |  " << round((double)i / size * 100) << "%";
	gotoxy(53, 8);
	cout << "��Ÿ��  |  " << typo << "Ÿ";
	gotoxy(96, 8); //���ڰ� �پ��� �� ���� �ִ� cout�� ����
	cout << "  ";
	gotoxy(83, 8);
	cout << "��Ȯ��  |  " << acc << "%";

	textcolor(2, 15); //�ʷ�
	gotoxy(x, y);
	cout << printword;
	textcolor(0, 15);
}

int InputKeyW(int key, int &inlen, string &inword, string printword, int num, int x, int y1, int y2)
{
	int place = 0;

	switch (key)
	{
	case KEY_ENTER:
	{	
		//���� ����ڰ� ������ �Է����� �ʾҴٸ� �Է����� ���� ���ڴ� ��� ��Ÿ�� �����ϹǷ� ���������� ���� ������.
		if (inword.length() != printword.length()) {
			place = printword.length() - inword.length();

			for (int i = 0; i <= place; i++) {
				gotoxy(x + printword.length() - i, y1); //printword�� ���������� ����
				textcolor(12, 15);
				cout << printword[printword.length() - i];
			}

			textcolor(0, 15);
		}

		return 0;
	}

	case KEY_BS: //Backspace �Է� ���� �� ���� ����
	{
		if (inlen > 0)
		{
			inlen--;
			gotoxy(x + inlen, y2);
			cout << " ";
			inword.pop_back();

			CompareWordsW(inword, printword, inlen, num, x, y1);
		}

		break;
	}

	case KEY_ESC: //esc ����
	{
		return 1;
	}

	default:
	{
		if (inlen < printword.length()) {
			ProcessInputW(key, inlen, inword, x, y2);
			CompareWordsW(inword, printword, inlen, num, x, y1);
		}
		
		break;
	}
	}

	return 2;
}

void AccuracyWords(string inword, string printword, int &typo, int &acc)
{
	int nowTypo = 0;

	//���� ����ڰ� ������ �Է����� �ʾҴٸ� �Է����� ���� ���ڴ� ��� ��Ÿ�� ������
	if (inword.length() != printword.length()) {
		typo += printword.length() - inword.length();
		nowTypo += printword.length() - inword.length();
	}

	//��Ÿ�� ����
	for (int i = 0; i < inword.length(); i++) {
		if (inword[i] != printword[i]) {
			typo++;
			nowTypo++;
		}
	}

	//��Ȯ��
	acc =100 - (round((double)nowTypo / printword.length() * 100));
}

void ProcessInputW(int key, int &inlen, string &inword, int x, int y)
{
	char temp1 = key;
	string temp2(1, temp1);

	gotoxy(x + inlen, y);
	cout << temp2;
	inword += temp2;

	inlen++;
}

void CompareWordsW(string inword, string printword, int inlen, int num, int x, int y)
{
	for (int i = 0; i < printword.length(); i++) {
		gotoxy(x + i, y);
		textcolor(2, 15); //�ʷ�
		cout << printword[i];
		textcolor(0, 15);
	}

	for (int i = 0; i < inlen; i++) {
		if (inword[i] != printword[i]) {
			gotoxy(x + i, y);
			textcolor(12, 15); //����
			cout << printword[i];
			textcolor(0, 15);
		}
	}
}