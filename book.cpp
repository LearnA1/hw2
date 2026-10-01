#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string &name, double price, int qty, const std::string& isbn, const std::string& author) : Product("book", name, price, qty), isbn_(isbn), author_(author){

  }
  Book::~Book(){

  }
  
  set<string> Book::keywords() const {
    set<string> keys = parseStringToWords(name_);
    set<string> authorKeys = parseStringToWords(author_);

    keys = setUnion(keys, authorKeys);
    keys.insert(convToLower(isbn_));
    return keys;
  }

  string Book::displayString() const
{
    ostringstream oss;
    oss << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Book::dump(ostream& os) const {
    Product::dump(os);

    os << isbn_ << "\n" << author_ << endl;
}