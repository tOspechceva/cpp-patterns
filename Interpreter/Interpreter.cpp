/*
  ЛЕГЕНДА: Формула «7 - 2» — дерево: минус(7, 2). Каждый узел вычисляет себя.
  СУТЬ: Выражение как дерево объектов, каждый вычисляет себя.
  КОГДА: простые языки, формулы, конфиги.
*/

#include <iostream>
using namespace std;

// Базовый класс выражения
class Expr {
public:
    virtual int eval() = 0;
    virtual ~Expr() = default;
};

// Число — просто возвращает значение
class Num : public Expr {
    int val;
public:
    Num(int v) : val(v) {}
    int eval() override { return val; }
};

// Минус — два подвыражения
class Minus : public Expr {
    Expr* left, *right;
public:
    Minus(Expr* l, Expr* r) : left(l), right(r) {}
    int eval() override {
        return left->eval() - right->eval();  // Рекурсия
    }
};

int main() {
    // Дерево: Minus(Num(7), Num(2))
    Expr* e = new Minus(new Num(7), new Num(2));
    cout << e->eval() << endl;  // 5
}