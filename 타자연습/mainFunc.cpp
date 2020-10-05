#include "main.h"

void Start(void)
{
	PlaySound(NULL, 0, 0);

	MessageBox(NULL, "Choose what you want to practice.\n\nIf you want exit while you're praticing, type exit.\n\nProgrammed by 정상현, 홍하연.\n\n(C)Copyright 2019 Project 'GSM'", "타자연습 설명서", MB_OK | MB_ICONINFORMATION);
	//[속성]-[구성 속성]-[일반]-프로젝트 기본값-[문자 집합]-멀티바이트 문자 집합 사용 설정

	//system("mode con:cols=120 lines=30"); //콘솔 창 크기 지정
	system("title 프로그래밍과 함께 하는 타자연습");
	system("color f0"); //콘솔 창 색상 지정
	SetCursorVisible(0);

	for (int i = 0; i < 5; i++) {
		textcolor(i + 9, 15);
		gotoxy(30, 7);
		cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□";
		gotoxy(30, 8);
		cout << "■■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□";
		gotoxy(30, 9);
		cout << "□□■□□□□□□□□□□□□□□□■□□□□□□□□□□□□";
		gotoxy(30, 10);
		cout << "□□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□";
		gotoxy(30, 11);
		cout << "□□■□□□□■□□■□■■■■□□■□■□■■□□□■■■■";
		gotoxy(30, 12);
		cout << "□□■□□□□■□□■□■□□□■□■□■■□□■□■□□□■";
		gotoxy(30, 13);
		cout << "□□■□□□□■□□■□■□□□■□■□■□□□■□■□□□■";
		gotoxy(30, 14);
		cout << "□□■□□□□■□□■□■□□□■□■□■□□□■□■□□□■";
		gotoxy(30, 15);
		cout << "□□■□□□□□■■□□■□□□■□■□■□□□■□■□□□■";
		gotoxy(30, 16);
		cout << "□□■□□□□□■□□□■■■■□□■□■□□□■□□■■■■";
		gotoxy(30, 17);
		cout << "□□□□□□□□■□□□■□□□□□□□□□□□□□□□□□■";
		gotoxy(30, 18);
		cout << "□□□□□□■■□□□□■□□□□□□□□□□□□□■■■■□";
		Sleep(300);
		system("cls");
	}

	textcolor(0, 15);
}

