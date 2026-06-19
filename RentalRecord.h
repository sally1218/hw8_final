#ifndef RENTAL_RECORD_H
#define RENTAL_RECORD_H

#include <string>

// 租借紀錄類別
class RentalRecord {
private:
    int recordId;                // 紀錄ID
    int equipmentId;             // 器材ID
    std::string equipmentName;   // 器材名稱
    std::string renterName;      // 租借人名稱
    std::string rentalDate;      // 租借日期
    std::string returnDate;      // 歸還日期
    int rentalDays;              // 租借天數
    double totalCost;            // 總費用
    bool isReturned;             // 是否已歸還

public:
    RentalRecord();
    RentalRecord(int recordId, int equipId, const std::string& equipName,
                 const std::string& renter, const std::string& rental,
                 const std::string& returnDt, int days, double cost, bool returned);

    // Getter方法
    int getRecordId() const;
    int getEquipmentId() const;
    std::string getEquipmentName() const;
    std::string getRenterName() const;
    std::string getRentalDate() const;
    std::string getReturnDate() const;
    int getRentalDays() const;
    double getTotalCost() const;
    bool getIsReturned() const;

    // Setter方法
    void setReturnDate(const std::string& date);
    void setIsReturned(bool returned);
    void setTotalCost(double cost);

    // 顯示記錄
    void displayRecord() const;

    // 轉換為字符串格式（用於文件存儲）
    std::string toFileFormat() const;
};

#endif
