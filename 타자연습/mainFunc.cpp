#include "main.h"

void Start(void)
{
	PlaySound(NULL, 0, 0);

	MessageBox(NULL, "Choose what you want to practice.\n\nIf you want exit while you're praticing, type exit.\n\nProgrammed by ������, ȫ�Ͽ�.\n\n(C)Copyright 2019 Project 'GSM'", "Ÿ�ڿ��� ����", MB_OK | MB_ICONINFORMATION);
	//[�Ӽ�]-[���� �Ӽ�]-[�Ϲ�]-������Ʈ �⺻��-[���� ����]-��Ƽ����Ʈ ���� ���� ��� ����

	//system("mode con:cols=120 lines=30"); //�ܼ� â ũ�� ����
	system("title ���α׷��ְ� �Բ� �ϴ� Ÿ�ڿ���");
	system("color f0"); //�ܼ� â ���� ����
	SetCursorVisible(0);

	for (int i = 0; i < 5; i++) {
		textcolor(i + 9, 15);
		gotoxy(30, 7);
		cout << "��������������������������������";
		gotoxy(30, 8);
		cout << "��������������������������������";
		gotoxy(30, 9);
		cout << "��������������������������������";
		gotoxy(30, 10);
		cout << "��������������������������������";
		gotoxy(30, 11);
		cout << "��������������������������������";
		gotoxy(30, 12);
		cout << "��������������������������������";
		gotoxy(30, 13);
		cout << "��������������������������������";
		gotoxy(30, 14);
		cout << "��������������������������������";
		gotoxy(30, 15);
		cout << "��������������������������������";
		gotoxy(30, 16);
		cout << "��������������������������������";
		gotoxy(30, 17);
		cout << "��������������������������������";
		gotoxy(30, 18);
		cout << "��������������������������������";
		Sleep(300);
		system("cls");
	}

	textcolor(0, 15);
}

BasicInfo ManInfo(int &use) {
	BasicInfo Man[4];

	int condition1 = 1; //while�� �ݺ� ����, messagebox
	int condition2 = 1; //while�� �ݺ� ����(ȯ�漳��), messagebox
	int count = 0; //����� �� ī��Ʈ
	int choice1 = 0; //����� ���� switch
	int choice2 = 0; //����� ����, ���� ifelse
	int i = 0; //for��
	int data = 0; //��ǥ Ÿ��, ��Ȯ���� �Է¹��� ����
	int choice3 = 0; //����� ���� Ȯ�� â ������/�����ϱ�

	//����� ���� �ʱ�ȭ
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
		cout << "����� ����" << endl;
		gotoxy(0, 6);
		line();

		gotoxy(45, 10);
		cout << "(1) ����� �����ϱ�";
		gotoxy(45, 12);
		cout << "(2) ����� �����ϱ�";
		gotoxy(45, 14);
		cout << "(3) ����� �����ϱ�";
		choice1 = select(73, 10, 14);
		system("cls");

		//nameList �ʱ�ȭ(name�� ��ġ�� �ʵ��� �ϱ� ����)
		for (int i = 0; i <= count; i++)
			nameList[i] = Man[i].GetNa();
		for (int i = count + 1; i < 3; i++)
			nameList[i] = "";

		switch (choice1)
		{
		case 10: //����� �����ϱ�
		{
			gotoxy(52, 7);
			cout << "<����� �����ϱ�>";
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
				condition1 = MessageBox(NULL, "�⺻ ����ڸ� ������ ���\n����� ������ ������� �ʽ��ϴ�.", "CONFIRM", MB_OKCANCEL | MB_ICONQUESTION);
			else
				condition1 = MessageBox(NULL, "Ÿ�ڿ����� �����մϴ�.", "CONFIRM", MB_OKCANCEL | MB_ICONQUESTION);

			if (condition1 == IDOK) { //OK�� ������
				condition1 = 0; //while�� ����
			}
			else {
				condition1 = 1;
			}
			break;
		}

		case 12: //����� �����ϱ�
		{
			MessageBox(NULL, "����� �̸��� �ߺ��� �� ������\n\"Man\", \"MAN\" ��뵵 �Ұ��մϴ�.\n����� �̸��� �ִ� 10�ڸ����� �����մϴ�.", "NOTICE", MB_OK);

			if (count == 3) {
				MessageBox(NULL, "����ڴ� �ִ� 3����� ������ �� �ֽ��ϴ�.", "NOTICE", MB_OK);
				break;
			}

			count++;

			gotoxy(52, 7);
			cout << "<����� �����ϱ�>";
			gotoxy(49, 10);
			cout << "����� �̸� >> ";
			Man[count].SetNa(64, 10);

			gotoxy(49, 12);
			cout << "��ǥ Ÿ��   >> ";
			cin >> data;
			Man[count].SetGT(data, 64, 12);

			gotoxy(49, 14);
			cout << "��ǥ ��Ȯ�� >> ";
			cin >> data;
			Man[count].SetGA(data, 64, 14);

			gotoxy(41, 18);
			cout << "���������� ����� ������ �����Ǿ����ϴ�!";
			Sleep(1000);

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			break;
		}

		case 14: //����� �����ϱ�
		{
			if (count == 0) {
				MessageBox(NULL, "������ ����ڰ� �����ϴ�.", "NOTICE", MB_OK);
				break;
			}

			gotoxy(52, 7);
			cout << "<����� �����ϱ�>";
			for (i = 1; i <= count; i++) { //�⺻���� �����Ǿ� �ִ� Man�� ������ ����
				if (Man[i].GetNa() != "Man") { //���� ������ �����ߴٸ� �̸��� Man���� �ٲ�Ƿ�
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
			cout << "���������� ����� ������ �����Ǿ����ϴ�!";
			Sleep(1000);
			break;
		} //case ��
		} //switch ��
	} //while ��

	//����� ���� ���Ͽ� ����
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
		MessageBox(NULL, "������ �ҷ����µ� �����߽��ϴ�.", "NOTICE", MB_OK);
	}

	in.close();
}

