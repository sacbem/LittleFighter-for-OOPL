#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HealthBar.h"
#include <iostream>

namespace game_framework {
	HealthBar::HealthBar() {
		
	}

	HealthBar::~HealthBar() {

	}

	void HealthBar::GetHealth(int n) {
		life = n;
	}

	void HealthBar::OnLoad() {
		img.LoadBitmap("ahhhhhhh");
	}

}
