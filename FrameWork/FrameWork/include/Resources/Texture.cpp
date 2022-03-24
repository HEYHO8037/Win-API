#include "Texture.h"
#include "../Core/PathManager.h"

CTexture::CTexture()
	: m_hMemDC(nullptr)
{
}


CTexture::~CTexture()
{
	//������ �����Ǿ��ִ� ������ �ٽ� �������ش�.
	SelectObject(m_hMemDC, m_hOldBitmap);

	//Bitmap�� �����ش�.
	DeleteObject(m_hBitmap);

	//DC�� �����ش�.
	DeleteDC(m_hMemDC);
}

void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_ColorKey = RGB(r, g, b);
}

void CTexture::SetColorKey(COLORREF colorKey)
{
	m_ColorKey = colorKey;
}

COLORREF CTexture::GetColorKey() const
{
	return m_ColorKey;
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC,
	const string & strKey, const wchar_t * pFileName,
	const string & strPathKey)
{
	//�޸� DC�� �����.
	m_hMemDC = CreateCompatibleDC(hDC);

	//��ü ��θ� ����� �ش�.
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
	{
		strPath = pPath;
	}

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//������ ������� ��Ʈ�� ������ DC�� �����Ѵ�.
	//�����ɶ� ��ȯ�Ǵ� ���� DC�� �⺻���� �����Ǿ��ִ� ������ ��ȯ�ȴ�.
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);


	return true;
}

HDC CTexture::GetDC() const
{
	return m_hMemDC;
}
