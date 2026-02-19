/*
  ЛЕГЕНДА: Витрина — экспонаты одни. Экскурсовод «рассказать» обходит. «Посчитать» — другой визитёр.
  СУТЬ: Новая операция над структурой без изменения элементов.
  КОГДА: много типов элементов, много операций (подсчёт, экспорт).
*/

#include <iostream>
#include <vector>
using namespace std;

class Exhibit;
class Showcase;

// Визитёр — операция (экскурсовод с разной задачей)
class GuideVisitor {
public:
    virtual void visit(Exhibit* e) = 0;
    virtual void visit(Showcase* s) = 0;
    virtual ~GuideVisitor() = default;
};

// Элемент витрины
class ExhibitItem {
public:
    virtual void accept(GuideVisitor* v) = 0;
    virtual ~ExhibitItem() = default;
};

// Один экспонат
class Exhibit : public ExhibitItem {
    string name;
    int year;
public:
    Exhibit(const string& n, int y) : name(n), year(y) {}
    void accept(GuideVisitor* v) override { v->visit(this); }
    string getName() { return name; }
    int getYear() { return year; }
};

// Витрина (несколько экспонатов)
class Showcase : public ExhibitItem {
    string name;
    vector<ExhibitItem*> items;
public:
    Showcase(const string& n) : name(n) {}
    void add(ExhibitItem* i) { items.push_back(i); }
    void accept(GuideVisitor* v) override {
        v->visit(this);
        for (auto i : items) i->accept(v);
    }
};

// Визитёр — рассказать про экспонаты
class TellVisitor : public GuideVisitor {
public:
    void visit(Exhibit* e) override { cout << "Экспонат: " << e->getName() << endl; }
    void visit(Showcase* s) override {}
};

int main() {
    Showcase shop("Витрина");
    shop.add(new Exhibit("Ваза", 1800));
    shop.add(new Exhibit("Часы", 1900));

    TellVisitor guide;
    shop.accept(&guide);
}
