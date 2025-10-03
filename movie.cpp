#include "movie.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Movie::Movie(const std::string& name,
             double price,
             int qty,
             const std::string& genre,
             const std::string& rating)
    : Product("movie", name, price, qty),
      genre_(genre),
      rating_(rating)
{}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keys = parseStringToWords(convToLower(name_));
    std::set<std::string> g    = parseStringToWords(convToLower(genre_));
    std::set<std::string> r    = parseStringToWords(convToLower(rating_));
    keys = setUnion(keys, g);
    keys = setUnion(keys, r);
    return keys;
}

std::string Movie::displayString() const
{
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss << std::setprecision(2);

    oss << name_ << "\n"
        << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << genre_ << "\n"
       << rating_ << "\n";
}