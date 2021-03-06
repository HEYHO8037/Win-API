#pragma once

#include "Obj.h"

class CMoveObj : public CObj
{
private:
	friend class CObj;
	friend class CScene;

protected:
	CMoveObj();
	CMoveObj(const CMoveObj& obj);
	virtual ~CMoveObj();
	
protected:
	float m_fAngle;
	float m_fSpeed;
	bool m_bMove;
	bool m_bFalling;
	float m_fForce;
	float m_fForceOrigin;

public:
	void SetForce(float fForce);
	void SetAngle(float fAngle);
	void SetSpeed(float fSpeed);
	float GetAngle() const;
	float GetSpeed() const;


public:
	void Move(float x, float y);
	void Move(float x, float y, float fDeltaTime);
	void Move(const POSITION& tMove);
	void Move(const POSITION& tMove, float fDeltaTime);

	void MoveX(float x);
	void MoveX(float x, float fDeltaTime);
	void MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir);

	void MoveY(float y);
	void MoveY(float y, float fDeltaTime);
	void MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir);

	void MoveAngle();
	void MoveAngle(float fTime);

	void Jump();
	void JumpEnd();

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMoveObj* Clone() = 0;
};

