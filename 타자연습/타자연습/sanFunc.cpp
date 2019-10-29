#include "san.h"

void ReadFile2()
{
	ifstream in("san.txt");
	string s;
	int counts = 0;

	if (in.is_open()) {
		while (counts!=WORDSSIZE-1) {
			counts++;
			getline(in, s);
			words[counts] = s;
		}
	}
	else {
		MessageBox(NULL, "������ �ҷ����µ� �����߽��ϴ�.", "NOTICE", MB_OK);
	}

	in.close(); // ���ϰ��� ������ ����.
}

void SanRun()
{
	srand((unsigned)time(NULL)); //�ð��� ����Ͽ� ������ ��ġ�� �ʵ��� �Ѵ�.

	string inword; // �Է� �ܾ� ����
	int stage_count = 1; //stage
	int  now = 0;
	int temp = 1; //2/1�� Ȯ���� now�� �ö󰡰� �ؼ� Ȯ���� ����
	int cnt = 0; //2/1�� Ȯ���� �ܾ 3�� �̻� �������� ���ý� �������� ������ ���
	int key; //�Էµ� Ű�� �ƽ�Ű �ڵ尪�� ����
	double fallspeed = 1.8; // �ܾ� ���� �ð�
	int inlen = 0; // �Է� �ܾ� ����

	//inword �ʱ�ȭ
	inword = "";
	//words �ʱ�ȭ
	ReadFile2();

	UserScore::fail = 3;
	UserScore::score = 0;

	SetCursorVisible(0); //Ŀ���� �� ���̰� ��
	InitScreen(stage_count); //Ʋ ���

	while (true) {
		if (UserScore::fail == 0) {
			MessageBox(NULL, "�꼺��� �ٴ��� �����Ǿ�\n������ �����ϼ̽��ϴ�.", "GAMEOVER", MB_OK);
			return;
		}

		if (temp == 1) {
			RandomWord(now); //words�� �ε����� ��� ��ġ ���� ����
			temp = 0;
			cnt = 0;
		}

		while (true) {
			if (UserScore::score >= 8)
				Stage(fallspeed, stage_count, now);

			if (_kbhit()) { //Ű������ �Է��� �ִٸ�
				key = getch();

				if (InputKey(key, inlen, stage_count, inword) == 0) //� Ű�� �Էµƴ��� �Ǻ�
					return;
			}

			if (GetDiffTime(start_time) >= fallspeed) { //�������� �ӵ��� �Ѿ��ٸ�
				for (int i = 0; i < now; i++) {
					if (scword[i].index != 0) { //index�� ����� �Ѿ��ٸ� �̹� ���� �ܾ��̹Ƿ� �Ѿ
						EraseWord(i); //������ ������ �� ������ ����Ʈ �ƴ� �κ��� ������ 
						if (scword[i].y == 19) { //�ܾ 19��° �ٱ��� ���� �� = �ٴڿ� ����� ��
							UserScore::fail--;
							UpdateFailCount();
							scword[i].index = 0;
						}
						else {
							if (scword[i].x > 1 && scword[i].y != 19) {
								scword[i].y++;
								DrawWord(i);
							} //if ��
						} //else ��
					}//for ��
				} //if ��
				start_time = clock();
				break;
			} //if ��
		} //while ��
		if (cnt >= 2) {
			now++;
			temp = 1;
		}
		else {
			if (rand() % 2 == 0) {
				now++;
				temp = 1;
			}
			else {
				cnt++;
			}
		}
	}//while ��
}//�Լ� ��

void RandomWord(int now)
{
	scword[now].x = rand() % 100; //���� x��ǥ
	scword[now].y = 0;
	scword[now].index = rand() % (WORDSSIZE - 2) + 1;

	for (int i = 0; i < now; i++) {
		if (scword[i].index == scword[now].index)
			RandomWord(now);
	}
}

int InputKey(int key, int &inlen, int stage_count, string &inword)
{
	switch (key)
	{
	case KEY_ENTER: //Enter ���� ��ü ����
	{
		CompareWords(inword);
		for (int i = 0; i < inlen; i++) {
			gotoxy((INPUTCAN + 2) + i, 22);
			cout << " ";
		}
		for (int i = 0; i < inlen; i++)
			inword = "";
		inlen = 0;
		break;
	}

	case KEY_BS: //Backspace �Է� ���� �� ���� ����
	{
		if (inlen > 0)
		{
			inlen--;
			gotoxy((INPUTCAN + 2) + inlen, 22);
			cout << " ";
			inword.pop_back();
		}
		break;
	}

	case KEY_ESC: //esc ����
	{
		return 0;
	}

	case KEY_SP: //spacebar ���߱�
	{
		int getget; //�������¿��� �Է¹��� ����

		system("cls");
		gotoxy(51, 12);	cout << "��� ���߼̽��ϴ�.";
		gotoxy(40, 14);	cout << "������ ����Ͻ÷��� spacebar�� �����ּ���.";
		gotoxy(33, 16);	cout << "������ ����۵Ǹ� �Է��� ���� enter�� �� �� �����ּ���.";

		getget = getch();
		if (getget == KEY_SP) {
			system("cls");
			InitScreen(stage_count);
		}
		else {
			InputKey(KEY_SP, inlen, stage_count, inword);
		}

		return 1;
	}
	default:
	{
		ProcessInput(key, inlen, inword);
		break;
	}
	}
}

