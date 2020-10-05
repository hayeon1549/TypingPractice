#include "word.h"

void WordRun(string texts[], int &tempAcc, int &tempTa, int a) 
{
	ScreenBasic myScreen1;
	ScreenUP myScreen2;

	const int size = wo_len;
	if (a == 2)
		const int size = ss_len; //배열에 저장된 행을 확인
	else if(a == 3)
		const int size = ls_len;

	string inword; //사용자 입력
	int index[size] = { 0 }; //지금까지 출력한 단어들의 인덱스를 저장하여 겹치지 않도록 비교함
	int sum1 = 0; //총 정확도
	int sum2 = 0; //총타수
	int avg1 = 0; //평균정확도 
	int avg2= 0; //평균타수
	int arr[size] = { 0 }; //표준 편차를 위한 평균 타수 저장
	int key = 0; //입력된 키
	int inlen = 0; //입력한 타자수를 저장
	int num = 0; //출력될 위치
	int sumTa = 0; //지금까지 완료한 총타수
	int typo = 0; //오타수
	int acc = 100; //정확도
	int forStop = 0; //esc키를 누르면 break
	int esc = 0; //inputkey 반환값
	int i = 0; //for문
	int five = 5; //긴 글 연습은 미리 5줄을 출력해놓고 그 후 5번동안 출력은 하지 않는다.
	int choice = 1; //긴 글 연습 선택
	int choice1 = 1; //인덱스에 숫자가 겹치지는지 확인

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
			WordPrint(texts[i], size, i, typo, acc, "낱말연습", num * 20 - 5, 17);
		else if (a == 2)
			WordPrint(texts[i], size, i, typo, acc, "짧은 글 연습", 1, 10 + num * 3);
		else {
			if (five == 5) {
				for (int j = 0; j < 5; j++) {
					WordPrint(texts[j], size, i, typo, acc, "긴 글 연습", 1, 10 + num * 3);
					num++;
				}

				num -= 5;
			}
		}

		unsigned int time = timeGetTime(); //시작 시간을 time에 복사

		while (true) {
			if (_kbhit()) { //키보드의 입력이 있다면
				key = getch();

				if (a == 1)
					esc = InputKeyW(key, inlen, inword, texts[i], num, num * 20 - 5, 17, 19);
				else
					esc = InputKeyW(key, inlen, inword, texts[i], num, 1, 10 + num * 3, 11 + num * 3);


				if (esc == 0) {//어떤 키가 입력됐는지 판별
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

		time = timeGetTime() - time; //딜레이 시간에서 현재 시간을 뺌

		float n = (float)60 / (time / 1000); //시작시간을 이용 1분 단위로 계산
		arr[i] = (int)n * inlen; //시간에서 입력한 타자수를 곱함
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
	cout << "진행도  |  " << round((double)i / size * 100) << "%";
	gotoxy(53, 8);
	cout << "오타수  |  " << typo << "타";
	gotoxy(96, 8); //숫자가 줄었을 때 원래 있던 cout을 지움
	cout << "  ";
	gotoxy(83, 8);
	cout << "정확도  |  " << acc << "%";

	textcolor(2, 15); //초록
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
		//만약 사용자가 끝까지 입력하지 않았다면 입력하지 않은 글자는 모두 오타로 간주하므로 빨간색으로 색을 변경함.
		if (inword.length() != printword.length()) {
			place = printword.length() - inword.length();

			for (int i = 0; i <= place; i++) {
				gotoxy(x + printword.length() - i, y1); //printword의 끝에서부터 접근
				textcolor(12, 15);
				cout << printword[printword.length() - i];
			}

			textcolor(0, 15);
		}

		return 0;
	}

	case KEY_BS: //Backspace 입력 내용 한 개씩 지움
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

	case KEY_ESC: //esc 종료
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

	//만약 사용자가 끝까지 입력하지 않았다면 입력하지 않은 글자는 모두 오타로 간주함
	if (inword.length() != printword.length()) {
		typo += printword.length() - inword.length();
		nowTypo += printword.length() - inword.length();
	}

	//오타수 측정
	for (int i = 0; i < inword.length(); i++) {
		if (inword[i] != printword[i]) {
			typo++;
			nowTypo++;
		}
	}

	//정확도
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
		textcolor(2, 15); //초록
		cout << printword[i];
		textcolor(0, 15);
	}

	for (int i = 0; i < inlen; i++) {
		if (inword[i] != printword[i]) {
			gotoxy(x + i, y);
			textcolor(12, 15); //빨강
			cout << printword[i];
			textcolor(0, 15);
		}
	}
}