#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <vector>
#include <Windows.h>

// Класс Правительства (Одиночка)
class Government {
private:
    // Статический указатель на единственный экземпляр
    static Government* instance;
    
    // Мьютекс для потокобезопасности
    static std::mutex mutex;
    
    // Приватный конструктор (нельзя создать через new)
    Government() {
        std::cout << "🏛️  Правительство создано!" << std::endl;
        budget = 1000000;
        countryName = "Россия";
    }
    
    // Приватный конструктор копирования (запрещаем копирование)
    Government(const Government&) = delete;
    
    // Приватный оператор присваивания (запрещаем присваивание)
    Government& operator=(const Government&) = delete;
    
    // Состояние правительства
    int budget;
    std::string countryName;
    std::string president;
    
public:
    // Публичный статический метод для получения экземпляра
    static Government* getInstance() {
        // Двойная проверка блокировки (Double-Checked Locking)
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new Government();
            }
        }
        return instance;
    }
    
    // Методы для работы с правительством
    void setPresident(const std::string& name) {
        president = name;
        std::cout << "👤 Президент назначен: " << president << std::endl;
    }
    
    std::string getPresident() const {
        return president;
    }
    
    void setBudget(int amount) {
        budget = amount;
        std::cout << "💰 Бюджет установлен: " << budget << " руб." << std::endl;
    }
    
    int getBudget() const {
        return budget;
    }
    
    void printInfo() const {
        std::cout << "\n=== ИНФОРМАЦИЯ О ПРАВИТЕЛЬСТВЕ ===" << std::endl;
        std::cout << "Страна: " << countryName << std::endl;
        std::cout << "Президент: " << (president.empty() ? "не назначен" : president) << std::endl;
        std::cout << "Бюджет: " << budget << " руб." << std::endl;
        std::cout << "Адрес правительства: " << this << std::endl;
        std::cout << "====================================\n" << std::endl;
    }
    
    // Метод для уничтожения экземпляра (для тестов)
    static void destroyInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
            std::cout << "🏛️  Правительство распущено!" << std::endl;
        }
    }
    
    // Деструктор
    ~Government() {
        std::cout << "🏛️  Правительство уничтожено!" << std::endl;
    }
};

// Инициализация статических членов
Government* Government::instance = nullptr;
std::mutex Government::mutex;


// ==================== КЛИЕНТСКИЙ КОД ====================

// Функция, которая получает доступ к правительству
void accessGovernment() {
    Government* gov = Government::getInstance();
    gov->printInfo();
}

// Функция для демонстрации многопоточности
void threadFunction(int threadId) {
    std::cout << "[Поток " << threadId << "] Запрос правительства..." << std::endl;
    Government* gov = Government::getInstance();
    std::cout << "[Поток " << threadId << "] Адрес правительства: " << gov << std::endl;
}

// ==================== MAIN ====================

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif

    // === ПРИМЕР 1: Базовое использование ===
    std::cout << "--- Пример 1: Создание правительства ---\n" << std::endl;
    
    Government* gov1 = Government::getInstance();
    gov1->setPresident("Иван Иванов");
    gov1->setBudget(1000000);
    
    std::cout << "\n--- Получаем правительство во второй раз ---" << std::endl;
    Government* gov2 = Government::getInstance();
    
    std::cout << "\nПроверяем, что это один и тот же объект:" << std::endl;
    std::cout << "Адрес gov1: " << gov1 << std::endl;
    std::cout << "Адрес gov2: " << gov2 << std::endl;
    std::cout << "Одинаковые? " << (gov1 == gov2 ? "✅ ДА" : "❌ НЕТ") << std::endl;
    
    gov2->printInfo();
    
    // === ПРИМЕР 2: Изменение через одну ссылку влияет на все ===
    std::cout << "--- Пример 2: Изменение состояния ---\n" << std::endl;
    
    gov1->setBudget(5000000);
    std::cout << "\nИзменили бюджет через gov1, проверяем через gov2:" << std::endl;
    std::cout << "Бюджет в gov2: " << gov2->getBudget() << " руб." << std::endl;
    
    // Очистка
    Government::destroyInstance();
    
    return 0;
}