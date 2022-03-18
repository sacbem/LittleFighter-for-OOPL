#include<iostream>
#include <stdio.h>
#include<windows.h>
#include "stdafx.h"
#include "Resource.h"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //¥²­n