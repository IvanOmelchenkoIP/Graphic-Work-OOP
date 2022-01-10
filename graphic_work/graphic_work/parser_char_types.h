#pragma once

class CharTypes
{
private:
	const std::string nums = "0123456789.";
	const std::string opers = "+-*/^";
	const std::string brackets = "()";
	const std::string variables = "xyz";

	std::map<std::string, int> possiblePriors;

public:
	CharTypes();

	bool IsNumber(std::string);
	bool IsOperator(std::string);
	bool IsBrackets(std::string);
	bool IsVariable(std::string);

	int ReturnPriority(std::string);
};

