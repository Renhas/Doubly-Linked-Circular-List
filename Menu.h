#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
/// <summary>
/// ���� � ���������� ������
/// </summary>
class Menu final {
private:
	const string title;
	vector<string> options;
public:
	Menu(const string& = "");

	//���������� �������� ������
	void Add(const string&);
	//���������� ���������
	const string& getTitle() const;
	//����� ���� �� �����
	void Show() const;
	/// <summary>
	/// ���������� ����������������� �����
	/// </summary>
	/// <returns>��������� �������. 0 � ������ ���������� ��������� � ����</returns>
	int Run() const;

	Menu& operator=(const Menu&);
};
/// <summary>
/// ��������� ��������� ������������� �������
/// </summary>
/// <returns>����� ������������� �����</returns>
int readUserOption();
bool YesOrNo();
//��������� ������������������ ����� � ���������� ������
void readUserInts(vector<int>&);