#include "framework.h"
#include "glut.h"

#include <string>	
#include <map>
#include <vector>
#include <math.h>
#include "parser_char_types.h"
#include "parser_equation.h"

//ExpressionParser
void ExpressionParser::EvaluateToVertexes(std::string expr)
{
	inputExpr = expr;
	if (!inputExpr.size()) return;

	BracketExpression();
	if (!Parse()) return;;
	Calculate();
}

void ExpressionParser::BracketExpression()
{
	std::string rightStr;
	std::string leftStr;
	for (int i = 0; i < inputExpr.size(); i++)
	{
		std::string c = inputExpr.substr(i, 1);
		if (c == "=")
		{
			rightStr = inputExpr.substr(0, i + 1);
			leftStr = inputExpr.substr(i + 1, inputExpr.size());
			break;
		}
	}
	inputExpr = rightStr + "(" + leftStr + ")";
}

//parsing the received expression
//----------------------------------
bool ExpressionParser::Parse()
{
	if (!ParseToChars()) return false;
	OrganizeNumbers();
	AssignVariableOrder();
	return true;
};

bool ExpressionParser::ParseToChars()
{
	std::string tmp;
	for (int i = 0; i < inputExpr.size(); i++)
	{
		std::string character = inputExpr.substr(i, 1);

		if (character == " " || character == "=")
		{
			continue;
		}
		else if (cType.IsNumber(character))
		{
			exprNumbers[i] = character;
		}
		else if (cType.IsOperator(character))
		{
			exprOperators[i] = character;
			exprPriorities[i] = cType.ReturnPriority(character);
		}
		else if (cType.IsBrackets(character))
		{
			exprBrackets[i] = character;
		}
		else if (cType.IsVariable(character))
		{
			exprVariables[i] = character;
		}
		else
		{
			return false;
		}
	}
	return true;
}

void ExpressionParser::OrganizeNumbers()
{
	std::string tmp;
	int prev = -1;

	int ind = 0;
	int size = exprNumbers.size();
	std::vector<int> keys(size);
	std::vector<std::string> values(size);

	for (auto iter = exprNumbers.begin(); iter != exprNumbers.end(); iter++)
	{
		int key = iter->first;
		std::string value = iter->second;

		keys[ind] = key;
		values[ind] = value;

		ind += 1;
	}

	for (int i = 0; i < size; i++)
	{
		int key = keys[i];
		std::string value = values[i];

		if (key - prev > 1 && prev != -1)
		{
			numsOrganized[prev] = (double)atof(tmp.c_str());
			tmp.erase();
		}

		tmp += values[i];
		prev = keys[i];

		if (i == size - 1)
		{
			numsOrganized[key] = (double)atof(tmp.c_str());
		}
	}
}

void ExpressionParser::AssignVariableOrder()
{
	bool firstIter;
	bool assignedFirst = false;
	bool assignedSecond = false;

	for (auto iter = exprVariables.begin(); iter != exprVariables.end(); iter++)
	{
		std::string var = iter->second;

		if (!assignedFirst)
		{
			varOrder[var] = 1;
			firstVar = var;
			assignedFirst = true;
			continue;
		}
		if (!assignedSecond)
		{
			varOrder[var] = 2;
			secondVar = var;
			assignedSecond = true;
			continue;
		}
		if (var != firstVar && var != secondVar)
		{
			varOrder[var] = 3;
			thirdVar = var;
			break;
		}
	}
}
//--------------------------

//calculating expression results
void ExpressionParser::Calculate()
{
	for (double i = 0; i < 1;)
	{
		for (double j = 0; j < 1;)
		{
			varValues[2] = i;
			varValues[3] = j;

			opersBackup = exprOperators;
			priorsBackup = exprPriorities;
			bracketsBackup = exprBrackets;
			varsBackup = exprVariables;
			numsBackup = numsOrganized;

			while (true)
			{
				if (IterateBrackets(i, j)) break;
			}

			double x = varValues[varOrder["x"]];
			double y = varValues[varOrder["y"]];
			double z = varValues[varOrder["z"]];

			glVertex3f(x, y, z);

			j += 0.1;
		}
		i += 0.1;
	}
}

