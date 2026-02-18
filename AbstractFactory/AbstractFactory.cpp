#include <iostream>
#include <string>
#include <memory>
#include <Windows.h>

// ==================== ИНТЕРФЕЙСЫ ПРОДУКТОВ ====================

// Интерфейс Кресла
class Chair {
public:
    virtual void sitOn() = 0;
    virtual ~Chair() = default;
};

// Интерфейс Дивана
class Sofa {
public:
    virtual void lieOn() = 0;
    virtual void sitOn() = 0;
    virtual ~Sofa() = default;
};

// Интерфейс Столика
class Table {
public:
    virtual void putItem() = 0;
    virtual ~Table() = default;
};

// ==================== КОНКРЕТНЫЕ ПРОДУКТЫ (МОДЕРН) ====================

class ModernChair : public Chair {
public:
    void sitOn() override {
        std::cout << "Сидим на современном кресле" << std::endl;
    }
};

class ModernSofa : public Sofa {
public:
    void lieOn() override {
        std::cout << "Лежим на современном диване" << std::endl;
    }
    
    void sitOn() override {
        std::cout << "Сидим на современном диване" << std::endl;
    }
};

class ModernTable : public Table {
public:
    void putItem() override {
        std::cout << "Ставим предметы на современный столик" << std::endl;
    }
};

// ==================== КОНКРЕТНЫЕ ПРОДУКТЫ (ВИКТОРИАНСКИЙ) ====================

class VictorianChair : public Chair {
public:
    void sitOn() override {
        std::cout << "Сидим на викторианском кресле" << std::endl;
    }
};

class VictorianSofa : public Sofa {
public:
    void lieOn() override {
        std::cout << "Лежим на викторианском диване" << std::endl;
    }
    
    void sitOn() override {
        std::cout << "Сидим на викторианском диване" << std::endl;
    }
};

class VictorianTable : public Table {
public:
    void putItem() override {
        std::cout << "Ставим предметы на викторианский столик" << std::endl;
    }
};

// ==================== АБСТРАКТНАЯ ФАБРИКА ====================

class FurnitureFactory {
public:
    virtual Chair* createChair() = 0;
    virtual Sofa* createSofa() = 0;
    virtual Table* createTable() = 0;
    virtual ~FurnitureFactory() = default;
};

// ==================== КОНКРЕТНЫЕ ФАБРИКИ ====================

class ModernFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() override {
        return new ModernChair();
    }
    
    Sofa* createSofa() override {
        return new ModernSofa();
    }
    
    Table* createTable() override {
        return new ModernTable();
    }
};

class VictorianFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() override {
        return new VictorianChair();
    }
    
    Sofa* createSofa() override {
        return new VictorianSofa();
    }
    
    Table* createTable() override {
        return new VictorianTable();
    }
};

// ==================== КЛИЕНТСКИЙ КОД ====================

class Application {
private:
    Chair* chair;
    Sofa* sofa;
    Table* table;
    
public:
    Application(FurnitureFactory* factory) {
        chair = factory->createChair();
        sofa = factory->createSofa();
        table = factory->createTable();
    }
    
    ~Application() {
        delete chair;
        delete sofa;
        delete table;
    }
    
    void run() {
        std::cout << "=== Работа с мебелью ===" << std::endl;
        chair->sitOn();
        sofa->sitOn();
        sofa->lieOn();
        table->putItem();
        std::cout << "========================" << std::endl;
    }
};

// ==================== ФУНКЦИЯ СОЗДАНИЯ ФАБРИКИ ====================

FurnitureFactory* createFactory(const std::string& style) {
    if (style == "modern") {
        return new ModernFurnitureFactory();
    } else if (style == "victorian") {
        return new VictorianFurnitureFactory();
    }
    // По умолчанию создаём модерн
    return new ModernFurnitureFactory();
}

// ==================== MAIN ====================

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    
    // Создаём фабрику на основе конфигурации/настроек
    std::string furnitureStyle = "modern"; // или "victorian"
    FurnitureFactory* factory = createFactory(furnitureStyle);
    
    // Клиентский код работает только с интерфейсами
    Application app(factory);
    app.run();
    
    delete factory;
    
    // Пример смены стиля мебели
    std::cout << "\nМеняем стиль на викторианский...\n" << std::endl;
    factory = createFactory("victorian");
    
    Application app2(factory);
    app2.run();
    
    delete factory;
    
    return 0;
}