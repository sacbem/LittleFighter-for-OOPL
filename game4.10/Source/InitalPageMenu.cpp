#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "InitalPageMenu.h"
#include <iostream>
namespace game_framework {

    MenuBtn::MenuBtn() {

    }

    /////////////////////////////////////// StartBtn ///////////////////////////////////////
   
    StartBtn::StartBtn() {
        Btn.push_back(btnNClick);
        Btn.push_back(btnClick);
        posistion_XY.resize(1);
        posistion_XY[0].push_back(520*0.81 + 20);
        posistion_XY[0].push_back(255*0.94);
    }

    void  StartBtn::Load(){
        Btn[0].LoadBitmap(IDB_BITMAP8);
        Btn[1].LoadBitmap(IDB_BITMAP9);
    }
    void StartBtn::buttonTouch() {
        Btn[1].SetTopLeft(posistion_XY[0][0], posistion_XY[0][1]);
        Btn[1].ShowBitmap();
    }
    void StartBtn::OnShow() {
        Btn[0].SetTopLeft(posistion_XY[0][0], posistion_XY[0][1]);
        Btn[0].ShowBitmap();
     }
    StartBtn::~StartBtn() {

    }
    /////////////////////////////////////// SettingBtn ///////////////////////////////////////
    SettingBtn::SettingBtn() {
        Btn.push_back(btnNClick);
        Btn.push_back(btnClick);
        posistion_XY.resize(1);
        posistion_XY[0].push_back(520 * 0.81 + 20);
        posistion_XY[0].push_back(300 * 0.94);
    }
    void  SettingBtn::Load() {
        Btn[0].LoadBitmapA(IDB_BITMAP12);
        Btn[1].LoadBitmapA(IDB_BITMAP11);
    }
    void SettingBtn::OnShow() {
        Btn[0].SetTopLeft(posistion_XY[0][0], posistion_XY[0][1]);
        Btn[0].ShowBitmap();
    }
    void SettingBtn::buttonTouch() {
        Btn[1].SetTopLeft(posistion_XY[0][0], posistion_XY[0][1]);
        Btn[1].ShowBitmap();
    }

    SettingBtn::~SettingBtn() {

    }

}