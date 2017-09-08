#include <exception>
#include <iostream>
#include <string>
#include "osrm/coordinate.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/json_container.hpp"
#include "osrm/match_parameters.hpp"
#include "osrm/osrm.hpp"
#include "osrm/status.hpp"

using namespace osrm;
using namespace std;

namespace tomatelo {
namespace router {

class Router {

private:

    EngineConfig config;

public:

    Router(const string& osrmFolderPath) {
        // Configure based on a .osrm base path, and no datasets in shared mem from osrm-datastore
        config.storage_config = { osrmFolderPath + "/../data/osrm/uruguay/uruguay-latest.osrm" };
        config.use_shared_memory = false;
    }

    vector<string> match(vector<Coordinate> coordinates, vector<unsigned> timestamps) {
        const OSRM osrm{config};

        MatchParameters params;
        params.coordinates = coordinates;
        params.timestamps = timestamps;
        
        json::Object result;
        
        switch (osrm.Match(params, result)) {

            case Status::Ok: {
                auto& matchings = result.values["matchings"].get<json::Array>();
                auto geometries = vector<string>();
                
                for (int i = 0; i < matchings.values.size(); i++) {
                    auto& matching = matchings.values.at(i).get<json::Object>();
                    geometries.push_back(matching.values["geometry"].get<json::String>().value);
                }

                return geometries;
            }

            case Status::Error: {
                const auto code = result.values["code"].get<json::String>().value;
                const auto message = result.values["message"].get<json::String>().value;
                throw runtime_error(code + " " + message);
            }

        }
    }

};

}
}