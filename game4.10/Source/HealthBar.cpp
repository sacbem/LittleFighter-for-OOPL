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
		posistion_XY.push_back(0);
		posistion_XY.push_back(0);

		imgHealth.reserve(36);

	}

	HealthBar::~HealthBar() {
		for (int i = 0; i < 36; i++) {
			delete imgHealth[i];
		}
		imgHealth.clear();
	}

	void HealthBar::init() {
		for (int i = 0; i < 36; i++) {
			imgHealth.push_back(new CMovingBitmap());
		}
	}

	void HealthBar::OnShow(int hp) {
		img.SetTopLeft(posistion_XY[0], posistion_XY[1]);
		img.ShowBitmap();

		imgCharacter.SetTopLeft(posistion_XY[0]+40, posistion_XY[1]+10);
		imgCharacter.ShowBitmap();

		for (int i = 0; i < 36; i++) {
			if ((i + 1) <= hp / 10){
				imgHealth[i]->ShowBitmap();
			}
		}

		/*
		for (auto i : imgHealth) {
			i->ShowBitmap();
		}
		*/
	}

	void HealthBar::OnLoad(int X,int Y) {
		posistion_XY[0] = X;
		posistion_XY[1] = Y;
		img.LoadBitmap(BITMAP_HEALTHBAR2);
		//147, 44
		for (int i = 0; i < 36; i++) {
			imgHealth[i]->LoadBitmap(RED);
			imgHealth[i]->SetTopLeft(posistion_XY[0] +177+(i*5), 21);
		}
	}

	void HealthBar::loadSmallImg(int id) {
		switch (id)
		{
		case 0:
			imgCharacter.LoadBitmap(FIRZEN_S,RGB(224,68,60));
			break;
		case 1:
			imgCharacter.LoadBitmap(FREEZE_S, RGB(224, 68, 60));
			break;
		case 2:
			imgCharacter.LoadBitmap(HENRY_S, RGB(224, 68, 60));
			break;
		default:
			imgCharacter.LoadBitmap(PLAYER0_S, RGB(224, 68, 60));
			break;
		}
	}

}
