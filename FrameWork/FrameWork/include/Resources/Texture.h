#pragma once
#include "../Ref.h"

class CTexture :
	public CRef
{
private:
	friend class CResourcesManager;
public:
	CTexture();
	~CTexture();
};

