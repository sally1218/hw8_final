#include "../include/RentalSystem.h"
#include "../include/Ball.h"
#include "../include/Racket.h"
#include "../include/ProtectiveGear.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

RentalSystem::RentalSystem()
    : dataDirectory("./data"), nextEquipmentId(1), nextRecordId(1) {}

RentalSystem::~RentalSystem() {
    saveAllData();
}

void RentalSystem::initialize() {
    loadAllData();
    if (equipment.empty()) {
        cout << "Initializing system, loading sample data..." << endl;

        // 添加示例球類器材
        equipment.push_back(make_shared<Ball>(nextEquipmentId++, "籃球", 50.0, true, 
                                             "籃球", "橡膠", 600));
        equipment.push_back(make_shared<Ball>(nextEquipmentId++, "足球", 45.0, true,
                                             "足球", "皮革", 430));
        equipment.push_back(make_shared<Ball>(nextEquipmentId++, "網球", 25.0, true,
                                             "網球", "絨毛", 56.5));

        // 添加示例拍類器材
        equipment.push_back(make_shared<Racket>(nextEquipmentId++, "網球拍", 120.0, true,
                                               "網球拍", "L", "60磅"));
        equipment.push_back(make_shared<Racket>(nextEquipmentId++, "羽毛球拍", 80.0, true,
                                               "羽毛球拍", "M", "高張力"));

        // 添加示例保護裝備
        equipment.push_back(make_shared<ProtectiveGear>(nextEquipmentId++, "安全頭盔", 35.0, true,
                                                        "安全頭盔", "M", "黑色"));
        equipment.push_back(make_shared<ProtectiveGear>(nextEquipmentId++, "護膝", 25.0, true,
                                                        "護膝", "L", "藍色"));
        equipment.push_back(make_shared<ProtectiveGear>(nextEquipmentId++, "護肘", 20.0, true,
                                                        "護肘", "M", "紅色"));

        saveAllData();
        cout << "[OK] System initialization complete!" << endl;
    }
}

// 添加器材
void RentalSystem::addEquipment(shared_ptr<Equipment> equip) {
    if (equip) {
        equip->setId(nextEquipmentId++);
        equipment.push_back(equip);
        cout << "✓ 器材已添加 (ID: " << equip->getId() << ")" << endl;
        saveEquipmentToFile();
    }
}

// 顯示所有器材
void RentalSystem::displayAllEquipment() const {
    if (equipment.empty()) {
        cout << "No equipment in system" << endl;
        return;
    }

    cout << "\n=========================================================" << endl;
    cout << "                ALL EQUIPMENT IN SYSTEM                     " << endl;
    cout << "=========================================================" << endl;

    for (size_t i = 0; i < equipment.size(); ++i) {
        cout << "[" << (i + 1) << "] " << equipment[i]->getDetails() << endl;
    }
    cout << endl;
}

// 顯示可租借器材
void RentalSystem::displayAvailableEquipment() const {
    vector<shared_ptr<Equipment>> available;
    for (const auto& equip : equipment) {
        if (equip->getAvailability()) {
            available.push_back(equip);
        }
    }

    if (available.empty()) {
        cout << "No available equipment for rental" << endl;
        return;
    }

    cout << "\n=========================================================" << endl;
    cout << "               AVAILABLE EQUIPMENT FOR RENTAL              " << endl;
    cout << "=========================================================" << endl;

    for (size_t i = 0; i < available.size(); ++i) {
        cout << "[" << (i + 1) << "] " << available[i]->getDetails() << endl;
    }
    cout << endl;
}

// 查找器材
shared_ptr<Equipment> RentalSystem::findEquipmentById(int id) const {
    for (const auto& equip : equipment) {
        if (equip->getId() == id) {
            return equip;
        }
    }
    return nullptr;
}

// 刪除器材
bool RentalSystem::deleteEquipment(int id) {
    auto it = find_if(equipment.begin(), equipment.end(),
                      [id](const shared_ptr<Equipment>& e) { return e->getId() == id; });
    
    if (it != equipment.end()) {
        equipment.erase(it);
        cout << "✓ 器材已刪除" << endl;
        saveEquipmentToFile();
        return true;
    }
    cout << "✗ 未找到該器材" << endl;
    return false;
}

