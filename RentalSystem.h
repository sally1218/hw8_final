#ifndef RENTAL_SYSTEM_H
#define RENTAL_SYSTEM_H

#include <vector>
#include <string>
#include <memory>
#include "Equipment.h"
#include "RentalRecord.h"

// 租借系統類別
class RentalSystem {
private:
    std::vector<std::shared_ptr<Equipment>> equipment;  // 器材列表
    std::vector<RentalRecord> rentalRecords;            // 租借紀錄
    std::string dataDirectory;                          // 數據目錄
    int nextEquipmentId;                                // 下一個器材ID
    int nextRecordId;                                   // 下一個紀錄ID

public:
    RentalSystem();
    ~RentalSystem();

    // 初始化方法
    void initialize();

    // 器材管理方法
    void addEquipment(std::shared_ptr<Equipment> equip);
    void displayAllEquipment() const;
    void displayAvailableEquipment() const;
    std::shared_ptr<Equipment> findEquipmentById(int id) const;
    bool deleteEquipment(int id);
    void editEquipment(int id);

    // 租借方法
    void rentEquipment(int equipmentId, const std::string& renterName, int rentalDays);
    void returnEquipment(int recordId);
    void displayRentalRecords() const;
    void displayUserRentals(const std::string& renterName) const;

    // 統計方法
    void displayStatistics() const;
    double calculateRevenue() const;

    // 文件操作方法
    void saveEquipmentToFile();
    void loadEquipmentFromFile();
    void saveRentalRecordsToFile();
    void loadRentalRecordsFromFile();
    void saveAllData();
    void loadAllData();

    // 查詢方法
    void searchEquipmentByName(const std::string& name) const;
    void searchEquipmentByCategory(const std::string& category) const;

    // 工具方法
    std::string getCurrentDate() const;
    std::string addDaysToDate(const std::string& date, int days) const;

private:
    int calculateDaysDifference(const std::string& startDate, const std::string& endDate) const;
};

#endif
