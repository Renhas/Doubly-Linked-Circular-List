#include <iostream>
#include <windows.h>
#include <string>
#include "MyList.h"
#include "Menu.h"
#include "CPoint.h"
using namespace std;

template <class T> void MenuForMyList(MyList<T>&, typename MyList<T>::Iterator&, string = "Список");
void MenuForMyList(/*MyList<string>&*/MyList<char*>&, typename /*MyList<string>::Iterator&*/MyList<char*>::Iterator&, string = "Список");

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    MyList<int> list_of_ints; 
    //MyList<string> list_of_strings;
    MyList<CPoint> list_of_points;
    MyList<char*> list_of_c_style;


    //Итераторы

    auto int_iter = list_of_ints.begin();
    //auto string_iter = list_of_strings.begin();
    auto point_iter = list_of_points.begin();
    auto c_style_iter = list_of_c_style.begin();

    //Меню
    Menu MainMenu("Главное меню");

    MainMenu.Add("Целые числа");
    MainMenu.Add("Строки");
    MainMenu.Add("Точки");
    MainMenu.Add("Выход из программы");


    int main_answer = 0;
    while (main_answer != 4) 
    {
        MainMenu.Show();
        switch (main_answer = MainMenu.Run()) {
        case 1: 
            MenuForMyList(list_of_ints, int_iter, "Список целых чисел");
            break;
        case 2:
            //MenuForMyList(list_of_strings, string_iter, "Список строк");
            MenuForMyList(list_of_c_style, c_style_iter, "Список строк");
            break;
        case 3:
            MenuForMyList(list_of_points, point_iter, "Список точек");
            break;
        case 4: exit(0);
        }
        system("cls");
    
    }
}

template<class T>
void MenuForMyList(MyList<T>& list, typename MyList<T>::Iterator& iter, string title)
{
    system("cls");
    Menu menu(title), IterMenu;

    menu.Add("Вернуться в главное меню");
    menu.Add("Вывести список");
    menu.Add("Добавить элемент");
    menu.Add("Удалить элемент по индексу");
    menu.Add("Очистить список");

    IterMenu.Add("Шаг вперёд");
    IterMenu.Add("Шаг назад");
    IterMenu.Add("Установить итератор");
    IterMenu.Add("Добавить элемент на место нынешнего (со смещением)");
    IterMenu.Add("Удалить нынешний элемент");
    IterMenu.Add("Сбросить итератор");
    IterMenu.Add("Выйти в меню");

    int menu_answer = 0, iter_answer = 0;
    menu.Show();
    while (menu_answer != 1)
    {
        bool result;
        int index;
        T element;
        switch (menu_answer = menu.Run())
        {
        case 1: break;
        case 2:
            if (list.empty()) { cout << "Список пуст" << endl; break; }

            cout << "Размер списка: " << list.size() << endl;
            cout << "Элементы списка: " << endl;
            for (int i = 0; i < list.size(); i++) cout << i + 1 << ": " << list[i] << endl;
            if (iter.IsNull()) {
                cout << "Итератор неопределён" << endl << "Сбросить итератор? Y/N ";
                if (YesOrNo()) iter = list.begin();
            }
            if (!iter.IsNull()) {
                cout << "Текущий элемент: " << *iter << endl << "Перейти в режим управления итератором? Y/N ";
                if (YesOrNo()) {
                    IterMenu.Show();
                    iter_answer = 0;
                    while (iter_answer != 7) {
                        int buf;

                        switch (iter_answer = IterMenu.Run()) {
                        case 1: ++iter; break;
                        case 2: --iter; break;
                        case 3:
                            buf = -1;
                            while (buf < 0 || buf >= list.size()) {
                                cout << "Введите индекс элемента: ";
                                buf = readUserOption();
                                if (buf < 0 || buf >= list.size()) cout << "Некорректный индекс" << endl;
                            }
                            iter = list.get(buf);
                            break;
                        case 4: 
                            result = false;
                            while (!result) {
                                cout << "Введите данные: ";
                                result = true;
                                cin >> element;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(32000, '\n');
                                    cout << "Некорректный ввод!" << endl;
                                    result = false;
                                }
                            }
                            iter = list.insert(element, iter);
                            break;
                        case 5: iter = list.erase(iter); break;
                        case 6: iter = list.begin(); break;
                        }
                        if (iter_answer != 7 && !iter.IsNull()) cout << "Текущий элемент: " << *iter << endl;
                        else if (iter.IsNull()) { cout << "Итератор неопределён" << endl; iter_answer = 7; }
                    }
                    menu.Show();
                }
            }
            
            break;
        case 3:
            index = -1;
            while (index < 0 || index > list.size()) {
                cout << "Введите индекс: ";
                index = readUserOption();
                if (index < 0 || index > list.size()) cout << "Некорректный индекс" << endl;
            }

            result = false;
            while (!result) {
                cout << "Введите данные: ";
                result = true;
                cin >> element;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(32000, '\n');
                    cout << "Некорректный ввод!" << endl;
                    result = false;
                }
            }

            if (index == 0) list.push_front(element);
            else if (index == list.size()) list.push_back(element);
            else list.insert(element, index);

            break;
        case 4:
            if (list.empty()) { cout << "Список пуст!" << endl; break; }

            index = -1;
            while (index < 0 || index >= list.size()) {
                cout << "Введите индекс: ";
                index = readUserOption();
                if (index < 0 || index >= list.size()) cout << "Некорректный индекс" << endl;
            }

            list.erase(index);
            break;
        case 5: 
            list.clear();
            iter = list.begin();
            break;
        }
    }
}