bool ExpressionParser::IterateBrackets(double value2, double value3)
{
	if (!bracketsBackup.size()) return true;;

	int left, right;
	for (auto iter = bracketsBackup.begin(); iter != bracketsBackup.end(); iter++)
	{
		int index = iter->first;
		std::string bracket = iter->second;

		if (bracket == "(")
		{
			left = index;
		}
		else if (bracket == ")")
		{
			right = index;

			double result = CountInInterval(left, right, value2, value3);
			varValues[1] = result;

			break;
		}
	}
	bracketsBackup.erase(left);
	bracketsBackup.erase(right);
	return false;
}

double ExpressionParser::CountInInterval(int left, int right, double value2, double value3)
{
	int assignInd;

	//creating temporary structure for operators
	std::map<int, std::string> tmpOpers;
	std::map<int, int> tmpPriors;

	for (auto iter = opersBackup.begin(); iter != opersBackup.end(); iter++)
	{
		int index = iter->first;
		std::string oper = iter->second;

		if (left > index) continue;
		if (index > right) break;

		tmpOpers[index] = oper;
		tmpPriors[index] = priorsBackup[index];
	}

	for (auto iter = tmpOpers.begin(); iter != tmpOpers.end(); iter++)
	{
		int index = iter->first;

		opersBackup.erase(index);
		priorsBackup.erase(index);
	}

	//creating temporary structure for numbers
	std::map<int, double> tmpNums;

	for (auto iter = numsBackup.begin(); iter != numsBackup.end(); iter++)
	{
		int index = iter->first;
		double num = iter->second;

		if (left > index) continue;
		if (index > right) break;

		tmpNums[index] = num;
		assignInd = index;
	}

	for (auto iter = tmpNums.begin(); iter != tmpNums.end(); iter++)
	{
		int index = iter->first;

		numsBackup.erase(index);
	}

	//assigning variables
	std::map<int, std::string> tmpVars;

	for (auto iter = varsBackup.begin(); iter != varsBackup.end(); iter++)
	{
		int index = iter->first;
		std::string var = iter->second;

		if (left > index) continue;
		if (index > right) break;

		tmpVars[index] = var;
	}

	for (auto iter = tmpVars.begin(); iter != tmpVars.end(); iter++)
	{
		int index = iter->first;
		std::string var = iter->second;

		if (var == secondVar)  tmpNums[index] = value2;
		else if (var == thirdVar) tmpNums[index] = value3;

		varsBackup.erase(index);
	}


	//counting loop
	double innerResult;
	while (true)
	{
		//break condition
		if (tmpNums.size() <= 1 && !tmpOpers.size()) break;

		//getting numbers and operators for counting
		int maxPrior = 0;
		int maxPriorInd;
		for (auto iter = tmpPriors.begin(); iter != tmpPriors.end(); iter++)
		{
			int index = iter->first;
			int prior = iter->second;

			if (prior > maxPrior) maxPriorInd = index;
		}

		int prevInd = -1, curInd;
		double prevNum = NULL, curNum;
		for (auto iter = tmpNums.begin(); iter != tmpNums.end(); iter++)
		{
			int index = iter->first;
			double num = iter->second;

			if (index > maxPriorInd)
			{
				curInd = index;
				curNum = num;

				if (prevInd > -1) prevNum = tmpNums[prevInd];
				break;
			}

			prevInd = index;
		}

		//erasing used numbers and operators
		std::string chosenOper = tmpOpers[maxPriorInd];

		tmpPriors.erase(maxPriorInd);
		tmpOpers.erase(maxPriorInd);

		tmpNums.erase(curInd);
		if (prevInd) tmpNums.erase(prevInd);

		//counting
		double res;
		if (chosenOper == "+")
		{
			res = prevNum + curNum;
		}
		else if (chosenOper == "-")
		{
			if (prevNum == NULL) res = 0 - curNum;
			res = prevNum - curNum;
		}
		else if (chosenOper == "*")
		{
			res = prevNum * curNum;
		}
		else if (chosenOper == "/")
		{
			res = prevNum / curNum;
		}
		else if (chosenOper == "^")
		{
			res = pow(prevNum, curNum);
		}

		innerResult = tmpNums[curInd] = res;
	}

	numsBackup[assignInd] = innerResult;

	//std::cout << "\n" << innerResult;

	return innerResult;
}
//-------------------------