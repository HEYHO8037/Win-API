#pragma once

#include "Include.h"

#include "Bullet.h"
#include "Player.h"

class CMainGame
{
public:				// ������, �Ҹ���
	CMainGame();
	~CMainGame();

// public, protected, private �Լ�
public:
	void	Initialize(void);		// �ʱ�ȭ �Լ�
	void	Update(void);			// �� �����Ӹ��� ���ŵǴ� �����͸� ����� �Լ�
	void	Render(void);			// �� �����Ӹ��� ����ϴ� �Լ�
	void	Release(void);			// �����Ҵ��� �����͸� �����ϴ� �Լ�

public:
	void ContactRect();
// public, protected, private ����
private:
	HDC		m_hDC;
	CObj*	m_pPlayer;
	list<CBullet*> m_pBulletList;


};

