#include "Input.h"

DEFINITION_SINGLE(CInput)

CInput::CInput() :
	m_pCreateKey(nullptr)
{
}


CInput::~CInput()
{
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('W', "MoveFront");
	AddKey('S', "MoveBack");
	AddKey("MoveLeft", 'A');
	AddKey("MoveRight", 'D');
	AddKey("Fire", VK_SPACE);
	AddKey(VK_CONTROL, "Skill1" , "1");


	return true;
}

void CInput::Update(float fDeltaTime)
{
}
