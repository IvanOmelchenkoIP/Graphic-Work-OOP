#pragma once

class SingleFunctionContainer
{
private:
	static SingleFunctionContainer* fcpInstance;

	SingleFunctionContainer() = default;
	SingleFunctionContainer(const SingleFunctionContainer&) = delete;
	SingleFunctionContainer& operator=(SingleFunctionContainer&) = delete;

public:
	~SingleFunctionContainer() = default;
	static SingleFunctionContainer* GetInstance();

	//function container
	std::vector<std::string> funcs;

	//vectors that define colors
	std::vector<int> reds;
	std::vector<int> greens;
	std::vector<int> blues;
};

