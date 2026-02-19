/*
  ЛЕГЕНДА: Оглавление книги — не читаешь всё. Кликнул раздел — открылась страница.
  СУТЬ: Заместитель откладывает создание тяжёлого объекта до использования.
  КОГДА: ленивая загрузка, кэш, контроль доступа.
*/
#include <Windows.h>
#include <iostream>
using namespace std;

// Интерфейс — «открыть»
class Chapter {
public:
    virtual void open() = 0;
    virtual ~Chapter() = default;
};

// Реальная страница — тяжёлая (загрузка при создании)
class RealPage : public Chapter {
    string title;
public:
    RealPage(const string& t) : title(t) {
        cout << "Открываю " << t << endl;  // Дорого
    }
    void open() override { cout << "Читаю " << title << endl; }
};

// Оглавление — лёгкое, открывает страницу только при клике
class TocEntry : public Chapter {
    string title;
    RealPage* page = nullptr;
public:
    TocEntry(const string& t) : title(t) {
        cout << "Оглавление: " << t << endl;  // Легко
    }
    void open() override {
        if (!page)
            page = new RealPage(title);  // Открываем только при клике
        page->open();
    }
    ~TocEntry() { delete page; }
};

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    Chapter* ch = new TocEntry("Глава 1");
    ch->open();  // Здесь откроется страница
    delete ch;
}
