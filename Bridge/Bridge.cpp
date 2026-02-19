/*
  ЛЕГЕНДА: Одна картинка — на экране или на бумаге.
  Носитель разный, картинка та же.
  СУТЬ: Абстракция и реализация раздельно — меняются независимо.
  КОГДА: много комбинаций (N картинок × M способов вывода).
*/

#include <Windows.h>
#include <iostream>

using namespace std;

// --- Реализация (куда выводим) ---
class Output
{
public:
    virtual void show(const string &pic) = 0;
    virtual ~Output() = default;
};
class ScreenOutput : public Output
{
    void show(const string &s) override { cout << "Экран: " << s << endl; }
};
class PaperOutput : public Output
{
    void show(const string &s) override { cout << "Бумага: " << s << endl; }
};

// --- Абстракция — картинка + способ вывода ---
class Picture
{
    Output *out;

public:
    Picture(Output *o) : out(o) {}
    void draw(const string &name)
    {
        out->show(name); // Делегируем — экран или бумага
    }
};

int main(){
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    ScreenOutput scr;
    PaperOutput pap;
    Picture p1(&scr), p2(&pap);
    p1.draw("пейзаж");
    p2.draw("пейзаж");
}