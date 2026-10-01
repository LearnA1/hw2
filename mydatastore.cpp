#include <iostream>
#include "mydatastore.h"
#include "util.h"
 
using namespace std;

 
MyDataStore::MyDataStore()
{
}
 
MyDataStore::~MyDataStore()
{
    for(size_t i = 0; i < products_.size(); i++) {
        delete products_[i];
    }
    for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}
 
void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);
    set<string> keys = p->keywords();
    for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it) {
        index_[*it].insert(p);
    }
}
 
void MyDataStore::addUser(User* u)
{
    string key = convToLower(u->getName());
    map<string, User*>::iterator it = users_.find(key);
    if(it != users_.end()) {   
        delete u;
        return;
    }
    users_[key] = u;
    carts_[key] = deque<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> hits;
    if(terms.empty()) {
        return hits;  
    }
    set<Product*> result;
    for (size_t i = 0; i < terms.size(); i++) {
        set<Product*> current;
        map<string, set<Product*> >::iterator it = index_.find(convToLower(terms[i]));
        if(it != index_.end()) {
            current = it->second;
        }
        if(i == 0) {
            result = current;
        }
        else if(type == 0) {
            result = setIntersection(result, current);
        }
        else {
            result = setUnion(result, current);
        }
    }
    for(set<Product*>::iterator it = result.begin(); it != result.end(); ++it) {
        hits.push_back(*it);
    }
    return hits;
}
 
void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for(size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}
 
bool MyDataStore::addToCart(const string& username, Product* p)
{
    map<string, deque<Product*> >::iterator it = carts_.find(convToLower(username));
    if(it == carts_.end() || p == NULL) {
        return false;
    }
    it->second.push_back(p);
    return true;
}
 
bool MyDataStore::viewCart(const string& username)
{
    map<string, deque<Product*> >::iterator it = carts_.find(convToLower(username));
    if(it == carts_.end()) {
        return false;
    }
    int n = 1;
    for(deque<Product*>::iterator pit = it->second.begin(); pit != it->second.end(); ++pit) {
        cout << "Item " << n << endl;
        cout << (*pit)->displayString() << endl;
        cout << endl;
        n++;
    }
    return true;
}
 
bool MyDataStore::buyCart(const string& username)
{
    string key = convToLower(username);
    map<string, deque<Product*> >::iterator it = carts_.find(key);
    if(it == carts_.end()) {
        return false;
    }
    User* u = users_[key];
    deque<Product*> remaining;
    for(deque<Product*>::iterator pit = it->second.begin(); pit != it->second.end(); ++pit) {
        Product* p = *pit;
        if(p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        }
        else {
            remaining.push_back(p);
        }
    }
    it->second = remaining;
    return true;
}
 






