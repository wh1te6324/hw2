#include "book.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Book::Book(const std::string& name,
           double price,
           int qty,
           const std::string& isbn,
           const std::string& author)
    : Product("book", name, price, qty),
      isbn_(isbn),
      author_(author)
{}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> keys = parseStringToWords(convToLower(name_));
    std::set<std::string> a    = parseStringToWords(convToLower(author_));
    keys = setUnion(keys, a);

    keys.insert(convToLower(isbn_));
    std::string isbn_clean;
    for(char c : isbn_) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            isbn_clean.push_back(std::tolower(static_cast<unsigned char>(c)));
        }
    }
    if(!isbn_clean.empty()) keys.insert(isbn_clean);

    return keys;
}

std::string Book::displayString() const
{
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss << std::setprecision(2);

    oss << name_ << "\n"
        << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Book::dump(std::ostream& os) const
{
    
    os << category_ << "\n"
       << name_     << "\n"
       << price_    << "\n"
       << qty_      << "\n"
       << isbn_     << "\n"
       << author_   << "\n";
}