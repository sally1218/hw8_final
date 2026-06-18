#ifndef RACKET_H
#define RACKET_H

#include "Equipment.h"

// 衍生類：拍類器材
class Racket : public Equipment {
private:
    std::string racketType;      // 拍類型（網球拍、乒乓拍等）
    std::string frameSize;       // 拍面大小（L、M、S等）
    std::string stringTension;   // 弦張力

public:
    Racket();
    Racket(int id, const std::string& name, double price, bool available,
           const std::string& type, const std::string& size, 
           const std::string& tension);
    
    // 覆寫父類虛擬方法
    void displayInfo() const override;
    std::string getDetails() const override;

    // Getter方法
    std::string getRacketType() const;
    std::string getFrameSize() const;
    std::string getStringTension() const;

    // Setter方法
    void setRacketType(const std::string& type);
    void setFrameSize(const std::string& size);
    void setStringTension(const std::string& tension);
};

#endif
