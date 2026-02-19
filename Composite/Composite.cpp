/*
  ЛЕГЕНДА: Список покупок — «молоко» или «молочное: молоко, сыр». Пункт и группа — считаем одинаково.
  СУТЬ: Листья и группы имеют один интерфейс (древовидная структура).
  КОГДА: меню, список, дерево элементов.
*/
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

// Общий интерфейс — пункт или группа
class ListItem {
public:
    virtual void show() = 0;
    virtual ~ListItem() = default;
};

// Лист — один товар
class Item : public ListItem {
    string name;
public:
    Item(const string& n) : name(n) {}
    void show() override { cout << "  " << name << endl; }
};

// Группа — «молочное» содержит молоко и сыр
class Group : public ListItem {
    string name;
    vector<ListItem*> items;
public:
    Group(const string& n) : name(n) {}
    void add(ListItem* i) { items.push_back(i); }
    void show() override {
        cout << "[" << name << "]" << endl;
        for (auto i : items)
            i->show();  // Рекурсия — показываем детей
    }
};

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    Group milk("Молочное");
    milk.add(new Item("молоко"));
    milk.add(new Item("сыр"));
    cout << "Список:" << endl;
    milk.show();
}