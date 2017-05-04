#pragma once

#include "resource.h"

class MeoRenderer
{
public:
	MeoRenderer();
	~MeoRenderer();

	void Initialize(HWND hWnd);
	void Shutdown();

	void Frame();

private:
	HWND m_hWnd = 0;
};