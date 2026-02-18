// ==================== ПРОДУКТ (ДОМ) ====================

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <Windows.h>
class House {
private:
    int walls;
    int doors;
    int windows;
    bool hasRoof;
    bool hasGarden;
    bool hasPool;
    std::string wallMaterial;
    std::string roofMaterial;
    
public:
    House() : walls(0), doors(0), windows(0), hasRoof(false), 
              hasGarden(false), hasPool(false), wallMaterial(""), roofMaterial("") {}
    
    void setWalls(int count) { walls = count; }
    void setDoors(int count) { doors = count; }
    void setWindows(int count) { windows = count; }
    void setRoof(bool value) { hasRoof = value; }
    void setGarden(bool value) { hasGarden = value; }
    void setPool(bool value) { hasPool = value; }
    void setWallMaterial(const std::string& material) { wallMaterial = material; }
    void setRoofMaterial(const std::string& material) { roofMaterial = material; }
    
    void showInfo() const {
        std::cout << "\n=== ХАРАКТЕРИСТИКИ ДОМА ===" << std::endl;
        std::cout << "Стены: " << walls << " шт. (" << wallMaterial << ")" << std::endl;
        std::cout << "Двери: " << doors << " шт." << std::endl;
        std::cout << "Окна: " << windows << " шт." << std::endl;
        std::cout << "Крыша: " << (hasRoof ? "есть (" + roofMaterial + ")" : "нет") << std::endl;
        std::cout << "Сад: " << (hasGarden ? "есть" : "нет") << std::endl;
        std::cout << "Бассейн: " << (hasPool ? "есть" : "нет") << std::endl;
        std::cout << "==========================\n" << std::endl;
    }
};

// ==================== ИНТЕРФЕЙС СТРОИТЕЛЯ ====================

class HouseBuilder {
protected:
    std::unique_ptr<House> house;
    
public:
    HouseBuilder() { house = std::make_unique<House>(); }
    virtual ~HouseBuilder() = default;
    
    virtual void buildWalls() = 0;
    virtual void installDoors() = 0;
    virtual void installWindows() = 0;
    virtual void buildRoof() = 0;
    virtual void addGarden() = 0;
    virtual void addPool() = 0;
    
    std::unique_ptr<House> getHouse() {
        return std::move(house);
    }
};

// ==================== КОНКРЕТНЫЕ СТРОИТЕЛИ ====================

// Деревянный дом
class WoodenHouseBuilder : public HouseBuilder {
public:
    void buildWalls() override {
        std::cout << "Строим деревянные стены..." << std::endl;
        house->setWalls(4);
        house->setWallMaterial("дерево");
    }
    
    void installDoors() override {
        std::cout << "Устанавливаем деревянные двери..." << std::endl;
        house->setDoors(2);
    }
    
    void installWindows() override {
        std::cout << "Вставляем деревянные окна..." << std::endl;
        house->setWindows(4);
    }
    
    void buildRoof() override {
        std::cout << "Строим деревянную крышу..." << std::endl;
        house->setRoof(true);
        house->setRoofMaterial("дерево");
    }
    
    void addGarden() override {
        std::cout << "Разбиваем сад..." << std::endl;
        house->setGarden(true);
    }
    
    void addPool() override {
        // Деревянные дома обычно без бассейна
        std::cout << "Бассейн не предусмотрен для деревянного дома" << std::endl;
        house->setPool(false);
    }
};

// Каменный дом
class StoneHouseBuilder : public HouseBuilder {
public:
    void buildWalls() override {
        std::cout << "Строим каменные стены..." << std::endl;
        house->setWalls(4);
        house->setWallMaterial("камень");
    }
    
    void installDoors() override {
        std::cout << "Устанавливаем металлические двери..." << std::endl;
        house->setDoors(3);
    }
    
    void installWindows() override {
        std::cout << "Вставляем пластиковые окна..." << std::endl;
        house->setWindows(6);
    }
    
    void buildRoof() override {
        std::cout << "Строим черепичную крышу..." << std::endl;
        house->setRoof(true);
        house->setRoofMaterial("черепица");
    }
    
