#include "clothing.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Clothing::Clothing(const std::string& name,
                   double price,
                   int qty,
                   const std::string& size,
                   const std::string& brand)
    : Product("clothing", name, price, qty),
      size_(size),
      brand_(brand)
{}

std::set<std::string> Clothing::keywords() const
{
     std::set<std::string> keys = parseStringToWords(convToLower(name_));
    std::set<std::string> b    = parseStringToWords(convToLower(brand_));
    std::set<std::string> s    = parseStringToWords(convToLower(size_));
    keys = setUnion(keys, b);
    keys = setUnion(keys, s);  
    return keys;
}

std::string Clothing::displayString() const
{
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss << std::setprecision(2);

    oss << name_ << "\n"
        << "Size: " << size_ << " Brand: " << brand_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << size_ << "\n"
       << brand_ << "\n";
}