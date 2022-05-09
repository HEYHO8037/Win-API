#pragma once

#include "Line.h"

class CLineMgr
{
	enum DIRECTION { LEFT, RIGHT, END };

private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Key_Input(void);

	void		Save_Line(void);
	void		Load_Line(void);


	bool		Collision_Line(float& _fX, float* pY);

public:
	static		CLineMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_LineList;
	LINEPOINT				m_tLinePoint[END];
};

// (���� ���� ����)�� �̿��Ͽ� ������ �����϶�
// Y = �� * sin(����) * �ð� - 1/2(�߷°��(9.8) * �ð� * �ð�)