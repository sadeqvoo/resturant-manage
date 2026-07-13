#ifndef MEMBERSHIPLEVEL_H
#define MEMBERSHIPLEVEL_H

#include <string>
#include <memory>


class MembershipLevel {
public:
    virtual ~MembershipLevel() = default;


    virtual std::string getLevelName() const = 0;


    virtual double calculateDiscount(double basePrice) const = 0;


    virtual double calculateShippingFee(double baseShipping) const = 0;


    virtual int calculatePointsEarned(double totalAmount) const = 0;


    virtual int getPointsRequiredForNext() const = 0;
};


class NormalLevel : public MembershipLevel {
public:
    std::string getLevelName() const override { return "Normal"; }
    
    double calculateDiscount(double basePrice) const override { 
        return 0.0; 
    }
    
    double calculateShippingFee(double baseShipping) const override { 
        return baseShipping; 
    }
    
    int calculatePointsEarned(double totalAmount) const override { 
        return static_cast<int>(totalAmount * 0.001); 
    }
    
    int getPointsRequiredForNext() const override { 
        return 100; 
    }
};


class SilverLevel : public MembershipLevel {
public:
    std::string getLevelName() const override { return "Silver"; }
    
    double calculateDiscount(double basePrice) const override { 
        return basePrice * 0.05; 
    }
    
    double calculateShippingFee(double baseShipping) const override { 
        return baseShipping * 0.80; 
    }
    
    int calculatePointsEarned(double totalAmount) const override { 
        return static_cast<int>(totalAmount * 0.002); 
    }
    
    int getPointsRequiredForNext() const override { 
        return 300; 
    }
};


class GoldLevel : public MembershipLevel {
public:
    std::string getLevelName() const override { return "Gold"; }
    
    double calculateDiscount(double basePrice) const override { 
        return basePrice * 0.10; 
    }
    
    double calculateShippingFee(double baseShipping) const override { 
        return baseShipping * 0.50; 
    }
    
    int calculatePointsEarned(double totalAmount) const override { 
        return static_cast<int>(totalAmount * 0.003); 
    }
    
    int getPointsRequiredForNext() const override { 
        return 600;
    }
};


class VIPLevel : public MembershipLevel {
public:
    std::string getLevelName() const override { return "VIP"; }
    
    double calculateDiscount(double basePrice) const override { 
        return basePrice * 0.15; 
    }
    
    double calculateShippingFee(double baseShipping) const override { 
        return 0.0; 
    }
    
    int calculatePointsEarned(double totalAmount) const override { 
        return static_cast<int>(totalAmount * 0.005); 
    }
    
    int getPointsRequiredForNext() const override { 
        return 0; 
    }
};

inline std::shared_ptr<MembershipLevel> createMembershipLevel(const std::string& levelStr) {
    if (levelStr == "Silver") return std::make_shared<SilverLevel>();
    if (levelStr == "Gold")   return std::make_shared<GoldLevel>();
    if (levelStr == "VIP")    return std::make_shared<VIPLevel>();
    return std::make_shared<NormalLevel>(); // پیش‌فرض
}

#endif 