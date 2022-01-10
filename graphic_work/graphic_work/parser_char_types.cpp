#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include "parser_char_types.h"

//Char Types
CharTypes::CharTypes()
{
	possiblePriors["+"] = 10;
	possiblePriors["-"] = 10;
	possiblePriors["*"] = 20;
	possiblePriors["/"] = 20;
	possiblePriors["^"] = 30;
}

bool CharTypes::IsNumber(std::string c)
{
	if (nums.find(c) != -1) return true;
	return false;

}

bool CharTypes::IsOperator(std::string c)
{
	if (opers.find(c) != -1) return true;
	return false;
}

bool CharTypes::IsBrackets(std::string c)
{
	if (brackets.find(c) != -1) return true;
	return false;
}

bool CharTypes::IsVariable(std::string c)
{
	if (variables.find(c) != -1) return true;
	return false;
}

int CharTypes::ReturnPriority(std::string c)
{
	int priority = possiblePriors[c];
	return priority;
}
