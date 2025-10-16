#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Movies;
struct Movie;

void from_json(const json&, Movie&);