void CompareWords(string inword)//ȭ�鿡 ��µ� �ܾ�� �߿� �Է� �ܾ�� ��ġ�ϴ� �ܾ �ִ��� �˻��ϰ� ��ġ�ϴ� �ܾ �ִٸ� ���� �� ���� ����
{
	for (int i = 0; i < INPUTMAX; i++) {
		if (scword[i].y > 0 && scword[i].y < 19) {
			if (scword[i].index != 0) {
				gotoxy(0, 0);

				if (inword == words[scword[i].index]) {  //�� ���ڿ��� ������
					putch(BELL); //�Ҹ��� ��
					EraseWord(i);
					scword[i].index = 0;
					UserScore::score++;
					UpdateScore();
				}
			}
		}
	}
}

void UpdateScore(void)
{
	gotoxy((SCORECAN + 3), 22);
	cout << UserScore::score;
}

void ProcessInput(int key, int &inlen, string &inword)
{
	char temp1 = key;
	string temp2(1, temp1);

	if (inlen < 20)
	{
		gotoxy((INPUTCAN + 2) + inlen, 22);
		cout << temp2;
		inword+=temp2; 

		inlen++;
	}
}

void Stage(double &fallspeed, int &stage_count, int &now)
{
	if (UserScore::score == 10 && stage_count == 1) {
		StageBoard(9, fallspeed, stage_count, now);
	}
	else if (UserScore::score == 10 && stage_count == 2) {
		StageBoard(10, fallspeed, stage_count, now);
	}
	else if (UserScore::score == 9 && stage_count == 3) {
		StageBoard(11, fallspeed, stage_count, now);
	}
	else if (UserScore::score == 9 && stage_count == 4) {
		StageBoard(12, fallspeed, stage_count, now);
	}
	else if (stage_count == 5) {
		StageBoard(13, fallspeed, stage_count, now);
	}
	else if (stage_count == 6) {
		MessageBox(NULL, "�¸��� �����մϴ�!\n\n������ �����Ͻ÷��� OK ��ư�� �����ּ���.", "COGRATURATION", MB_OK);
	}
}

void StageBoard(int a, double &fallspeed, int &stage_count, int &now)
{
	now = 0;
	UserScore::score = 0;
	UserScore::fail = 3;
	fallspeed -= 0.2;
	textcolor(15, a);
	for (int i = 0; i < 20; i++)
		scword[i].Reset();

	system("cls");
	gotoxy(48, 12);	printf("====== STAGE %d clear ======", stage_count);
	gotoxy(43, 14);	cout << "���� Stage�� �����Ϸ��� �ƹ�Ű�� ġ����.";
	system("pause > null");
	stage_count++;

	textcolor(0, 15);
	system("cls");
	InitScreen(stage_count);
}

double GetDiffTime(clock_t start_time)
{
	clock_t cur_time;
	cur_time = clock(); //���� �ð�
	return ((double)(cur_time - start_time) / CLOCKS_PER_SEC); //����ð� - ����
}

void EraseWord(int a) //����Ʈ�� ������ �����
{
	if (scword[a].y > 0)
	{
		gotoxy(scword[a].x, scword[a].y);
		for (int i = 0; i < words[scword[a].index].length(); i++)
			cout << " ";
	}
}

void UpdateFailCount(void)
{
	gotoxy((FAILCAN + 3), 22);
	cout << UserScore::fail;
}

void DrawWord(int a)
{
	gotoxy(scword[a].x, scword[a].y);
	cout << words[scword[a].index];
}

void SetCursorVisible(BOOL tf)	// ȭ�� Ŀ���� On/Off
{
	CONSOLE_CURSOR_INFO ci = { 10, tf };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void InitScreen(int stage_count)
{
	cout << "���������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������� \n";
	for (int i = 0; i < 19; i++)
		cout << "��                                                                                                                     �� \n";
	cout << "���������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������� \n";

	cout << "������������������������������������������������ \n";
	cout << "��  Programmed by GSM   �� \n";
	cout << "������������������������������������������������ ";
	//�Է�ĭ
	gotoxy(INPUTCAN - 5, 22); cout << "�Է�";
	gotoxy(INPUTCAN, 21); cout << "���������������������������������������������� \n";
	gotoxy(INPUTCAN, 22);  cout << "��                     �� \n";
	gotoxy(INPUTCAN, 23); cout << "���������������������������������������������� ";
	//stage
	gotoxy(STAGECAN - 6, 22); cout << "STAGE";
	gotoxy(STAGECAN, 21); cout << "������������ \n";
	gotoxy(STAGECAN, 22); printf("��  %d �� \n", stage_count);
	gotoxy(STAGECAN, 23); cout << "������������ ";
	//���� Ƚ��
	gotoxy(SCORECAN - 8, 22); cout << "SUCCESS";
	gotoxy(SCORECAN, 21); cout << "������������ \n";
	gotoxy(SCORECAN, 22); printf("��  %d �� \n", UserScore::score);
	gotoxy(SCORECAN, 23); cout << "������������ ";
	// ���� Ƚ��
	gotoxy(FAILCAN - 5, 22); cout << "LIFE";
	gotoxy(FAILCAN, 21); cout << "������������ \n";
	gotoxy(FAILCAN, 22); printf("��  %d �� \n", UserScore::fail);
	gotoxy(FAILCAN, 23); cout << "������������ ";
}