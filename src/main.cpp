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
        try {
            auto a = split(line, ' ');
            coordinates.push_back({util::FloatLongitude{stof(a[2])}, util::FloatLatitude{stof(a[1])}});
            timestamps.push_back(stol(a[0]) / 1000);
        }
        catch (...) {
        }
    }

    auto argv0 = string(argv[0]);
    auto path = argv0.substr(0, argv0.find_last_of("\\/"));
    auto router = Router(path);
    auto response = router.match(coordinates, timestamps);
    for (auto match : response) cout << match << endl;

}