// 編輯器材
void RentalSystem::editEquipment(int id) {
    auto equip = findEquipmentById(id);
    if (!equip) {
        cout << "✗ 未找到該器材" << endl;
        return;
    }

    equip->displayInfo();
    
    int choice;
    cout << "選擇要修改的項目:" << endl;
    cout << "1. 名稱" << endl;
    cout << "2. 租借價格" << endl;
    cout << "3. 描述" << endl;
    cout << "請輸入: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: {
            string newName;
            cout << "新名稱: ";
            getline(cin, newName);
            equip->setName(newName);
            break;
        }
        case 2: {
            double newPrice;
            cout << "新價格: ";
            cin >> newPrice;
            equip->setRentalPrice(newPrice);
            break;
        }
        case 3: {
            string newDesc;
            cout << "新描述: ";
            getline(cin, newDesc);
            equip->setDescription(newDesc);
            break;
        }
        default:
            cout << "無效選擇" << endl;
            return;
    }

    cout << "✓ 器材已更新" << endl;
    saveEquipmentToFile();
}

// 租借器材
void RentalSystem::rentEquipment(int equipmentId, const string& renterName, int rentalDays) {
    auto equip = findEquipmentById(equipmentId);
    if (!equip) {
        cout << "✗ 器材不存在" << endl;
        return;
    }

    if (!equip->getAvailability()) {
        cout << "✗ 器材已被租出" << endl;
        return;
    }

    string rentalDate = getCurrentDate();
    string returnDate = addDaysToDate(rentalDate, rentalDays);
    double totalCost = equip->getRentalPrice() * rentalDays;

    RentalRecord record(nextRecordId++, equipmentId, equip->getName(), renterName,
                       rentalDate, returnDate, rentalDays, totalCost, false);
    
    rentalRecords.push_back(record);
    equip->setAvailability(false);

    cout << "✓ 租借成功！" << endl;
    cout << "租借紀錄ID: " << record.getRecordId() << endl;
    cout << "租借人: " << renterName << endl;
    cout << "租借日期: " << rentalDate << endl;
    cout << "應歸還日期: " << returnDate << endl;
    cout << "總費用: $" << totalCost << endl;

    saveRentalRecordsToFile();
    saveEquipmentToFile();
}

// 歸還器材
void RentalSystem::returnEquipment(int recordId) {
    auto it = find_if(rentalRecords.begin(), rentalRecords.end(),
                      [recordId](const RentalRecord& r) { return r.getRecordId() == recordId; });
    
    if (it == rentalRecords.end()) {
        cout << "✗ 租借紀錄不存在" << endl;
        return;
    }

    if (it->getIsReturned()) {
        cout << "✗ 該器材已歸還" << endl;
        return;
    }

    auto equip = findEquipmentById(it->getEquipmentId());
    if (equip) {
        equip->setAvailability(true);
    }

    it->setReturnDate(getCurrentDate());
    it->setIsReturned(true);

    cout << "✓ 器材已歸還" << endl;
    cout << "器材: " << it->getEquipmentName() << endl;
    cout << "歸還人: " << it->getRenterName() << endl;
    cout << "總費用: $" << it->getTotalCost() << endl;

    saveRentalRecordsToFile();
    saveEquipmentToFile();
}

// 顯示租借紀錄
void RentalSystem::displayRentalRecords() const {
    if (rentalRecords.empty()) {
        cout << "沒有租借紀錄" << endl;
        return;
    }

    cout << "\n╔═══════════════════════════════════════════════════════════╗" << endl;
    cout << "║               所有租借紀錄                                 ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════╝" << endl;

    for (const auto& record : rentalRecords) {
        record.displayRecord();
    }
    cout << endl;
}

// 顯示用戶租借
void RentalSystem::displayUserRentals(const string& renterName) const {
    vector<RentalRecord> userRentals;
    for (const auto& record : rentalRecords) {
        if (record.getRenterName() == renterName) {
            userRentals.push_back(record);
        }
    }

    if (userRentals.empty()) {
        cout << "用戶 " << renterName << " 沒有租借紀錄" << endl;
        return;
    }

    cout << "\n用戶 " << renterName << " 的租借紀錄:" << endl;
    cout << "────────────────────────────────────────" << endl;
    for (const auto& record : userRentals) {
        record.displayRecord();
    }
}

// 統計方法
void RentalSystem::displayStatistics() const {
    cout << "\n╔═══════════════════════════════════════════════════════════╗" << endl;
    cout << "║               系統統計信息                                 ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════╝" << endl;

    cout << "總器材數: " << equipment.size() << "件" << endl;

    int available = 0, rented = 0;
    for (const auto& equip : equipment) {
        if (equip->getAvailability()) available++;
        else rented++;
    }
    cout << "可租借: " << available << "件" << endl;
    cout << "已租出: " << rented << "件" << endl;

    cout << "\n總租借紀錄: " << rentalRecords.size() << "條" << endl;
    int completed = 0, pending = 0;
    for (const auto& record : rentalRecords) {
        if (record.getIsReturned()) completed++;
        else pending++;
    }
    cout << "已完成: " << completed << "條" << endl;
    cout << "進行中: " << pending << "條" << endl;

    double revenue = calculateRevenue();
    cout << "\n總收入: $" << fixed << setprecision(2) << revenue << endl;
    cout << endl;
}

