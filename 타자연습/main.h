#include "same.h"

//����
static string nameList[3]; //�ٸ� ����� �̸�

//Ŭ����
class BasicInfo { //����� ����
private:
	string name; //����� �̸�
	int GoalTasok = 0; //��ǥ Ÿ��
	int GoalAccu = 0; //��ǥ ��Ȯ��
	int AverTasok = 0; //��� Ÿ��
	int AverAccu = 0; //��� ��Ȯ��
	int volume = 0; //�Ҹ� ON/OFF

public:

	BasicInfo(string  a = "MAN", int b = 300, int c = 95) : name(a), GoalTasok(b), GoalAccu(c) { }
	~BasicInfo() {}

	string GetNa() const { return name; }
	int GetGT() const { return GoalTasok; }
	int GetGA() const { return GoalAccu; }
	int GetAT() const { return AverTasok; }
	int GetAA() const { return AverAccu; }
	string GetVo() const {
		if (volume == 0) {
			return "OFF";
		}
		else {
			return "ON";
		}
	}

	void SetNa(int x, int y)
	{
		int comp = 0;
		string a;

		while (true) {
			cin >> a;
			comp = 0;

			for (int i = 0; i < 3; i++) {
				if (nameList[i] == a)
					comp = 1;
			}

			if (a == "Man" || a.length() > 10 || comp == 1) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');

				if (a == "Man")
					MessageBox(NULL, "������� �̸��� Man�� ����� �� �����ϴ�.", "NOTICE", MB_OK);
				else if (a.length() > 10)
					MessageBox(NULL, "������� �̸��� ���̴� �ִ� 10�Դϴ�.", "NOTICE", MB_OK);
				else
					MessageBox(NULL, "�ٸ� ����ڿ� ���� �̸��� ����� �� �����ϴ�.", "NOTICE", MB_OK);

				gotoxy(x, y);
				printf("                                                              ");
				gotoxy(x, y);
			}
			else
				break;
		}

		name = a;
	}
	void SetNa2(string a) {
		name = a;
	}
	void SetGT(int a, int x, int y) {
		a = IntOnly(a, x, y);

		if (a >= 1000)
			a = 1000;
		GoalTasok = a;
	}
	void SetGT2(int a) {
		GoalTasok = a;
	}
	void SetGA(int a, int x, int y) {
		a = IntOnly(a, x, y);

		if (a >= 100)
			a = 100;
		GoalAccu = a;
	}
	void SetGA2(int a) {
		GoalAccu = a;
	}
	void SetAT(int a) { AverTasok = a; }
	void SetAA(int a) { AverAccu = a; }
	void SetVo(int a) {
		if (a == 0) {
			PlaySound(NULL, 0, 0);
			volume = 0;
		}
		else {
			PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			volume = 1;
		}
	}

	int  IntOnly(int data, int x, int y)
	{
		if (cin.fail()) {
			while (!(cin >> data)) {

				cin.clear();
				cin.ignore(INT_MAX, '\n');

				MessageBox(NULL, "���ڸ� �Է����ּ���.", "NOTICE", MB_OK);

				gotoxy(x, y);
				printf("                                             ");
				gotoxy(x, y);
			}
		}

		return data;
	}

	void Reset() {
		name = "";
		GoalTasok = 0;
		GoalAccu = 0;
		AverTasok = 0;
		AverAccu = 0;
		volume = 0;
	}
};

//�Լ�
void Start(void); //���
BasicInfo ManInfo(int &use); //����� ���� ����
void FileInC(int &count); //����� ���� ���Ͽ��� ����� �����ؾߵǴ��� �ҷ���
void FileInU(BasicInfo &Man, string a); //����� ���� ���Ͽ��� ����� ������ �ҷ���
void FileOutC(int count); //count ���Ͽ� ����
void FileOutU(BasicInfo Man, string a); // ����� ���� ���Ͽ� ����
void MenuLang(FileInfo &Text); //��� ����
void ReadFile(FileInfo &Text, string data, int len); //file �б�
void MenuWay(BasicInfo &Man, FileInfo Text); //�޴� ����
void Option(BasicInfo &Man); //ȯ�漳��