BasicInfo ManInfo(int &use) {
	BasicInfo Man[4];

	int condition1 = 1; //while문 반복 조건, messagebox
	int condition2 = 1; //while문 반복 조건(환경설정), messagebox
	int count = 0; //사용자 수 카운트
	int choice1 = 0; //사용자 정보 switch
	int choice2 = 0; //사용자 선택, 삭제 ifelse
	int i = 0; //for문
	int data = 0; //목표 타수, 정확도를 입력받을 변수
	int choice3 = 0; //사용자 정보 확인 창 나가기/수정하기

	//사용자 정보 초기화
	FileInC(count);
	for (int i = 1; i <= count; i++) {
		if(i == 1)
			FileInU(Man[i], "User1.txt");
		else if(i == 2)
			FileInU(Man[i], "User2.txt");
		else
			FileInU(Man[i], "User3.txt");
	}
		

	while (condition1 == 1) {
		system("cls");
		gotoxy(0, 2);
		line();
		gotoxy(54, 4);
		cout << "사용자 정보" << endl;
		gotoxy(0, 6);
		line();

		gotoxy(45, 10);
		cout << "(1) 사용자 선택하기";
		gotoxy(45, 12);
		cout << "(2) 사용자 생성하기";
		gotoxy(45, 14);
		cout << "(3) 사용자 삭제하기";
		choice1 = select(73, 10, 14);
		system("cls");

		//nameList 초기화(name이 겹치지 않도록 하기 위함)
		for (int i = 0; i <= count; i++)
			nameList[i] = Man[i].GetNa();
		for (int i = count + 1; i < 3; i++)
			nameList[i] = "";

		switch (choice1)
		{
		case 10: //사용자 선택하기
		{
			gotoxy(52, 7);
			cout << "<사용자 선택하기>";
			for (i = 0; i <= count; i++) {
				gotoxy(51, 10 + 2 * i);
				cout << "(" << i + 1 << ") " << Man[i].GetNa();
			}

			choice2 = select(68, 10, 8 + 2 * i);
			if (choice2 == 10)
				use = 0;
			else if (choice2 == 12)
				use = 1;
			else if (choice2 == 14)
				use = 2;
			else 
				use = 3;

			if(use == 0)
				condition1 = MessageBox(NULL, "기본 사용자를 선택할 경우\n사용자 정보가 저장되지 않습니다.", "CONFIRM", MB_OKCANCEL | MB_ICONQUESTION);
			else
				condition1 = MessageBox(NULL, "타자연습을 시작합니다.", "CONFIRM", MB_OKCANCEL | MB_ICONQUESTION);

			if (condition1 == IDOK) { //OK를 누르면
				condition1 = 0; //while문 나감
			}
			else {
				condition1 = 1;
			}
			break;
		}

		case 12: //사용자 생성하기
		{
			MessageBox(NULL, "사용자 이름은 중복될 수 없으며\n\"Man\", \"MAN\" 사용도 불가합니다.\n사용자 이름은 최대 10자리까지 가능합니다.", "NOTICE", MB_OK);

			if (count == 3) {
				MessageBox(NULL, "사용자는 최대 3명까지 생성할 수 있습니다.", "NOTICE", MB_OK);
				break;
			}

			count++;

			gotoxy(52, 7);
			cout << "<사용자 생성하기>";
			gotoxy(49, 10);
			cout << "사용자 이름 >> ";
			Man[count].SetNa(64, 10);

			gotoxy(49, 12);
			cout << "목표 타수   >> ";
			cin >> data;
			Man[count].SetGT(data, 64, 12);

			gotoxy(49, 14);
			cout << "목표 정확도 >> ";
			cin >> data;
			Man[count].SetGA(data, 64, 14);

			gotoxy(41, 18);
			cout << "성공적으로 사용자 정보가 생성되었습니다!";
			Sleep(1000);

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			break;
		}

		case 14: //사용자 삭제하기
		{
			if (count == 0) {
				MessageBox(NULL, "삭제할 사용자가 없습니다.", "NOTICE", MB_OK);
				break;
			}

			gotoxy(52, 7);
			cout << "<사용자 삭제하기>";
			for (i = 1; i <= count; i++) { //기본으로 생성되어 있는 Man은 지우지 못함
				if (Man[i].GetNa() != "Man") { //만약 정보를 삭제했다면 이름이 Man으로 바뀌므로
					gotoxy(51, 8 + 2 * i);
					cout << "(" << i  << ") " << Man[i].GetNa();
				}
			}
			choice2 = select(68, 10, 6 + 2 * i);

			if (choice2 == 10) {
				Man[1] = Man[2];
			}
			Man[2] = Man[3];
			Man[3].Reset();

			count--;

			gotoxy(40, 18);
			cout << "성공적으로 사용자 정보가 삭제되었습니다!";
			Sleep(1000);
			break;
		} //case 끝
		} //switch 끝
	} //while 끝

	//사용자 정보 파일에 저장
	FileOutC(count);
	for (int i = 1; i <= count; i++) {
		if (i == 1)
			FileOutU(Man[i], "User1.txt");
		else if (i == 2)
			FileOutU(Man[i], "User2.txt");
		else
			FileOutU(Man[i], "User3.txt");
	}

	return Man[use];
}

void FileInC(int &count)
{
	ifstream in("Count.txt");
	string s;

	if (in.is_open()) {
		getline(in, s);
		count = atoi(s.c_str());
	}

	in.close();
}

void FileInU(BasicInfo &Man, string a)
{
	ifstream in(a);

	string s;

	if (in.is_open()) {
		for(int i= 0; !in.eof(); i++){
			getline(in, s);

			if(i == 0)
				Man.SetNa2(s);
			if(i == 1)
				Man.SetGT2(atoi(s.c_str()));
			if(i == 2)
				Man.SetGA2(atoi(s.c_str()));
			if(i == 3)
				Man.SetAT(atoi(s.c_str()));
			if(i == 4)
				Man.SetAA(atoi(s.c_str()));
			if (i == 5) {
				if (s == "OFF")
					Man.SetVo(0);
				else
					Man.SetVo(1);
			}
		}
	}
	else {
		MessageBox(NULL, "파일을 불러오는데 실패했습니다.", "NOTICE", MB_OK);
	}

	in.close();
}

