#pragma once

#include "CATHODE.h"
#include <string>
#include <vector>

struct ShortGuidWithString
{
	std::string string;
	CATHODE::DataTypes::ShortGuid* shortguid;
};


class ShortGuidTable
{
public:
	static void Add(const char* str, CATHODE::DataTypes::ShortGuid* shortguid_ptr) {
		for (int i = 0; i < table.size(); i++)
			if (table[i].shortguid == shortguid_ptr)
				return;
				
		ShortGuidWithString entry = ShortGuidWithString();
		entry.shortguid = shortguid_ptr;
		entry.string = str;
		table.push_back(entry);
	}

	static std::string Get(CATHODE::DataTypes::ShortGuid* shortguid_ptr) {
		std::string test = "";
		for (int i = 0; i < table.size(); i++)
			if (table[i].shortguid == shortguid_ptr)
				return table[i].string;
		return "";
	}

	static std::vector<ShortGuidWithString> table;
};
