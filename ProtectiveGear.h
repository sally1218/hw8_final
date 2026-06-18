#ifndef PROTECTIVE_GEAR_H
#define PROTECTIVE_GEAR_H

#include "Equipment.h"

// 衍生類：保護裝備
class ProtectiveGear : public Equipment {
private:
    std::string gearType;        // 裝備類型（頭盔、護膝等）
    std::string size;            // 尺寸（S、M、L、XL）
    std::string color;           // 顏色

public:
    ProtectiveGear();
    ProtectiveGear(int id, const std::string& name, double price, bool available,
                   const std::string& type, const std::string& size, 
                   const std::string& color);
    
    // 覆寫父類虛擬方法
    void displayInfo() const override;
    std::string getDetails() const override;

    // Getter方法
    std::string getGearType() const;
    std::string getSize() const;
    std::string getColor() const;

    // Setter方法
    void setGearType(const std::string& type);
    void setSize(const std::string& size);
    void setColor(const std::string& color);
};

#endif
