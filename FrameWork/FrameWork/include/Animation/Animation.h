#pragma once
#include "../Ref.h"

class CAnimation :
	public CRef
{
private:
	friend class CObj;

private:
	CAnimation();
	CAnimation(const CAnimation& anim);
	~CAnimation();

private:
	unordered_map<string, PANIMATIONCLIP> m_mapClip;
	
public:
	bool Init();
	void Update(float fTime);
	CAnimation* Clone();

};

