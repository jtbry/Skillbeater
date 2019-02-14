#pragma once
#include <string>
#include <random>
#include "Module.h"

namespace Util {
	int generate_random_int(int min, int max);
	std::string generate_random_string(int max);
	Module * findModule(std::vector<Module*> *moduleArrPtr, std::string name);
}