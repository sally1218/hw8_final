#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <ctime>

// 基類：運動器材
class Equipment {
protected:
    int id;                      // 器材ID
    std::string name;            // 器材名稱
    std::string category;        // 器材分類
    double rentalPrice;          // 租借價格（每天）
    bool isAvailable;            // 是否可租借
    std::string description;     // 器材描述

public:
    Equipment();
    Equipment(int id, const std::string& name, const std::string& category, 
              double price, bool available, const std::string& desc);
    virtual ~Equipment();

    // 虛擬方法
    virtual void displayInfo() const;
    virtual std::string getDetails() const;
    virtual void setAvailability(bool available);

    // Getter方法
    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getRentalPrice() const;
    bool getAvailability() const;
    std::string getDescription() const;

    // Setter方法
    void setId(int id);
    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setRentalPrice(double price);
    void setDescription(const std::string& desc);
};

#endif
