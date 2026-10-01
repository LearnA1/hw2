#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <set>
#include <deque>
#include <vector>
#include <string>
#include "datastore.h"

class MyDataStore : public DataStore {

public:
    MyDataStore();
    virtual ~MyDataStore();
 
    virtual void addProduct(Product* p);
    virtual void addUser(User* u);
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
    virtual void dump(std::ostream& ofile);
 
    // Returns false if the user does not exist
    bool addToCart(const std::string& username, Product* p);
    bool viewCart(const std::string& username);
    bool buyCart(const std::string& username);
 
private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;                    
    std::map<std::string, std::set<Product*> > index_;      
    std::map<std::string, std::deque<Product*> > carts_;  
};
#endif
