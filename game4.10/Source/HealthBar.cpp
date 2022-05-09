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

		imgHealth.reserve(180);
		imgInnerHealth.reserve(180);
		imgMana.reserve(180);
		imgInnerMana.reserve(180);
	}

	HealthBar::~HealthBar() {
		for (int i = 0; i < 180; i++) {
			delete imgHealth[i];
		}
		imgHealth.clear();

		for (int i = 0; i < 180; i++) {
			delete imgInnerHealth[i];
		}
		imgInnerHealth.clear();

		for (int i = 0; i < 180; i++) {
			delete imgMana[i];
		}
		imgMana.clear();

		for (int i = 0; i < 180; i++) {
			delete imgInnerMana[i];
		}
		imgInnerMana.clear();
	}

	void HealthBar::init() {
		for (int i = 0; i < 180; i++) {
			imgHealth.push_back(new CMovingBitmap());
		}
		for (int i = 0; i < 180; i++) {
			imgInnerHealth.push_back(new CMovingBitmap());
		}
		for (int i = 0; i < 180; i++) {
			imgMana.push_back(new CMovingBitmap());
		}
		for (int i = 0; i < 180; i++) {
			imgInnerMana.push_back(new CMovingBitmap());
		}
	}

	void HealthBar::OnShow(int hp, int InnerHp, int mana, int InnerMana) {
		img.SetTopLeft(posistion_XY[0], posistion_XY[1]);
		img.ShowBitmap();

		imgCharacter.SetTopLeft(posistion_XY[0] + 10, posistion_XY[1] + 10);
		imgCharacter.ShowBitmap();

		for (int i = 0; i < 180; i++) {
			if ((i + 1) <= InnerHp / 10) {
				imgInnerHealth[i]->ShowBitmap();
			}
		}

		for (int i = 0; i < 180; i++) {
			if ((i + 1) <= hp / 10) {
				imgHealth[i]->ShowBitmap();
			}
		}

		for (int i = 0; i < 180; i++) {
			if ((i + 1) <= InnerMana / 10) {
				imgInnerMana[i]->ShowBitmap();
			}
		}
		for (int i = 0; i < 180; i++) {
			if ((i + 1) <= mana / 10) {
				imgMana[i]->ShowBitmap();
			}
		}
	}

	void HealthBar::OnLoad(int X, int Y) {
		posistion_XY[0] = X;
		posistion_XY[1] = Y;
		img.LoadBitmap(".\\res\\Health\\HealthBar.bmp");
		//147, 44
		for (int i = 0; i < 180; i++) {
			imgInnerHealth[i]->LoadBitmap(".\\res\\Health\\InnerRedBar.bmp");
			imgInnerHealth[i]->SetTopLeft(posistion_XY[0] + 70 + i, 21);
			
			imgHealth[i]->LoadBitmap(".\\res\\Health\\RedBar.bmp");
			imgHealth[i]->SetTopLeft(posistion_XY[0] + 70 + i, 21);

			imgInnerMana[i]->LoadBitmap(".\\res\\Health\\InnerBlueBar.bmp");
			imgInnerMana[i]->SetTopLeft(posistion_XY[0] + 70 + i, 45);

			imgMana[i]->LoadBitmap(".\\res\\Health\\BlueBar.bmp");
			imgMana[i]->SetTopLeft(posistion_XY[0] + 70 + i, 45);
		}
	}

	void HealthBar::loadSmallImg(int id) {
		switch (id)
		{
		case 0:
			imgCharacter.LoadBitmap(FIRZEN_S, RGB(224, 68, 60));
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