void MenuForMyList(/*MyList<string>&*/MyList<char*>& list, typename /*MyList<string>::Iterator&*/MyList<char*>::Iterator& iter, string title)
{
    system("cls");
    Menu menu(title), IterMenu;

    menu.Add("Вернуться в главное меню");
    menu.Add("Вывести список");
    menu.Add("Добавить элемент");
    menu.Add("Удалить элемент по индексу");
    menu.Add("Очистить список");

    IterMenu.Add("Шаг вперёд");
    IterMenu.Add("Шаг назад");
    IterMenu.Add("Установить итератор");
    IterMenu.Add("Добавить элемент на место нынешнего (со смещением)");
    IterMenu.Add("Удалить нынешний элемент");
    IterMenu.Add("Сбросить итератор");
    IterMenu.Add("Выйти в меню");

    int menu_answer = 0, iter_answer = 0;
    menu.Show();
    while (menu_answer != 1)
    {
        //bool result;
        int index;
        //string element;
        char* element = new char[255];
        switch (menu_answer = menu.Run())
        {
        case 1: break;
        case 2:
            if (list.empty()) { cout << "Список пуст" << endl; break; }

            cout << "Размер списка: " << list.size() << endl;
            cout << "Элементы списка: " << endl;
            for (int i = 0; i < list.size(); i++) cout << i + 1 << ": " << list[i] << endl;
            if (iter.IsNull()) {
                cout << "Итератор неопределён" << endl << "Сбросить итератор? Y/N ";
                if (YesOrNo()) iter = list.begin();
            }
            if (!iter.IsNull()) {
                cout << "Текущий элемент: " << *iter << endl << "Перейти в режим управления итератором? Y/N ";
                if (YesOrNo()) {
                    IterMenu.Show();
                    iter_answer = 0;
                    while (iter_answer != 7) {
                        int buf;

                        switch (iter_answer = IterMenu.Run()) {
                        case 1: ++iter; break;
                        case 2: --iter; break;
                        case 3:
                            buf = -1;
                            while (buf < 0 || buf >= list.size()) {
                                cout << "Введите индекс элемента: ";
                                buf = readUserOption();
                                if (buf < 0 || buf >= list.size()) cout << "Некорректный индекс" << endl;
                            }
                            iter = list.get(buf);
                            break;
                        case 4:
                            cout << "Введите данные: ";
                            //getline(cin, element, '\n');
                            cin.getline(element, 255);
                            iter = list.insert(element, iter);
                            break;
                        case 5: iter = list.erase(iter); break;
                        case 6: iter = list.begin(); break;
                        }
                        if (iter_answer != 7 && !iter.IsNull()) cout << "Текущий элемент: " << *iter << endl;
                        else if (iter.IsNull()) { cout << "Итератор неопределён" << endl; iter_answer = 7; }
                    }
                    menu.Show();
                }
            }

            break;
        case 3:
            index = -1;
            while (index < 0 || index > list.size()) {
                cout << "Введите индекс: ";
                index = readUserOption();
                if (index < 0 || index > list.size()) cout << "Некорректный индекс" << endl;
            }

            cout << "Введите данные: ";
            //getline(cin, element, '\n');
            cin.getline(element, 255);

            if (index == 0) list.push_front(element);
            else if (index == list.size()) list.push_back(element);
            else list.insert(element, index);

            break;
        case 4:
            if (list.empty()) { cout << "Список пуст!" << endl; break; }

            index = -1;
            while (index < 0 || index >= list.size()) {
                cout << "Введите индекс: ";
                index = readUserOption();
                if (index < 0 || index >= list.size()) cout << "Некорректный индекс" << endl;
            }

            list.erase(index);
            break;
        case 5:
            list.clear();
            iter = list.begin();
            break;
        }
        delete[] element;
    }
}