void FileOutC(int count)
{
	ofstream out("Count.txt", ios::trunc);
	if(out.is_open())
		out << count << endl;
	else
		MessageBox(NULL, "������ �ҷ����µ� �����߽��ϴ�.", "NOTICE", MB_OK);

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
	cout << "��� ����";
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

	condition = MessageBox(NULL, "�� �����մϴ�.", "CONFIRM", MB_OKCANCEL | MB_ICONQUESTION);

	if (condition == IDCANCEL) { //��Ҹ� ������
		MenuLang(Text);
	}
}

void ReadFile(FileInfo &Text, string data, int len)
{
	ifstream ifs; // ifs��� ifstream ��ü�� ������.
	string str;

	ifs.open(data); // ifs�� data�� ������.

	for (int i = 0; !ifs.eof(); i++){
		if (!ifs.is_open()) {
			MessageBox(NULL, "������ �ҷ����µ� �����߽��ϴ�.", "NOTICE", MB_OK);
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
	ifs.close(); // ���ϰ��� ������ ����.
}


void MenuWay(BasicInfo &Man, FileInfo Text)
{
	int input;
	int sanstart = 0;
	int whileout = 0;
	int exitconfirm = 0;
	int tempAcc = 0; //��Ȯ���� �ӽ÷� ����
	int tempTa = 0; //Ÿ���� �ӽ÷� ����

	while (whileout == 0) {
		system("cls");
		gotoxy(0, 2);
		line();
		gotoxy(43, 4);
		cout << "���α׷��ְ� �Բ��ϴ� Ÿ�ڿ���";
		gotoxy(0, 6);
		line();

		gotoxy(50, 10);
		cout << "(1) ���� ����";
		gotoxy(50, 12);
		cout << "(2) ª�� �� ����";
		gotoxy(50, 14);
		cout << "(3) �� �� ����";
		gotoxy(50, 16);
		cout << "(4) �꼺��";
		gotoxy(50, 18);
		cout << "(5) ȯ�漳��";
		gotoxy(50, 20);
		cout << "(6) ��� �缱��";
		gotoxy(50, 22);
		cout << "(7) ����";
		input = select(70, 10, 22);

		system("cls");

		switch (input)
		{
		case 10: //���� ����
			WordRun(Text.wo, tempAcc, tempTa, 1);
			Man.SetAA(tempAcc);
			Man.SetAT(tempTa);
			break;

		case 12: //ª�� �� ����
			WordRun(Text.ss, tempAcc, tempTa, 2);
			Man.SetAA(tempAcc);
			Man.SetAT(tempTa);
			break;

		case 14: //��� ����
			WordRun(Text.ls, tempAcc, tempTa, 3);
			Man.SetAA(tempAcc);
			Man.SetAT(tempTa);
			break;

		case 16: //�꼺��
			sanstart = MessageBox(NULL, "�꼺�� ������ �����մϴ�.", "CONFIRM", MB_OKCANCEL | MB_ICONQUESTION);

			if (sanstart == IDOK) { //OK�� ������
				SanRun();
			}
			break;

		case 18: //ȯ�漳��
		{
			MessageBox(NULL, "�����ϰ� ���� ������ Ŀ���� ������ ��\nenter�� ������ �Է�ĭ�� ����ϴ�.\n�ٽ� enter�� ������ ���� ����˴ϴ�.", "NOTICE", MB_OK);
			Option(Man);
			break;
		}

		case 20: //��� �缱��
			MenuLang(Text);
			break;

		case 22: //����
		{
			exitconfirm = MessageBox(NULL, "Ÿ�ڿ����� �����մϴ�.\n���ݱ��� �̿����ּż� �����մϴ�.", "NOTICE", MB_OKCANCEL | MB_ICONQUESTION);
			if (exitconfirm == IDOK) {
				return;
			}
			else
				break;
		}
		}//switch ��
	}
}

void Option(BasicInfo &Man)
{
	int choice = 0;
	int condition = 1;
	int data1 = 0; //������ cin

	while (condition == 1) {
		system("cls");
		gotoxy(0, 2);
		line();
		gotoxy(56, 4);
		cout << "ȯ�漳��";
		gotoxy(0, 6);
		line();

		gotoxy(50, 10);
		cout << "�̸� : " << Man.GetNa();
		gotoxy(50, 12);
		cout << "��ǥ Ÿ�� : " << Man.GetGT();
		gotoxy(50, 14);
		cout << "��ǥ ��Ȯ�� : " << Man.GetGA();
		gotoxy(50, 16);
		cout << "BGM : " << Man.GetVo();
		gotoxy(50, 18);
		cout << "������";

		gotoxy(0, 22);
		line();

		gotoxy(50, 25.5);
		cout << "��� Ÿ�� : " << Man.GetAT();
		gotoxy(50, 27.5);
		cout << "��� ��Ȯ�� : " << Man.GetAA();

		choice = select(70, 10, 18);
		switch (choice)
		{
		case 10:
			gotoxy(86, 10);
			cout << "�Է�  >> ";
			Man.SetNa(95, 10);
			break;
		case 12:
			gotoxy(86, 12);
			cout << "�Է�  >> ";
			cin >> data1;
			Man.SetGT(data1, 95, 12);
			break;
		case 14:
			gotoxy(86, 14);
			cout << "�Է�  >> ";
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
		}//switch ��
		system("cls");
	}//while ��
}//�Լ� ��

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
		(*y) -= 2; //����(��) ������ȭ��ǥŰ�Է�
		if (*y < y_min)    *y = y_min; //y��ǥ���ּڰ�
		break;
	case 80:
		(*y) += 2;  //�Ʒ���(��) ������ȭ��ǥŰ�Է�
		if (*y > y_max)    *y = y_max; //y��ǥ���ִ�
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
		cout << ("��");
		temp_y = y;
		key = _getch();
		move(key, &x, &y, min, max);
	} while (key != 13); //Enter�� �ԷµǸ� ����ȴ�
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

	ConsoleCursor.dwSize = 1; // Ŀ��������

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // ����
}

void line(void)
{
	cout << "========================================================================================================================" << "\n" ;
}