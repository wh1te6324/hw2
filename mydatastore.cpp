 #include "mydatastore.h"
#include <iostream>
#include <set>

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore()
{
    

    for (std::size_t i = 0; i < products_.size(); ++i) delete products_[i];
    products_.clear();

    std::map<std::string, User*>::iterator uit = users_.begin();
    for (; uit != users_.end(); ++uit) delete uit->second;
    users_.clear();

}

void MyDataStore::addProduct(Product* p)
{
    if(p) {
        products_.push_back(p);
    }
}

void MyDataStore::addUser(User* u)
{
    if(u) {
        users_[u->getName()] = u;
    }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    
     std::vector<Product*> results;
    if (terms.empty()) return results;

    std::set<Product*> resultSet;
    for (std::size_t ti = 0; ti < terms.size(); ++ti) {
        std::set<Product*> matches;

        
        for (std::size_t pi = 0; pi < products_.size(); ++pi) {
            Product* p = products_[pi];
            std::set<std::string> keys = p->keywords();

            
            std::set<std::string>::const_iterator kit = keys.find(convToLower(terms[ti]));
            if (kit != keys.end()) {
                matches.insert(p);
            }
        }

        if (ti == 0) {
            resultSet = matches;
        } else {
            if (type == 0) {
               
                resultSet = setIntersection(resultSet, matches);
            } else {
                
                resultSet = setUnion(resultSet, matches);
            }
        }
    }
    std::set<Product*>::const_iterator it = resultSet.begin();
    for (; it != resultSet.end(); ++it) {
        results.push_back(*it);
    }
    return results;
}

void MyDataStore::dump(std::ostream& ofile)
{
     ofile << "<products>" << std::endl;
    for (std::size_t i = 0; i < products_.size(); ++i) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    std::map<std::string, User*>::const_iterator it = users_.begin();
    for (; it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(const std::string& username, Product* p)
{
    std::map<std::string, User*>::const_iterator uit = users_.find(username);
    if (uit == users_.end() || p == NULL) {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    carts_[username].push_back(p);
}

void MyDataStore::viewCart(const std::string& username) const
{
    std::map<std::string, std::vector<Product*> >::const_iterator it =
        carts_.find(username);
    if (it == carts_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    const std::vector<Product*>& cart = it->second;
    if (cart.empty()) {
        std::cout << "Cart is empty" << std::endl;
        return;
    }
    for (std::size_t i = 0; i < cart.size(); ++i) {
        std::cout << "Item " << (i+1) << std::endl;
        std::cout << cart[i]->displayString() << std::endl << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username)
{
    std::map<std::string, User*>::iterator uit = users_.find(username);
    if (uit == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    std::vector<Product*>& cart = carts_[username];
    if (cart.empty()) return;

    std::vector<Product*> remain;
    remain.reserve(cart.size());

    for (std::size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart[i];
        
        if (p->getQty() > 0 && uit->second->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            uit->second->deductAmount(p->getPrice());
        } else {
            remain.push_back(p); 
        }
    }
    cart = remain;
}