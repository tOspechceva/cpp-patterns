/*
  ЛЕГЕНДА: Рецепт — схема одна: подготовить → готовить → подать. Суп и омлет — детали разные.
  СУТЬ: Базовый класс задаёт скелет, подклассы — конкретные шаги.
  КОГДА: общий процесс с вариациями.
*/

#include <iostream>
using namespace std;

// Базовый класс — скелет рецепта
class Recipe {
public:
    void cook() {
        prepare();   // Шаг 1 — каждый свой
        cookStep();  // Шаг 2 — каждый свой
        serve();     // Шаг 3 — общий
    }
    virtual ~Recipe() = default;
protected:
    virtual void prepare() = 0;
    virtual void cookStep() = 0;
    void serve() { cout << "Подать\n"; }
};

// Суп
class Soup : public Recipe {
    void prepare() override { cout << "Режем овощи\n"; }
    void cookStep() override { cout << "Варим\n"; }
};

// Омлет
class Omelet : public Recipe {
    void prepare() override { cout << "Взбиваем яйца\n"; }
    void cookStep() override { cout << "Жарим\n"; }
};

int main() {
    Soup s;
    s.cook();
    Omelet o;
    o.cook();
}