// 計算收入
double RentalSystem::calculateRevenue() const {
    double total = 0.0;
    for (const auto& record : rentalRecords) {
        if (record.getIsReturned()) {
            total += record.getTotalCost();
        }
    }
    return total;
}

// 搜索方法
void RentalSystem::searchEquipmentByName(const string& name) const {
    vector<shared_ptr<Equipment>> results;
    for (const auto& equip : equipment) {
        if (equip->getName().find(name) != string::npos) {
            results.push_back(equip);
        }
    }

    if (results.empty()) {
        cout << "未找到匹配的器材" << endl;
        return;
    }

    cout << "\n搜索結果 (名稱: " << name << "):" << endl;
    cout << "────────────────────────────────────────" << endl;
    for (const auto& equip : results) {
        cout << equip->getDetails() << endl;
    }
}

void RentalSystem::searchEquipmentByCategory(const string& category) const {
    vector<shared_ptr<Equipment>> results;
    for (const auto& equip : equipment) {
        if (equip->getCategory() == category) {
            results.push_back(equip);
        }
    }

    if (results.empty()) {
        cout << "該分類沒有器材" << endl;
        return;
    }

    cout << "\n" << category << " 分類的器材:" << endl;
    cout << "────────────────────────────────────────" << endl;
    for (const auto& equip : results) {
        cout << equip->getDetails() << endl;
    }
}

// 文件操作方法
void RentalSystem::saveEquipmentToFile() {
    ofstream file("./data/equipment.csv");
    if (!file.is_open()) {
        cerr << "無法打開設備文件" << endl;
        return;
    }

    file << "ID,名稱,分類,價格,狀態,類型,詳細信息\n";
    
    for (const auto& equip : equipment) {
        file << equip->getId() << ","
             << equip->getName() << ","
             << equip->getCategory() << ","
             << equip->getRentalPrice() << ","
             << (equip->getAvailability() ? "可租" : "已租") << ","
             << equip->getDetails() << "\n";
    }
    file.close();
}

void RentalSystem::loadEquipmentFromFile() {
    ifstream file("./data/equipment.csv");
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line); // 跳過頭行

    while (getline(file, line)) {
        if (line.empty()) continue;
        // 這裡可以添加更多的解析邏輯
    }
    file.close();
}

void RentalSystem::saveRentalRecordsToFile() {
    ofstream file("./data/rental_records.csv");
    if (!file.is_open()) {
        cerr << "無法打開租借紀錄文件" << endl;
        return;
    }

    file << "紀錄ID,器材ID,器材名稱,租借人,租借日期,歸還日期,天數,費用,已歸還\n";
    
    for (const auto& record : rentalRecords) {
        file << record.toFileFormat() << "\n";
    }
    file.close();
}

void RentalSystem::loadRentalRecordsFromFile() {
    ifstream file("./data/rental_records.csv");
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line); // 跳過頭行

    while (getline(file, line)) {
        if (line.empty()) continue;
        // 這裡可以添加更多的解析邏輯
    }
    file.close();
}

void RentalSystem::saveAllData() {
    saveEquipmentToFile();
    saveRentalRecordsToFile();
}

void RentalSystem::loadAllData() {
    loadEquipmentFromFile();
    loadRentalRecordsFromFile();
}

// 工具方法
string RentalSystem::getCurrentDate() const {
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    
    ostringstream oss;
    oss << (1900 + timeinfo->tm_year) << "-"
        << setfill('0') << setw(2) << (1 + timeinfo->tm_mon) << "-"
        << setw(2) << timeinfo->tm_mday;
    
    return oss.str();
}

string RentalSystem::addDaysToDate(const string& date, int days) const {
    // 簡單的日期計算（假設YYYY-MM-DD格式）
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    day += days;
    while (day > 31) {
        day -= 31;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    ostringstream oss;
    oss << year << "-" << setfill('0') << setw(2) << month << "-" << setw(2) << day;
    return oss.str();
}

int RentalSystem::calculateDaysDifference(const string& startDate, const string& endDate) const {
    return 0; // 簡化實現
}
