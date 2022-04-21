#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_pMonster(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
		dynamic_cast<CPlayer*>(m_pPlayer)->SetBulletList(&m_pBulletList);
	}

	if (!m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}

}

void CMainGame::Update(void)
{
	m_pPlayer->Update();

	if (m_pMonster)
	{
		m_pMonster->Update();
	}

	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update();
	}
}

void CMainGame::Late_Update(void)
{
	ContactRect();
	ContactMonster();
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	m_pPlayer->Render(m_hDC);

	if (m_pMonster)
	{
		m_pMonster->Render(m_hDC);
	}

	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(m_hDC);
	}
}

void CMainGame::Release(void)
{
	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; ++iter)
	{
		delete (*iter);
		iter = m_pBulletList.erase(iter);
		iterEnd = m_pBulletList.end();
	}

	m_pBulletList.clear();

	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CObj*>(m_pMonster);

	ReleaseDC(g_hWnd, m_hDC);	
}

void CMainGame::ContactRect()
{
	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; iter)
	{
		if ((*iter)->GetRect().bottom >= WINCY - 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().top <= 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().left <= 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().right >= WINCX - 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else
		{
			++iter;
		}
	}
}

void CMainGame::ContactMonster()
{
	if (!m_pMonster)
	{
		return;
	}

	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();
	RECT rc{};

	for (iter = m_pBulletList.begin(); iter != iterEnd; iter)
	{
		if (IntersectRect(&rc, &dynamic_cast<CMonster*>(m_pMonster)->GetRect(), &(*iter)->GetRect()))
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			Safe_Delete<CObj*>(m_pMonster);
			break;
		}
		else
		{
			++iter;
		}
	}

}


// 1. w,a,s,d Ű�� ���� 4���� �Ѿ˽��
// 2. ���� ���ΰ� 100�� ���� ��Ʈ�� ����� �簢�� ������ ����� �̻����� �����϶�
// 3. ���͸� �����Ͽ� ���� �簢�� �ȿ��� ���� �ε����� �ݴ� �������� �����̵��� �����.(���ʴ� ���������� �̵�)
// 4. �Ѿ˿� �ε����� ���͸� ���Ÿ� �ϸ� �ȴ�.(IntersectRect �Լ��� ����϶�)
// InterSectRect 1. �ιڽ��� �浹�ϸ鼭 �߻��� ��Ʈ�� ������ ������ Rect�� �ּҰ�
// 2. ù��° �浹 RECT �ּҰ�
// 3. �ι�° �浹 RECT �ּҰ�

// 5. ��Ÿ��� ���� �ѹ� ����.

// 1. �ﰢ�Լ� �����ϱ�
// 2. �÷��̾� ���� �߰��ϰ� ȸ���� ���Ѷ�
// 3. ���Ź������� �÷��̾ �̵��ض�.(�ﰢ�Լ�)