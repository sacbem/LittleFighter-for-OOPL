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

    void MenuBtn::Initialize(vector<vector<int>> posXY) {
        posistion_XY.resize(posXY.end() - posXY.begin());
        int ind_x =0;
        for (auto i : posXY) {
            for (auto o : i) {
                posistion_XY[ind_x].push_back(o);
            }  
            ind_x++;
        }
    }

    /////////////////////////////////////// StartBtn ///////////////////////////////////////
   
    StartBtn::StartBtn() {
        Btn.push_back(btnNClick);
        Btn.push_back(btnClick);
        posistion_XY.resize(1);
        posistion_XY[0].push_back(520);
        posistion_XY[0].push_back(255);
        Initialize(posistion_XY);
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
        posistion_XY[0].push_back(520);
        posistion_XY[0].push_back(300);
        Initialize(posistion_XY);
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