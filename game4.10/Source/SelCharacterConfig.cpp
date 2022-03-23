#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "SelCharacterConfig.h"
#include <iostream>
namespace game_framework {
    SelectCharacterMenu::SelectCharacterMenu() {
        *pic = new CMovingBitmap[8];
        posistion_XY.resize(8);

    }
    void SelectCharacterMenu::Initialize() {
        int x, y, pos, count = 0;
        for (auto &i : posistion_XY) {

            i.push_back(x + pos * count);
            i.push_back(y + pos * count);

            if (++count == 4) {
                //x=;
                //y=;
            }
        }
    }

    void SelectCharacterMenu::Load(vector<int> bitmap) {
        for (int i = 0; i < 8; i++) {
            pic[i] = new CMovingBitmap();
            pic[i]->LoadBitmap(bitmap[i]);
        }
    }
    SelectCharacterMenu::~SelectCharacterMenu() {
        delete[] pic;
    }
}