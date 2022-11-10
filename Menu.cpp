#include "Menu.h"

Menu::Menu(const string& s) : title(s)
{
}

void Menu::Add(const string& s)
{
	options.push_back(s);
}

const string& Menu::getTitle() const
{
	return title;
}

void Menu::Show() const
{
	if (options.empty()) { 
		cout << "Меню пусто";
		return;
	}
	if(title != "")	cout << endl << title << endl;
	for (int i = 0; i < options.size(); i++) {
		cout << i + 1 << ". " << options.at(i) << endl;
	}
}

int Menu::Run() const
{
	if (options.empty()) return 0;

	int answer = 0;
	while (answer < 1 || answer > options.size()) {
		cout << "Выберите вариант: ";
		answer = readUserOption();
		if (answer < 1 || answer > options.size()) cout << "Такого пункта нет!" << endl;
	}
	return answer;
}

Menu& Menu::operator=(const Menu& menu2)
{
	options = menu2.options;
	return *this;
}

int readUserOption()
{
	int answer;
	bool result = false;
	while (!result) {
		result = true;
		cin >> answer;
		if (cin.fail()) {
			cin.clear();
			cout << "Некорректный ввод!" << endl;
			result = false;
		}
		cin.ignore(32000, '\n');
	}
	return answer;
}

bool YesOrNo()
{
	char buf = '\0';
	while (toupper(buf) != 'Y' && toupper(buf) != 'N') {
		//if (cin.peek() != ' ') cin.ignore(32000, '\n');
		cin >> buf;
	}
	return toupper(buf) == 'Y';
}

void readUserInts(vector<int>& vec) 
{
	vec.clear();
	cin.clear();
	if(cin.peek() =='\n') cin.ignore(32000, '\n');
	string buf, intbuf;
	getline(cin, buf, '\n');
	for (char element : buf)
	{
		if (element >= '0' && element <= '9') {
			if (element == '0' && intbuf.size() == 0) continue;
			intbuf.push_back(element);
		}
		else if (intbuf.size() > 0) {
			vec.push_back(stoi(intbuf));
			intbuf.clear();
		}
	}
	if (intbuf.size() > 0) vec.push_back(stoi(intbuf));
}
