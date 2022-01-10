#pragma once

class ExpressionParser
{
private:
	CharTypes cType;

	std::string inputExpr;


	//defining order of variables
	std::string firstVar;
	std::string secondVar;
	std::string thirdVar;

	std::map<std::string, int> varOrder;
	std::map<int, double> varValues;


	//original copies of parsed structures
	std::map<int, std::string> exprNumbers;

	std::map<int, std::string> exprOperators;
	std::map<int, int> exprPriorities;
	std::map<int, std::string> exprBrackets;
	std::map<int, std::string> exprVariables;

	std::map<int, double> numsOrganized;

	//backup copies for counting
	std::map<int, std::string> opersBackup;
	std::map<int, int> priorsBackup;
	std::map<int, std::string> bracketsBackup;
	std::map<int, std::string> varsBackup;
	std::map<int, double> numsBackup;


	//private methods
	void BracketExpression();

	//parsing
	bool Parse();

	bool ParseToChars();
	void OrganizeNumbers();

	void AssignVariableOrder();

	//calculating
	void Calculate();

	bool IterateBrackets(double, double);
	double CountInInterval(int, int, double, double);

public:
	void EvaluateToVertexes(std::string);

};

