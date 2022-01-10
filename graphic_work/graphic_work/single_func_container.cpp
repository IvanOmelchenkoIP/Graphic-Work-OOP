#include "framework.h"
#include <string>
#include <vector>
#include "single_func_container.h"

SingleFunctionContainer* SingleFunctionContainer::fcpInstance = nullptr;

SingleFunctionContainer* SingleFunctionContainer::GetInstance()
{
	if (!fcpInstance) fcpInstance = new SingleFunctionContainer();
	return fcpInstance;
}
