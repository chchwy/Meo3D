// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <cstdlib>
#include <memory>
#include <cassert>
#include <cstdint>
#include <cstring>

// D3D headers
#include <dxgi.h>
#include <d3d11.h>

// Common headers
#include "Util.h"
#include "MeoMath.h"