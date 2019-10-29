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
		MessageBox(NULL, "파일을 불러오는데 실패했습니다.", "NOTICE", MB_OK);
	}

	in.close(); // 파일과의 연결을 닫음.
}

void SanRun()
{
	srand((unsigned)time(NULL)); //시간을 사용하여 난수가 겹치지 않도록 한다.

	string inword; // 입력 단어 저장
	int stage_count = 1; //stage
	int  now = 0;
	int temp = 1; //2/1의 확률로 now가 올라가게 해서 확률을 조절
	int cnt = 0; //2/1의 확률로 단어가 3개 이상 공백으로 나올시 다음에는 무조건 출력
	int key; //입력된 키의 아스키 코드값을 저장
	double fallspeed = 1.8; // 단어 낙하 시간
	int inlen = 0; // 입력 단어 길이

	//inword 초기화
	inword = "";
	//words 초기화
	ReadFile2();

	UserScore::fail = 3;
	UserScore::score = 0;

	SetCursorVisible(0); //커서를 안 보이게 함
	InitScreen(stage_count); //틀 출력

	while (true) {
		if (UserScore::fail == 0) {
			MessageBox(NULL, "산성비로 바닥이 오염되어\n도전에 실패하셨습니다.", "GAMEOVER", MB_OK);
			return;
		}

		if (temp == 1) {
			RandomWord(now); //words의 인덱스와 출력 위치 랜덤 배정
			temp = 0;
			cnt = 0;
		}

		while (true) {
			if (UserScore::score >= 8)
				Stage(fallspeed, stage_count, now);

			if (_kbhit()) { //키보드의 입력이 있다면
				key = getch();

				if (InputKey(key, inlen, stage_count, inword) == 0) //어떤 키가 입력됐는지 판별
					return;
			}

			if (GetDiffTime(start_time) >= fallspeed) { //떨어지는 속도를 넘었다면
				for (int i = 0; i < now; i++) {
					if (scword[i].index != 0) { //index가 사이즈를 넘었다면 이미 맞춘 단어이므로 넘어감
						EraseWord(i); //밑으로 내려올 때 이전에 프린트 됐던 부분을 지워줌 
						if (scword[i].y == 19) { //단어가 19번째 줄까지 왔을 때 = 바닥에 닿았을 때
							UserScore::fail--;
							UpdateFailCount();
							scword[i].index = 0;
						}
						else {
							if (scword[i].x > 1 && scword[i].y != 19) {
								scword[i].y++;
								DrawWord(i);
							} //if 끝
						} //else 끝
					}//for 끝
				} //if 끝
				start_time = clock();
				break;
			} //if 끝
		} //while 끝
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
	}//while 끝
}//함수 끝

void RandomWord(int now)
{
	scword[now].x = rand() % 100; //랜덤 x좌표
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
	case KEY_ENTER: //Enter 내용 전체 지움
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

	case KEY_BS: //Backspace 입력 내용 한 개씩 지움
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

	case KEY_ESC: //esc 종료
	{
		return 0;
	}

	case KEY_SP: //spacebar 멈추기
	{
		int getget; //정지상태에서 입력받을 변수

		system("cls");
		gotoxy(51, 12);	cout << "잠시 멈추셨습니다.";
		gotoxy(40, 14);	cout << "게임을 계속하시려면 spacebar를 눌러주세요.";
		gotoxy(33, 16);	cout << "게임이 재시작되면 입력을 위해 enter를 한 번 눌러주세요.";

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

void CompareWords(string inword)//화면에 출력된 단어들 중에 입력 단어와 일치하는 단어가 있는지 검사하고 일치하는 단어가 있다면 삭제 및 점수 갱신
{
	for (int i = 0; i < INPUTMAX; i++) {
		if (scword[i].y > 0 && scword[i].y < 19) {
			if (scword[i].index != 0) {
				gotoxy(0, 0);

				if (inword == words[scword[i].index]) {  //두 문자열이 같으면
					putch(BELL); //소리를 냄
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
		MessageBox(NULL, "승리를 축하합니다!\n\n게임을 종료하시려면 OK 버튼을 눌러주세요.", "COGRATURATION", MB_OK);
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
	gotoxy(43, 14);	cout << "다음 Stage를 시작하려면 아무키나 치세요.";
	system("pause > null");
	stage_count++;

	textcolor(0, 15);
	system("cls");
	InitScreen(stage_count);
}

double GetDiffTime(clock_t start_time)
{
	clock_t cur_time;
	cur_time = clock(); //현재 시각
	return ((double)(cur_time - start_time) / CLOCKS_PER_SEC); //현재시간 - 시작
}

void EraseWord(int a) //프린트된 곳에서 지우기
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

void SetCursorVisible(BOOL tf)	// 화면 커서를 On/Off
{
	CONSOLE_CURSOR_INFO ci = { 10, tf };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void InitScreen(int stage_count)
{
	cout << "┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐ \n";
	for (int i = 0; i < 19; i++)
		cout << "│                                                                                                                     │ \n";
	cout << "└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘ \n";

	cout << "┌──────────────────────┐ \n";
	cout << "│  Programmed by GSM   │ \n";
	cout << "└──────────────────────┘ ";
	//입력칸
	gotoxy(INPUTCAN - 5, 22); cout << "입력";
	gotoxy(INPUTCAN, 21); cout << "┌─────────────────────┐ \n";
	gotoxy(INPUTCAN, 22);  cout << "│                     │ \n";
	gotoxy(INPUTCAN, 23); cout << "└─────────────────────┘ ";
	//stage
	gotoxy(STAGECAN - 6, 22); cout << "STAGE";
	gotoxy(STAGECAN, 21); cout << "┌────┐ \n";
	gotoxy(STAGECAN, 22); printf("│  %d │ \n", stage_count);
	gotoxy(STAGECAN, 23); cout << "└────┘ ";
	//성공 횟수
	gotoxy(SCORECAN - 8, 22); cout << "SUCCESS";
	gotoxy(SCORECAN, 21); cout << "┌────┐ \n";
	gotoxy(SCORECAN, 22); printf("│  %d │ \n", UserScore::score);
	gotoxy(SCORECAN, 23); cout << "└────┘ ";
	// 실패 횟수
	gotoxy(FAILCAN - 5, 22); cout << "LIFE";
	gotoxy(FAILCAN, 21); cout << "┌────┐ \n";
	gotoxy(FAILCAN, 22); printf("│  %d │ \n", UserScore::fail);
	gotoxy(FAILCAN, 23); cout << "└────┘ ";
}