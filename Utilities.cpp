#include "Utilities.h"

int Util::generate_random_int(int min, int max)
{
	std::random_device random_device;
	std::mt19937 rng(random_device());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(rng);
}

std::string Util::generate_random_string(int max)
{
	const char possible_chars[] =
		"01234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string random_string;
	for (int i = 0; i < max; i++) {
		random_string += (possible_chars[generate_random_int(0, sizeof(possible_chars))]);
	}
	return random_string;
}

Module* Util::findModule(std::vector<Module*> *moduleArrPtr, std::string moduleName) {
	for (int i = 0; i < moduleArrPtr->size(); i++) {
		if (moduleArrPtr->at(i)->getModuleName() == moduleName) {
			return moduleArrPtr->at(i);
		}
	}
	return new Module();
}