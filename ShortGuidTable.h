#pragma once

#include <string>
#include <vector>
#include "Datatypes.h"

struct ShortGuidWithString
{
	std::string string;
	DataTypes::ShortGuid shortguid;
};


class ShortGuidTable
{
public:
	static void Add(const char* str, DataTypes::ShortGuid shortguid) {
		for (int i = 0; i < table.size(); i++)
			if (table[i].shortguid == shortguid)
				return;

		ShortGuidWithString entry = ShortGuidWithString();
		entry.shortguid = shortguid;
		entry.string = str;
		table.push_back(entry);
	}

	static std::string Get(DataTypes::ShortGuid shortguid) {
		std::string test = "";
		for (int i = 0; i < table.size(); i++)
			if (table[i].shortguid == shortguid)
				return table[i].string;
		return "";
	}

	static std::vector<ShortGuidWithString> table;
};
