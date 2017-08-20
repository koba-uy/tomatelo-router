#include <exception>
#include <fstream>
#include <iostream>
#include "osrm/osrm.hpp"

#include "router/Router.cpp"
#include "util/split.cpp"

using namespace std;
using namespace tomatelo::router;
using namespace tomatelo::util;

int main(int argc, char** argv) {
    
    auto coordinates = vector<Coordinate>();
    auto timestamps = vector<unsigned>();

    ifstream file(argv[1]);
    string line;
    
    while (getline(file, line)) {
        auto a = split(line, ',');
        coordinates.push_back({util::FloatLongitude{stof(a[0])}, util::FloatLatitude{stof(a[1])}});
        timestamps.push_back(stol(a[2]));
    }

    try {
        auto router = Router();
        auto response = router.match(coordinates, timestamps);
        for (auto match : response) cout << match << endl;
    }
    catch (exception ex) {
        cout << ex.what();
    }

}