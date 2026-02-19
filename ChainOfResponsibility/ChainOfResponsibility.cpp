/*
  ЛЕГЕНДА: Очередь в банке — касса 1 не подходит, идёшь в кассу 2. Запрос по цепочке.
  СУТЬ: Запрос передаётся по цепочке, пока кто-то не обработает.
  КОГДА: поддержка, одобрение заявок по уровням.
*/
#include <Windows.h>
#include <iostream>
using namespace std;

// Базовый обработчик — знает про «следующего»
class Cashier {
protected:
    Cashier* next = nullptr;
public:
    void setNext(Cashier* c) { next = c; }
    virtual void serve(int amount) {
        if (next)
            next->serve(amount);  // Передаём дальше
        else
            cout << "Нет кассы\n";
    }
};

// Касса 1 — только мелкие суммы
class Cash1 : public Cashier {
public:
    void serve(int n) override {
        if (n <= 100)
            cout << "Касса 1 обслужила " << n << endl;
        else
            Cashier::serve(n);
    }
};

// Касса 2 — крупные
class Cash2 : public Cashier {
public:
    void serve(int n) override { cout << "Касса 2 обслужила " << n << endl; }
};

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    Cash1 c1;
    Cash2 c2;
    c1.setNext(&c2);
    c1.serve(50);
    c1.serve(500);
}