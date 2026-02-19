/*
  ЛЕГЕНДА: Заметка «купить молоко» — не купил, а записал действие. Выполнишь потом.
  СУТЬ: Действие как объект — можно хранить, отложить, отменить.
  КОГДА: Undo, очереди действий, макросы.
*/
#include <Windows.h>
#include <iostream>
using namespace std;

// Команда — действие, упакованное в объект
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

// Список покупок
class ShoppingList {
public:
    void add(const string& item) { cout << "Добавлено: " << item << endl; }
};

// Заметка «купить X» — команда
class BuyCommand : public Command {
    ShoppingList* list;
    string item;
public:
    BuyCommand(ShoppingList* l, const string& i) : list(l), item(i) {}
    void execute() override {
        list->add(item);  // Выполняем потом
    }
};

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    ShoppingList list;
    Command* cmd = new BuyCommand(&list, "молоко");
    cmd->execute();  // Можно сохранить и выполнить позже
    delete cmd;
}