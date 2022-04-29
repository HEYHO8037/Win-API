#pragma once
#include "Obj.h"
#include "Bullet.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}
	void	Set_ShieldList(list<CObj*>* pShield) { m_pShield = pShield; }

public:
	virtual void Initialize(void) override;
	virtual int		Update(void) override;
	virtual		void	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);

	CObj*		Create_Shield(void);

	template<typename T>
	CObj*		Create_Bullet(void);

	//�Ϲ� �߷� ����
	void NormalJump();
	void JumpPhysics();

	//������
	void ParabolaJump();
	void ParabolaPhysics();


private:
	LARGE_INTEGER timer, start, end;

	typedef list<CObj*>		BULLETLIST;
	BULLETLIST*				m_pBullet;

	list<CObj*>*			m_pShield;

	POINT					m_tPosin;
	float					m_fDiagonal;
	float					m_fDeltaTime;
	float					m_fForce;
	bool					m_bIsParabolaJump; // ������
	bool					m_bIsNormalJump; // �Ϲ� ����
};

// 1. �÷��̾� ���� ����(�÷��̾� �߽����� �����ϴ� ���� �����ϱ�)
// 2. ��ũ�� �̻��� ����
// 3. �÷��̾ ����ٴϴ� ���� ����(���Լ� ���)


// �Լ�		: ���, Input�� Output�� ����		Y = F(X)	-> y = x + 1
// �ﰢ �Լ�  : �����ڵ��� ã�� ����, �غ�, ���� ���̿� ���踦 �ǹ�, ���� ���� �˸� �� ���̿� �������� ���踦 ������ ���� �Լ�
