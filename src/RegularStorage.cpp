#include "RegularStorage.h"

RegularStorage::RegularStorage()
{

}

RegularStorage* RegularStorage::_instance = nullptr;

vector<regex> RegularStorage::instructions_storage = {
	std::regex(R"(\s*(div)\s+(r[0-9]|[12][0-9]|3[0-2])\s*,?\s*(r[0-9]|[12][0-9]|3[0-2])\s*,?\s*(r[0-9]|[12][0-9]|3[0-2])\s*,?\s*(r[0-9]|[12][0-9]|3[0-2])\s*)"),// DIV


	//some typical operations
	std::regex(R"(\s*(fadd|fsub|fmul|fdiv)\s+(f[0-9]|[12][0-9]|3[0-2])\s*,?\s*(f[0-9]|[12][0-9]|3[0-2])\s*,?\s*(f[0-9]|[12][0-9]|3[0-2])\s*)"),
	std::regex(R"(\s*(add|sub|mul|and|or|xor|shl|shr)\s+(r[0-9]|[12][0-9]|3[0-2])\s*,?\s*(r[0-9]|[12][0-9]|3[0-2])\s*,?\s*(r[0-9]|[12][0-9]|3[0-2])\s*)"),
	//RAW строку не переносим "для удобного чтения" потому что перенос будет считаться частью патеран DO NOT BROKE LINE WITH ENTER, WILL NOT WORK

	

	std::regex(R"(\s*(not)\s+(r[0-9]|[12][0-9]|3[0-2])\s*,?\s*(r[0-9]|[12][0-9]|3[0-2])\s*)"), // NOT


	// ALU - Other operations
	std::regex(R"(\s*(cmp)\s+(r[0-9]|[12][0-9]|3[0-2])\s*,?\s*(r[0-9]|[12][0-9]|3[0-2])\s*)"), // CMP
	std::regex(R"(\s*(cmp)\s+(f[0-9]|[12][0-9]|3[0-2])\s*,?\s*(f[0-9]|[12][0-9]|3[0-2])\s*)"),
	std::regex(R"(\s*(inc)\s+(r[0-9]|[12][0-9]|3[0-2])\s*)"), // INC
	std::regex(R"(\s*(dec)\s+(r[0-9]|[12][0-9]|3[0-2])\s*)"), // DEC

	// Jump operations
	std::regex(R"(\s*(jmp|je|jge|jl|jg|jle|jne)\s+\[\s*(.+?)\s*\]\s*)"), // JMPS

	// Memory operations
	std::regex(R"(\s*(ld)\s*(\[.*\])\s*,?\s*([rf](?:[0-9]|[12][0-9]|3[0-2]))\s*)"), // LD
	std::regex(R"(\s*(st)\s*([rf](?:[0-9]|[12][0-9]|3[0-2]))\s*,?\s*(\[.*\])\s*)"), // ST
	std::regex(R"(\s*(mov)\s*(r(?:[0-9]|[12][0-9]|3[0-2]))\s*,?\s*(r(?:[0-9]|[12][0-9]|3[0-2]))\s*)"),
	std::regex(R"(\s*(mov)\s*(f(?:[0-9]|[12][0-9]|3[0-2]))\s*,?\s*(f(?:[0-9]|[12][0-9]|3[0-2]))\s*)")// MOV
};

vector<regex> RegularStorage::memory_storage = {
	regex(R"(\[\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\s*(\+|\-)\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\s*\])"), // reg+reg
	regex(R"(\[\s*(\d+)\s*(\+|\-)\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\s*\])"), // const+reg
	regex(R"(\[\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\s*(\+|\-)\s*(\d+)\s*\])"), // reg+const
	regex(R"(\[\s*(\d+)\s*\])"), // const
	regex(R"(\[\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\s*\])") // reg
};





RegularStorage* RegularStorage::Instance()
{
	if (_instance == nullptr)
		_instance = new RegularStorage();
	return _instance;
}


const vector<regex>& RegularStorage::getInstructionsStorage()
{
	return instructions_storage;
}

const vector<regex>& RegularStorage::getMemoryStorage()
{
	return memory_storage;
}