void FileOutC(int count)
{
	ofstream out("Count.txt", ios::trunc);
	if(out.is_open())
		out << count << endl;
	else
		MessageBox(NULL, "파일을 불러오는데 실패했습니다.", "NOTICE", MB_OK);

	out.close();
}

void FileOutU(BasicInfo Man, string a)
{
	ofstream out(a, ios::trunc);

	if (out.is_open()) {
		out << Man.GetNa() << endl;
		out << Man.GetGT() << endl;
		out << Man.GetGA() << endl;
		out << Man.GetAT() << endl;
		out << Man.GetAA() << endl;
		out << Man.GetVo() << endl;
	}

	out.close();
}

void MenuLang(FileInfo &Text)
{
	system("cls");
	int input;
	int condition;

	gotoxy(0, 2);
	line();
	gotoxy(56, 4);
	cout << "언어 선택";
	gotoxy(0, 6);
	line();

	gotoxy(50, 10);
	cout << "(1) C";
	gotoxy(50, 12);
	cout << "(2) C++";
	gotoxy(50, 14);
	cout << "(3) Python";
	gotoxy(50, 16);
	cout << "(4) Java";
	gotoxy(50, 18);
	cout << "(5) Html";
	input = select(70, 10, 18);
	system("cls");

	if (input == 10) {
		ReadFile(Text, "C_wo.txt", 1);
		ReadFile(Text, "C_ss.txt", 2);
		ReadFile(Text, "C_ls.txt", 3);
	}
	else if (input == 12) {
		ReadFile(Text, "C++_wo.txt", 1);
		ReadFile(Text, "C++_ss.txt", 2);
		ReadFile(Text, "C++_ls.txt", 3);
	}
	else if (input == 14) {
		ReadFile(Text, "Python_wo.txt", 1);
		ReadFile(Text, "Python_ss.txt", 2);
		ReadFile(Text, "Python_ls.txt", 3);
	}
	else if(input == 16) {
		ReadFile(Text, "Java_wo.txt", 1);
		ReadFile(Text, "Java_ss.txt", 2);
		ReadFile(Text, "Java_ls.txt", 3);
	}
	else {
		ReadFile(Text, "Html_wo.txt", 1);
		ReadFile(Text, "Html_ss.txt", 2);
		ReadFile(Text, "Html_ls.txt", 3);
	}

	condition = MessageBox(NULL, "언어를 선택합니다.", "CONFIRM", MB_OKCANCEL | MB_ICONQUESTION);

	if (condition == IDCANCEL) { //취소를 누르면
		MenuLang(Text);
	}
}

void ReadFile(FileInfo &Text, string data, int len)
{
	ifstream ifs; // ifs라는 ifstream 객체를 생성함.
	string str;

	ifs.open(data); // ifs를 data와 연결함.

	for (int i = 0; !ifs.eof(); i++){
		if (!ifs.is_open()) {
			MessageBox(NULL, "파일을 불러오는데 실패했습니다.", "NOTICE", MB_OK);
			MenuLang(Text);
		}
		else {
			getline(ifs, str);
			if (len == 1) 
				Text.wo[i] = str;
			else if (len == 2) 
				Text.ss[i] = str;
			else
				Text.ls[i] = str;
		}
	}
	ifs.close(); // 파일과의 연결을 닫음.
}


