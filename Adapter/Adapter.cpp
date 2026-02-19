/*
  ЛЕГЕНДА: Переводчик — ты говоришь по-русски, он передаёт по-английски. «Переводит» один интерфейс в другой.
  СУТЬ: Адаптирует старый интерфейс под новый.
  КОГДА: нужный класс есть, но интерфейс не подходит.
*/
#include <Windows.h>
#include <iostream>
using namespace std;

// --- Что ожидает клиент (по-русски) ---
class RussianSpeaker {
public:
    virtual void sayRussian(const string& s) = 0;
    virtual ~RussianSpeaker() = default;
};

// --- Старый класс — умеет только по-английски ---
class EnglishOnly {
public:
    void sayEnglish(const string& s) { cout << "English: " << s << endl; }
};

// --- Адаптер: переводит русское в английское ---
class Translator : public RussianSpeaker {
    EnglishOnly eng;
public:
    void sayRussian(const string& s) override {
        eng.sayEnglish(s);  // «Переводим» вызов
    }
};

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    RussianSpeaker* r = new Translator();
    r->sayRussian("Привет");   // Клиент говорит по-русски
    delete r;
}
