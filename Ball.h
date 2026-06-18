#ifndef BALL_H
#define BALL_H

#include "Equipment.h"

// 衍生類：球類器材
class Ball : public Equipment {
private:
    std::string ballType;        // 球類型（籃球、足球、網球等）
    std::string material;        // 材料（橡膠、皮革等）
    double weight;               // 重量（克）

public:
    Ball();
    Ball(int id, const std::string& name, double price, bool available,
         const std::string& type, const std::string& material, double weight);
    
    // 覆寫父類虛擬方法
    void displayInfo() const override;
    std::string getDetails() const override;

    // Getter方法
    std::string getBallType() const;
    std::string getMaterial() const;
    double getWeight() const;

    // Setter方法
    void setBallType(const std::string& type);
    void setMaterial(const std::string& material);
    void setWeight(double weight);
};

#endif