    void addGarden() override {
        std::cout << "Разбиваем сад с фонтаном..." << std::endl;
        house->setGarden(true);
    }
    
    void addPool() override {
        std::cout << "Строим бассейн..." << std::endl;
        house->setPool(true);
    }
};

// Роскошный дом (из золота и бриллиантов)
class LuxuryHouseBuilder : public HouseBuilder {
public:
    void buildWalls() override {
        std::cout << "Строим стены из золота и бриллиантов..." << std::endl;
        house->setWalls(8);
        house->setWallMaterial("золото и бриллианты");
    }
    
    void installDoors() override {
        std::cout << "Устанавливаем золотые двери с инкрустацией..." << std::endl;
        house->setDoors(5);
    }
    
    void installWindows() override {
        std::cout << "Вставляем витражные окна с золотой отделкой..." << std::endl;
        house->setWindows(12);
    }
    
    void buildRoof() override {
        std::cout << "Строим золотую крышу..." << std::endl;
        house->setRoof(true);
        house->setRoofMaterial("золото");
    }
    
    void addGarden() override {
        std::cout << "Создаём роскошный сад с скульптурами..." << std::endl;
        house->setGarden(true);
    }
    
    void addPool() override {
        std::cout << "Строим бассейн с мраморной отделкой..." << std::endl;
        house->setPool(true);
    }
};

// ==================== ДИРЕКТОР (УПРАВЛЯЕТ СТРОИТЕЛЬСТВОМ) ====================

class Director {
private:
    HouseBuilder* builder;
    
public:
    void setBuilder(HouseBuilder* b) {
        builder = b;
    }
    
    // Построить стандартный дом (базовая конфигурация)
    void buildStandardHouse() {
        std::cout << "\n=== Строим стандартный дом ===" << std::endl;
        builder->buildWalls();
        builder->installDoors();
        builder->installWindows();
        builder->buildRoof();
        // Без сада и бассейна для стандартного дома
    }
    
    // Построить дом с удобствами
    void buildComfortableHouse() {
        std::cout << "\n=== Строим комфортабельный дом ===" << std::endl;
        builder->buildWalls();
        builder->installDoors();
        builder->installWindows();
        builder->buildRoof();
        builder->addGarden();
        // Без бассейна
    }
    
    // Построить полный дом (со всеми удобствами)
    void buildFullHouse() {
        std::cout << "\n=== Строим дом полной комплектации ===" << std::endl;
        builder->buildWalls();
        builder->installDoors();
        builder->installWindows();
        builder->buildRoof();
        builder->addGarden();
        builder->addPool();
    }
};

// ==================== КЛИЕНТСКИЙ КОД ====================

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    
    Director director;
    std::unique_ptr<House> house;
    
    // Пример 1: Деревянный дом (стандартный)
    WoodenHouseBuilder woodenBuilder;
    director.setBuilder(&woodenBuilder);
    director.buildStandardHouse();
    house = woodenBuilder.getHouse();
    house->showInfo();
    
    // Пример 2: Каменный дом (с садом)
    StoneHouseBuilder stoneBuilder;
    director.setBuilder(&stoneBuilder);
    director.buildComfortableHouse();
    house = stoneBuilder.getHouse();
    house->showInfo();
    
    // Пример 3: Роскошный дом (полная комплектация)
    LuxuryHouseBuilder luxuryBuilder;
    director.setBuilder(&luxuryBuilder);
    director.buildFullHouse();
    house = luxuryBuilder.getHouse();
    house->showInfo();
    
    // Пример 4: Каменный дом с бассейном (пошаговое строительство)
    std::cout << "\n=== Индивидуальное строительство ===" << std::endl;
    StoneHouseBuilder customBuilder;
    customBuilder.buildWalls();
    customBuilder.installDoors();
    customBuilder.installWindows();
    customBuilder.buildRoof();
    customBuilder.addPool(); // Только бассейн, без сада
    house = customBuilder.getHouse();
    house->showInfo();
    
    std::cout << "========================================" << std::endl;
    std::cout << "   ВСЕ ДОМА ПОСТРОЕНЫ!" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}