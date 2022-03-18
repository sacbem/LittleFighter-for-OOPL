#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "InitalPageMenu.h"

namespace game_framework {

    MenuBtn::MenuBtn() {

    }

    void MenuBtn::Initialize(int positionX, int positionY) {
        x = positionX;
        y = positionY;
    }
    void MenuBtn::OnShow() {
        Btn.SetTopLeft(x, y);
        Btn.ShowBitmap();
    }
    /////////////////////////////////////// StartBtn ///////////////////////////////////////
   
    StartBtn::StartBtn() {
        Initialize(410, 330);
    }
    void  StartBtn::LoadBitmap() {
        Btn.LoadBitmapA(IDB_BITMAP8);
        Btn.LoadBitmapA(IDB_BITMAP9);
    }
    void StartBtn::buttonTouch() {
        Btn.SetTopLeft(x, y);
        Btn.ShowBitmap(IDB_BITMAP8);
    }
    void  StartBtn::status() {

    }
    StartBtn::~StartBtn() {

    }
    /////////////////////////////////////// SettingBtn ///////////////////////////////////////
    SettingBtn::SettingBtn() {
        Initialize(510, 330);
    }
    void  SettingBtn::LoadBitmap() {
        Btn.LoadBitmapA(IDB_BITMAP6);
        Btn.LoadBitmapA(IDB_BITMAP7);
    }
    void SettingBtn::buttonTouch() {
        Btn.SetTopLeft(x, y);
        Btn.ShowBitmap(IDB_BITMAP6);
    }
    void  SettingBtn::status() {

    }

    SettingBtn::~SettingBtn() {

    }

}