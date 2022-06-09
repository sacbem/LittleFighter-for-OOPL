#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <typeinfo>
#include "PhotoSticker.h"
namespace game_framework {
	PhotoSticker::PhotoSticker(int ind) {
		posistion_XY.resize(1); //Beta =>info.resize(1);->info.resize(2);
		photoSticker_XY.resize(2);
		info.resize(1);         //Beta =>info.resize(1);->info.resize(3);


		Initialize(ind);
	}
	void PhotoSticker::Initialize(int ind) {
		
		info.push_back(infoA);
		info.push_back(infoB);
		info.push_back(infoC);
		
		//Beta
		//for (int i = 0; i < 3; i++) {
		//    info.push_back(new CMovingBitmap);
		//}
			
		int cnt = 0;
		if (ind > 3) {    
			photoSticker_XY.push_back(155 + ind * 152);
			photoSticker_XY.push_back( 358);
		}
		else {
			photoSticker_XY.push_back(155 + ind * 152);
			photoSticker_XY.push_back(136);
		}

		for (auto &i : posistion_XY) {
			if (ind > 3) {
				i.push_back(154*(4-ind));
			}
			else {
				i.push_back(154 * ind);
			}
			i.push_back(240 + 20 * cnt);
			cnt++;
		}
	}
	void PhotoSticker::OnShow() {
		info[0].SetTopLeft(photoSticker_XY[0], photoSticker_XY[1]);
		//for (int i = 1; i < 3; i++) {
		//    info[i].SetTopLeft(posistion_XY[i][0], posistion_XY[i][1]);
		//}
		
		for (auto i : info) {
			i.ShowBitmap();
		}
	}
	void PhotoSticker::Load() {
	/*      int cnt = 0;
		for (auto &i : info) {
			i->LoadBitmap(data[cnt]);
			cnt++;
	   }*/
		info[0].LoadBitmap(188);
		
		TRACE("fuck-------------------");
	   
	}
	PhotoSticker::~PhotoSticker() {

	}
}