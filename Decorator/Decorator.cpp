/*
  ЛЕГЕНДА: Подарок — коробка, обёртка, бант. Каждый слой добавляет. Основа + обёртки.
  СУТЬ: Динамически добавляет обязанности через обёртки.
  КОГДА: много комбинаций без взрыва классов.
*/
#include <Windows.h>
#include <iostream>
using namespace std;

// Базовый интерфейс
class Gift {
public:
    virtual int price() = 0;
    virtual ~Gift() = default;
};

// Основа — коробка
class Box : public Gift {
    int price() override { return 50; }
};

// Обёртка — содержит подарок и добавляет свою цену
class Wrapper : public Gift {
protected:
    Gift* base;
public:
    Wrapper(Gift* b) : base(b) {}
};

// Бант — добавляет 20 к цене
class Bow : public Wrapper {
public:
    Bow(Gift* b) : Wrapper(b) {}
    int price() override { return base->price() + 20; }
};

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    // Коробка + бант (можно: new Bow(new Paper(new Box())))
    Gift* g = new Bow(new Box());
    cout << "Цена: " << g->price() << endl;
    delete g;
}