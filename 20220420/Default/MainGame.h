#pragma once

#include "Include.h"

#include "Bullet.h"
#include "Player.h"
#include "Monster.h"

class CMainGame
{
public:				// ������, �Ҹ���
	CMainGame();
	~CMainGame();

// public, protected, private �Լ�
public:
	void	Initialize(void);		// �ʱ�ȭ �Լ�
	void	Update(void);			// �� �����Ӹ��� ���ŵǴ� �����͸� ����� �Լ�
	void	Late_Update(void);		// Update�� Render���� �ʿ��� �۾��� �ϱ� ���� ���� �Լ�
	void	Render(void);			// �� �����Ӹ��� ����ϴ� �Լ�
	void	Release(void);			// �����Ҵ��� �����͸� �����ϴ� �Լ�

public:
	void ContactRect();
	void ContactMonster();
// public, protected, private ����
private:
	HDC		m_hDC;
	CObj*	m_pPlayer;
	CObj*	m_pMonster;
	list<CBullet*> m_pBulletList;


};

