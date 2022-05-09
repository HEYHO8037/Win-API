#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
	ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	
}

int CLineMgr::Update(void)
{
	Key_Input();


	return 0;
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

void CLineMgr::Key_Input(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
		{
			m_tLinePoint[LEFT].fX = (float)pt.x;
			m_tLinePoint[LEFT].fY = (float)pt.y;
		}
		else
		{
			m_tLinePoint[RIGHT].fX = (float)pt.x;
			m_tLinePoint[RIGHT].fY = (float)pt.y;

			m_LineList.push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));

			m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
			m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Save_Line();
		return ;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		Load_Line();
		return ;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);
}

void CLineMgr::Save_Line(void)
{
	// 1. ���� ����

	// CreateFile : api ���� ���� �Լ�, ���� ���� �� INVALID_HANDLE_VALUE�ϱ� ������ null������ ����ó���� �� �� ����.

	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// ���� ��ο� �̸� ���
									GENERIC_WRITE,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
									NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
									NULL,						// ���� �Ӽ�, �⺻��	
									CREATE_ALWAYS,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
									FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
									NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		WriteFile(hFile, &iter->Get_Info(), sizeof(LINE), &dwByte, nullptr);
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), _T("����"), MB_OK);
}

void CLineMgr::Load_Line(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� �б�

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		m_LineList.push_back(new CLine(tInfo));
	}
	

	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("����"), MB_OK);
}

bool CLineMgr::Collision_Line(float& _fX, float* pY)
{
	// ������ ������

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
		return true;
}
