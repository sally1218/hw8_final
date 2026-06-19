#include "Ball.h"
#include <iostream>

using namespace std;

// 構造函數
Ball::Ball() 
    : Equipment(), ballType(""), material(""), weight(0.0) {}

Ball::Ball(int id, const string& name, double price, bool available,
           const string& type, const string& material, double weight)
    : Equipment(id, name, "球類", price, available, "球類運動器材"),
      ballType(type), material(material), weight(weight) {}

// 覆寫虛擬方法
void Ball::displayInfo() const {
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║           球類運動器材詳細資訊              ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    cout << "器材ID: " << id << endl;
    cout << "名稱: " << name << endl;
    cout << "球類型: " << ballType << endl;
    cout << "材料: " << material << endl;
    cout << "重量: " << weight << "克" << endl;
    cout << "租借價格: $" << rentalPrice << "/天" << endl;
    cout << "狀態: " << (isAvailable ? "✓ 可租借" : "✗ 已租出") << endl;
    cout << "────────────────────────────────────────────" << endl;
}

string Ball::getDetails() const {
    return "球類-" + ballType + "|材料:" + material + "|重量:" + to_string((int)weight) + "g|$" + to_string((int)rentalPrice);
}

// Getter方法
string Ball::getBallType() const { return ballType; }
string Ball::getMaterial() const { return material; }
double Ball::getWeight() const { return weight; }

// Setter方法
void Ball::setBallType(const string& type) { this->ballType = type; }
void Ball::setMaterial(const string& material) { this->material = material; }
void Ball::setWeight(double weight) { this->weight = weight; }
