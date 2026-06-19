#include "RentalRecord.h"
#include <iostream>

using namespace std;

// 構造函數
RentalRecord::RentalRecord()
    : recordId(0), equipmentId(0), equipmentName(""), renterName(""),
      rentalDate(""), returnDate(""), rentalDays(0), totalCost(0.0), isReturned(false) {}

RentalRecord::RentalRecord(int recordId, int equipId, const string& equipName,
                           const string& renter, const string& rental,
                           const string& returnDt, int days, double cost, bool returned)
    : recordId(recordId), equipmentId(equipId), equipmentName(equipName),
      renterName(renter), rentalDate(rental), returnDate(returnDt),
      rentalDays(days), totalCost(cost), isReturned(returned) {}

// Getter方法
int RentalRecord::getRecordId() const { return recordId; }
int RentalRecord::getEquipmentId() const { return equipmentId; }
string RentalRecord::getEquipmentName() const { return equipmentName; }
string RentalRecord::getRenterName() const { return renterName; }
string RentalRecord::getRentalDate() const { return rentalDate; }
string RentalRecord::getReturnDate() const { return returnDate; }
int RentalRecord::getRentalDays() const { return rentalDays; }
double RentalRecord::getTotalCost() const { return totalCost; }
bool RentalRecord::getIsReturned() const { return isReturned; }

// Setter方法
void RentalRecord::setReturnDate(const string& date) { this->returnDate = date; }
void RentalRecord::setIsReturned(bool returned) { this->isReturned = returned; }
void RentalRecord::setTotalCost(double cost) { this->totalCost = cost; }

// 顯示記錄
void RentalRecord::displayRecord() const {
    cout << "──────────────────────────────────────────" << endl;
    cout << "紀錄ID: " << recordId << endl;
    cout << "器材: " << equipmentName << " (ID: " << equipmentId << ")" << endl;
    cout << "租借人: " << renterName << endl;
    cout << "租借日期: " << rentalDate << " → 歸還日期: " << returnDate << endl;
    cout << "租借天數: " << rentalDays << "天" << endl;
    cout << "總費用: $" << totalCost << endl;
    cout << "狀態: " << (isReturned ? "✓ 已歸還" : "⏳ 租借中") << endl;
}

// 轉換為字符串格式
string RentalRecord::toFileFormat() const {
    return to_string(recordId) + "," + to_string(equipmentId) + "," + 
           equipmentName + "," + renterName + "," + rentalDate + "," + 
           returnDate + "," + to_string(rentalDays) + "," + 
           to_string(totalCost) + "," + (isReturned ? "1" : "0");
}
