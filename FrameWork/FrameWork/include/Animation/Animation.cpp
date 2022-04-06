#include "Animation.h"
#include "../Resources/Texture.h"
#include "../Resources/ResourcesManager.h"


CAnimation::CAnimation()
{
}

CAnimation::CAnimation(const CAnimation & anim)
{
	*this = anim;

	m_mapClip.clear();

	unordered_map<string, PANIMATIONCLIP>::const_iterator iter;
	unordered_map<string, PANIMATIONCLIP>::const_iterator iterEnd = anim.m_mapClip.end();

	for (iter = anim.m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		PANIMATIONCLIP pClip = new ANIMATIONCLIP;

		*pClip = *iter->second;

		for (size_t i = 0; i < pClip->vecTexture.size(); ++i)
		{
			pClip->vecTexture[i]->AddRef();
		}
	}

}


CAnimation::~CAnimation()
{
	unordered_map<string, PANIMATIONCLIP>::iterator iter;
	unordered_map<string, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		for (size_t i = 0; i < iter->second->vecTexture.size(); ++i)
		{
			SAFE_RELEASE(iter->second->vecTexture[i]);
		}

		SAFE_DELETE(iter->second);
	}

	m_mapClip.clear();
}

bool CAnimation::AddClip(const string & strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, 
	float fAnimationTime, int iFrameMaxX, int iFrameMaxY, 
	int iStartX, int iStartY, int iLengthX, int iLengthY, 
	float fOptionLimitTime, const string & strTexKey, 
	const wchar_t * pFileName, const string & strPathKey)
{
	PANIMATIONCLIP pClip = new ANIMATIONCLIP;

	pClip->eType = eType;
	pClip->eOption = eOption;
	pClip->fAnimationTime = fAnimationTime;
	pClip->iFrameMaxX = iFrameMaxX;
	pClip->iFrameMaxY = iFrameMaxY;
	pClip->iStartX = iStartX;
	pClip->iStartY = iStartY;
	pClip->iLengthX = iLengthX;
	pClip->iLengthY = iLengthY;
	pClip->fOptionLimitTime = fOptionLimitTime;

	CTexture* pTex = GET_SINGLE(CResourcesManager)->LoadTexture(strTexKey, pFileName, strPathKey);
	pClip->vecTexture.push_back(pTex);

	pClip->fAnimationTime = 0.f;
	pClip->iFrameX = 0.f;
	pClip->iFrameY = 0.f;
	pClip->fOptionTime = 0.f;

	m_mapClip.insert(make_pair(strName, pClip));

	return true;

}

bool CAnimation::Init()
{
	return true;
}

void CAnimation::Update(float fTime)
{
}

CAnimation * CAnimation::Clone()
{
	return new CAnimation(*this);
}