void MenuWay(BasicInfo &Man, FileInfo Text)
{
	int input;
	int sanstart = 0;
	int whileout = 0;
	int exitconfirm = 0;
	int tempAcc = 0; //정확도를 임시로 저장
	int tempTa = 0; //타속을 임시로 저장

	while (whileout == 0) {
		system("cls");
		gotoxy(0, 2);
		line();
		gotoxy(43, 4);
		cout << "프로그래밍과 함께하는 타자연습";
		gotoxy(0, 6);
		line();

		gotoxy(50, 10);
		cout << "(1) 낱말 연습";
		gotoxy(50, 12);
		cout << "(2) 짧은 글 연습";
		gotoxy(50, 14);
		cout << "(3) 긴 글 연습";
		gotoxy(50, 16);
		cout << "(4) 산성비";
		gotoxy(50, 18);
		cout << "(5) 환경설정";
		gotoxy(50, 20);
		cout << "(6) 언어 재선택";
		gotoxy(50, 22);
		cout << "(7) 종료";
		input = select(70, 10, 22);

		system("cls");

		switch (input)
		{
		case 10: //낱말 연습
			WordRun(Text.wo, tempAcc, tempTa, 1);
			Man.SetAA(tempAcc);
			Man.SetAT(tempTa);
			break;

		case 12: //짧은 글 연습
			WordRun(Text.ss, tempAcc, tempTa, 2);
			Man.SetAA(tempAcc);
			Man.SetAT(tempTa);
			break;

		case 14: //긴글 연습
			WordRun(Text.ls, tempAcc, tempTa, 3);
			Man.SetAA(tempAcc);
			Man.SetAT(tempTa);
			break;

		case 16: //산성비
			sanstart = MessageBox(NULL, "산성비 게임을 시작합니다.", "CONFIRM", MB_OKCANCEL | MB_ICONQUESTION);

			if (sanstart == IDOK) { //OK를 누르면
				SanRun();
			}
			break;

		case 18: //환경설정
		{
			MessageBox(NULL, "수정하고 싶은 곳으로 커서를 움직인 후\nenter를 누르면 입력칸이 생깁니다.\n다시 enter를 누르면 값이 저장됩니다.", "NOTICE", MB_OK);
			Option(Man);
			break;
		}

		case 20: //언어 재선택
			MenuLang(Text);
			break;

		case 22: //종료
		{
			exitconfirm = MessageBox(NULL, "타자연습을 종료합니다.\n지금까지 이용해주셔서 감사합니다.", "NOTICE", MB_OKCANCEL | MB_ICONQUESTION);
			if (exitconfirm == IDOK) {
				return;
			}
			else
				break;
		}
		}//switch 끝
	}
}

void Option(BasicInfo &Man)
{
	int choice = 0;
	int condition = 1;
	int data1 = 0; //정수형 cin

	while (condition == 1) {
		system("cls");
		gotoxy(0, 2);
		line();
		gotoxy(56, 4);
		cout << "환경설정";
		gotoxy(0, 6);
		line();

		gotoxy(50, 10);
		cout << "이름 : " << Man.GetNa();
		gotoxy(50, 12);
		cout << "목표 타수 : " << Man.GetGT();
		gotoxy(50, 14);
		cout << "목표 정확도 : " << Man.GetGA();
		gotoxy(50, 16);
		cout << "BGM : " << Man.GetVo();
		gotoxy(50, 18);
		cout << "나가기";

		gotoxy(0, 22);
		line();

		gotoxy(50, 25.5);
		cout << "평균 타수 : " << Man.GetAT();
		gotoxy(50, 27.5);
		cout << "평균 정확도 : " << Man.GetAA();

		choice = select(70, 10, 18);
		switch (choice)
		{
		case 10:
			gotoxy(86, 10);
			cout << "입력  >> ";
			Man.SetNa(95, 10);
			break;
		case 12:
			gotoxy(86, 12);
			cout << "입력  >> ";
			cin >> data1;
			Man.SetGT(data1, 95, 12);
			break;
		case 14:
			gotoxy(86, 14);
			cout << "입력  >> ";
			cin >> data1;
			Man.SetGA(data1, 95, 14);
			data1 = 0;
			break;
		case 16:
			if (Man.GetVo() == "OFF") {
				Man.SetVo(1);
			}
			else {
				Man.SetVo(0);
			}
			break;
		case 18:
			condition = 0;
			break;
		}//switch 끝
		system("cls");
	}//while 끝
}//함수 끝

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void move(int key, int *x, int *y, int y_min, int y_max)
{
	switch (key)
	{
	case 72:
		(*y) -= 2; //위쪽(상) 방향의화살표키입력
		if (*y < y_min)    *y = y_min; //y좌표의최솟값
		break;
	case 80:
		(*y) += 2;  //아래쪽(하) 방향의화살표키입력
		if (*y > y_max)    *y = y_max; //y좌표의최댓값
		break;
	default:
		return;
	}
}

int select(int x, int min, int max)
{
	int y = min, temp_y = y, key;
	do
	{
		gotoxy(x, temp_y);
		cout << (" ");
		gotoxy(x, y);
		cout << ("◀");
		temp_y = y;
		key = _getch();
		move(key, &x, &y, min, max);
	} while (key != 13); //Enter가 입력되면 종료된다
	return y;
}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetcursorVisible(bool tf)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;

	ConsoleCursor.bVisible = tf;

	ConsoleCursor.dwSize = 1; // 커서사이즈

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // 설정
}

void line(void)
{
	cout << "========================================================================================================================" << "\n" ;
}