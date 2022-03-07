#pragma once

#include <Windows.h>
#include <vector>
#include <list>
#include <unordered_map>

#include "Macro.h"
#include "resource.h"
#include "Types.h"
#include "Flag.h"

using namespace std;

template <typename T>
void Safe_Delete_VecList(T& p)
{
	T::literator iter;
	T::literator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd, ++iter)
	{
		SAFE_DELETE((*iter));
	}

	p.clear();
}