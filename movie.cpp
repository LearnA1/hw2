#include <sstream>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const string& name, double price, int qty, const string& genre, const string& rating) : Product("movie", name, price, qty), genre_(genre), rating_(rating)
{
}

Movie::~Movie()
{
}

set<string> Movie::keywords() const
{
    set<string> keys = parseStringToWords(name_);
    keys.insert(convToLower(genre_));  // verbatim apart from case folding
    return keys;
}

string Movie::displayString() const
{
    ostringstream oss;
    oss << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Movie::dump(ostream& os) const
{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}