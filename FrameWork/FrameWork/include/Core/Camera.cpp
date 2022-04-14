#include "Camera.h"
#include "../Object/Obj.h"

DEFINITION_SINGLE(CCamera)

CCamera::CCamera()
	: m_pTarget(nullptr)
{
}


CCamera::~CCamera()
{
	SAFE_RELEASE(m_pTarget);
}

void CCamera::SetTarget(CObj * pObj)
{
	SAFE_RELEASE(m_pTarget);
	m_pTarget = pObj;

	if (m_pTarget)
	{
		m_pTarget->AddRef();
	}

}

void CCamera::SetPivot(const POSITION & tPivot)
{
	m_tPivot = tPivot;
}

void CCamera::SetPivot(float x, float y)
{
	m_tPivot = POSITION(x, y);
}

void CCamera::SetPos(const POSITION & tPos)
{
	m_tPos = tPos;
}

void CCamera::SetPos(float x, float y)
{
	m_tPos = POSITION(x, y);
}

void CCamera::SetClientResolution(const RESOLUTION & tRS)
{
	m_tClientRS = tRS;
}

void CCamera::SetClientResolution(float x, float y)
{
	m_tClientRS = RESOLUTION(x, y);
}

void CCamera::SetWorldResolution(const RESOLUTION & tRS)
{
	m_tWorldRS = tRS;
}

void CCamera::SetWorldResolution(float x, float y)
{
	m_tWorldRS = RESOLUTION(x, y);
}

POSITION CCamera::GetPos() const
{
	return m_tPos;
}

RESOLUTION CCamera::GetClientRS() const
{
	return m_tClientRS;
}

bool CCamera::Init(const POSITION& tPos, const RESOLUTION& tClientRS, const RESOLUTION& tWorldRS)
{
	m_tPos = tPos;
	m_tClientRS = tClientRS;
	m_tWorldRS = tWorldRS;
	m_tPivot = POSITION(0.5f, 0.5f);

	return true;
}

void CCamera::Input(float fDeltaTime)
{
	if (!m_pTarget)
	{

	}
}

void CCamera::Update(float fDeltaTime)
{
	if (m_pTarget)
	{
		POSITION tPos = m_pTarget->GetPosition();
		POSITION tPivot = m_pTarget->GetPivot();
		_SIZE tSize = m_pTarget->GetSize();

		float fL = tPos.x - tPivot.x * tSize.x;
		float fT = tPos.y - tPivot.y * tSize.y;
		float fR = fL + tSize.x;
		float fB = fT + tSize.y;

		float fLeftArea = m_tClientRS.iW * m_tPivot.x;
		float fRightArea = m_tClientRS.iW - fLeftArea;
		float fTopArea = m_tClientRS.iH * m_tPivot.y;
		float fBottomArea = m_tClientRS.iH - fTopArea;

		if (tPos.x <= fLeftArea)
		{
			m_tPos.x = 0.f;
		}
		else if (tPos.x >= m_tWorldRS.iW - fRightArea)
		{
			m_tPos.x = m_tWorldRS.iW - m_tClientRS.iW;
		}
		else
		{
			m_tPos.x = tPos.x - m_tClientRS.iW * m_tPivot.x;
		}

		if (tPos.y <= fTopArea)
		{
			m_tPos.y = 0.f;
		}
		else if (tPos.y >= m_tWorldRS.iH - fBottomArea)
		{
			m_tPos.y = m_tWorldRS.iH - m_tClientRS.iH;
		}
		else
		{
			m_tPos.y = tPos.y - m_tClientRS.iH * m_tPivot.y;
		}

	}
}
