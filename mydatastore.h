#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include <map>
#include <vector>
#include <set>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    MyDataStore(const MyDataStore&) = delete;
    MyDataStore& operator=(const MyDataStore&) = delete;
    MyDataStore(MyDataStore&&) = delete;               
    MyDataStore& operator=(MyDataStore&&) = delete;

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    void addToCart(const std::string& username, Product* p);
    void viewCart(const std::string& username) const;
    void buyCart(const std::string& username);

    


private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;  

     std::map<std::string, std::vector<Product*> > carts_;
};

#endif