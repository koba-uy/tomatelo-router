#include <sstream>
#include <string>

using namespace std;

namespace tomatelo {
namespace util {

template<typename T>
void split(const string &s, char delim, T result) {
    string item;
    stringstream ss;
    ss.str(s);
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

}
}