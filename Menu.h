#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
/// <summary>
/// Меню с вариантами выбора
/// </summary>
class Menu final {
private:
	const string title;
	vector<string> options;
public:
	Menu(const string& = "");

	//Добавление варианта выбора
	void Add(const string&);
	//Считывание заголовка
	const string& getTitle() const;
	//Вывод меню на экран
	void Show() const;
	/// <summary>
	/// Считывание пользовательского ввода
	/// </summary>
	/// <returns>Выбранный вариант. 0 в случае отсутствия вариантов в меню</returns>
	int Run() const;

	Menu& operator=(const Menu&);
};
/// <summary>
/// Считывает выбранный пользователем вариант
/// </summary>
/// <returns>Целое положительное число</returns>
int readUserOption();
bool YesOrNo();
//Считывает последовательность чисел в переданный вектор
void readUserInts(vector<int>&);