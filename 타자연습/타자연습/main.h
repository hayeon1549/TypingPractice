#include "same.h"

//전역
static string nameList[3]; //다른 사용자 이름

//클래스
class BasicInfo { //사용자 정보
private:
	string name; //사용자 이름
	int GoalTasok = 0; //목표 타속
	int GoalAccu = 0; //목표 정확도
	int AverTasok = 0; //평균 타속
	int AverAccu = 0; //평균 정확도
	int volume = 0; //소리 ON/OFF

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
					MessageBox(NULL, "사용자의 이름은 Man을 사용할 수 없습니다.", "NOTICE", MB_OK);
				else if (a.length() > 10)
					MessageBox(NULL, "사용자의 이름의 길이는 최대 10입니다.", "NOTICE", MB_OK);
				else
					MessageBox(NULL, "다른 사용자와 같은 이름은 사용할 수 없습니다.", "NOTICE", MB_OK);

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

				MessageBox(NULL, "숫자만 입력해주세요.", "NOTICE", MB_OK);

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

//함수
void Start(void); //출력
BasicInfo ManInfo(int &use); //사용자 정보 설정
void FileInC(int &count); //사용자 정보 파일에서 몇명을 저장해야되는지 불러옴
void FileInU(BasicInfo &Man, string a); //사용자 정보 파일에서 사용자 정보를 불러옴
void FileOutC(int count); //count 파일에 저장
void FileOutU(BasicInfo Man, string a); // 사용자 정보 파일에 저장
void MenuLang(FileInfo &Text); //언어 선택
void ReadFile(FileInfo &Text, string data, int len); //file 읽기
void MenuWay(BasicInfo &Man, FileInfo Text); //메뉴 선택
void Option(BasicInfo &Man); //환경설정