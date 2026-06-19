#include "ProtectiveGear.h"
#include <iostream>

using namespace std;

// 構造函數
ProtectiveGear::ProtectiveGear()
    : Equipment(), gearType(""), size(""), color("") {}

ProtectiveGear::ProtectiveGear(int id, const string& name, double price, bool available,
                               const string& type, const string& size, const string& color)
    : Equipment(id, name, "保護裝備", price, available, "保護裝備"),
      gearType(type), size(size), color(color) {}

// 覆寫虛擬方法
void ProtectiveGear::displayInfo() const {
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║            保護裝備詳細資訊                 ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    cout << "器材ID: " << id << endl;
    cout << "名稱: " << name << endl;
    cout << "裝備類型: " << gearType << endl;
    cout << "尺寸: " << size << endl;
    cout << "顏色: " << color << endl;
    cout << "租借價格: $" << rentalPrice << "/天" << endl;
    cout << "狀態: " << (isAvailable ? "✓ 可租借" : "✗ 已租出") << endl;
    cout << "────────────────────────────────────────────" << endl;
}

string ProtectiveGear::getDetails() const {
    return "保護裝備-" + gearType + "|尺寸:" + size + "|顏色:" + color + "|$" + to_string((int)rentalPrice);
}

// Getter方法
string ProtectiveGear::getGearType() const { return gearType; }
string ProtectiveGear::getSize() const { return size; }
string ProtectiveGear::getColor() const { return color; }

// Setter方法
void ProtectiveGear::setGearType(const string& type) { this->gearType = type; }
void ProtectiveGear::setSize(const string& size) { this->size = size; }
void ProtectiveGear::setColor(const string& color) { this->color = color; }
