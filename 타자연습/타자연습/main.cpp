#include "main.h"

int main() 
{
	int use = 0; //���� ����ϴ� Ŭ����
	FileInfo Text; //������ ������ Ŭ���� ����

	Start(); //����ȭ�� ���
	BasicInfo Man = ManInfo(use); //����� ����
	MenuLang(Text); //Ÿ�ڿ��� ��� ����
	MenuWay(Man, Text); //Ÿ�ڿ��� ��� ����

	if (use == 1)
		FileOutU(Man, "User1.txt");
	else if (use == 2)
		FileOutU(Man, "User2.txt");
	else if (use == 3)
		FileOutU(Man, "User3.txt");

	return 0;
}