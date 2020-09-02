#ifndef MEOPCH_H
#define MEOPCH_H

// Windows Header Files
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
#include <windows.h>
#include <wrl.h>

// Cpp headers
#include <string>
#include <memory>
#include <iostream>

// D3D headers
#include <dxgi1_4.h>
#include <d3d12.h>

// helpers
#include "helpers.h"

#define ENABLE_DEBUG_LAYER

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif // MEOPCH_H
