#include "Equipment.h"
#include <iostream>

using namespace std;

// 構造函數
Equipment::Equipment() 
    : id(0), name(""), category(""), rentalPrice(0.0), 
      isAvailable(true), description("") {}

Equipment::Equipment(int id, const string& name, const string& category, 
                     double price, bool available, const string& desc)
    : id(id), name(name), category(category), rentalPrice(price), 
      isAvailable(available), description(desc) {}

// 析構函數
Equipment::~Equipment() {}

// 虛擬方法
void Equipment::displayInfo() const {
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "器材ID: " << id << endl;
    cout << "名稱: " << name << endl;
    cout << "分類: " << category << endl;
    cout << "租借價格: $" << rentalPrice << "/天" << endl;
    cout << "狀態: " << (isAvailable ? "可租借" : "已租出") << endl;
    cout << "描述: " << description << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
}

string Equipment::getDetails() const {
    return "ID:" + to_string(id) + "|名稱:" + name + "|分類:" + category + 
           "|價格:" + to_string(rentalPrice) + "|狀態:" + (isAvailable ? "可租" : "已租");
}

void Equipment::setAvailability(bool available) {
    isAvailable = available;
}

// Getter方法
int Equipment::getId() const { return id; }
string Equipment::getName() const { return name; }
string Equipment::getCategory() const { return category; }
double Equipment::getRentalPrice() const { return rentalPrice; }
bool Equipment::getAvailability() const { return isAvailable; }
string Equipment::getDescription() const { return description; }

// Setter方法
void Equipment::setId(int id) { this->id = id; }
void Equipment::setName(const string& name) { this->name = name; }
void Equipment::setCategory(const string& category) { this->category = category; }
void Equipment::setRentalPrice(double price) { this->rentalPrice = price; }
void Equipment::setDescription(const string& desc) { this->description = desc; }
