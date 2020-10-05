#include "main.h"

int main() 
{
	int use = 0; //현재 사용하는 클래스
	FileInfo Text; //파일을 저장할 클래스 생성

	Start(); //시작화면 출력
	BasicInfo Man = ManInfo(use); //사용자 정보
	MenuLang(Text); //타자연습 언어 선택
	MenuWay(Man, Text); //타자연습 방법 선택

	if (use == 1)
		FileOutU(Man, "User1.txt");
	else if (use == 2)
		FileOutU(Man, "User2.txt");
	else if (use == 3)
		FileOutU(Man, "User3.txt");

	return 0;
}