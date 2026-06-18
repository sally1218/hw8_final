#include "../include/Racket.h"
#include <iostream>

using namespace std;

// 構造函數
Racket::Racket()
    : Equipment(), racketType(""), frameSize(""), stringTension("") {}

Racket::Racket(int id, const string& name, double price, bool available,
               const string& type, const string& size, const string& tension)
    : Equipment(id, name, "拍類", price, available, "拍類運動器材"),
      racketType(type), frameSize(size), stringTension(tension) {}

// 覆寫虛擬方法
void Racket::displayInfo() const {
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║           拍類運動器材詳細資訊              ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    cout << "器材ID: " << id << endl;
    cout << "名稱: " << name << endl;
    cout << "拍類型: " << racketType << endl;
    cout << "拍面大小: " << frameSize << endl;
    cout << "弦張力: " << stringTension << endl;
    cout << "租借價格: $" << rentalPrice << "/天" << endl;
    cout << "狀態: " << (isAvailable ? "✓ 可租借" : "✗ 已租出") << endl;
    cout << "────────────────────────────────────────────" << endl;
}

string Racket::getDetails() const {
    return "拍類-" + racketType + "|尺寸:" + frameSize + "|張力:" + stringTension + "|$" + to_string((int)rentalPrice);
}

// Getter方法
string Racket::getRacketType() const { return racketType; }
string Racket::getFrameSize() const { return frameSize; }
string Racket::getStringTension() const { return stringTension; }

// Setter方法
void Racket::setRacketType(const string& type) { this->racketType = type; }
void Racket::setFrameSize(const string& size) { this->frameSize = size; }
void Racket::setStringTension(const string& tension) { this->stringTension = tension; }
