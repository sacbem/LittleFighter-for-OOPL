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
        posistion_XY.resize(1);
        Initialize();
    }
    void SelectCharacterMenu::Initialize() {

        posistion_XY[0].push_back(((SIZE_X - 704) / 2));
        posistion_XY[0].push_back((SIZE_Y - 487) / 2);
        TRACE("posistion_XY: %d ,%d\n", posistion_XY[0][0], posistion_XY[0][1]);
    }
    void SelectCharacterMenu::Load(int bitmap) {
        pic.LoadBitmap(bitmap);
    }
    void SelectCharacterMenu::OnShow() {
        pic.SetTopLeft(posistion_XY[0][0], posistion_XY[0][1]);
        pic.ShowBitmap();
    }
    SelectCharacterMenu::~SelectCharacterMenu() {
        
    }

    ////////////////////////////////////////////// Seclecter (Derived) ////////////////////////////////////
    Seclecter::Seclecter(int ind) {
        posistion_XY.reserve(1);  //Beta =>info.resize(1);->info.resize(2);
        photoSticker_XY.reserve(2);
        Picture.reserve(3);         //Beta =>info.resize(1);->info.resize(3);
        seclectedID = 0;
        posID = ind;
        Picture.push_back(PicA); Picture.push_back(PicB); Picture.push_back(PicC);
        Id.push_back(idA); Id.push_back(idB); Id.push_back(idC);
        Name.push_back(nameA); Name.push_back(nameB); Name.push_back(nameC);
        Initialize(posID);
    }
    void Seclecter::Initialize(int ind) {
        int cnt = 0;
        if (ind > 3) {      // 頭貼位置初始化
            photoSticker_XY.push_back(155 + ind * 152);
            photoSticker_XY.push_back(358);
        }
        else {
            photoSticker_XY.push_back(155 + ind * 152);
            photoSticker_XY.push_back(136);
        }

        //for (auto &i : posistion_XY) {// 名字 與 ID 位置初始化
        //    if (ind > 3) {
        //        i.push_back(154 * (ind - 4));
        //    }
        //    else {
        //        i.push_back(154 * ind);
        //    }
        //    i.push_back(240 + 20 * cnt);
        //    cnt++;
        //}
    }
    void Seclecter::SetXY(int x ,int y) {
        this->photoSticker_XY[0] = x;
        this->photoSticker_XY[1] = y;
        for (auto &i : Picture) {
            i.SetTopLeft(x, y);
        }
        for (auto &i : Id) {
            i.SetTopLeft(x + 60, 241);
        }
        for (auto &i : Name) {
            i.SetTopLeft(x + 40, 261);
        }
    }
   
    void Seclecter::Load(vector<int> data, vector<int> picID, vector<int> picName) { //(int => vector<int>) /// 需處理 Picture[i] 大小與data的問題
         
         
        int cnt = 0;
        for (auto &i :Picture) {
            i.LoadBitmap(data[cnt]);
            i.SetTopLeft(photoSticker_XY[0], photoSticker_XY[1] - 20);
            cnt++;
        }
        cnt = 0;
        for (auto &i : Id) {
            i.LoadBitmap(picID[cnt]);     
            i.SetTopLeft(photoSticker_XY[0] + 60, 241);
            cnt++;
        }
        cnt = 0;
        for (auto &i : Name){
            i.LoadBitmap(picName[cnt]);
            i.SetTopLeft(photoSticker_XY[0] + 40, 261);
            cnt++;
        }
    }
    

    void Seclecter::IsSeclected(int characterIsSeclected) {
        seclectedID = characterIsSeclected;
    }
    void Seclecter::OnShow() {
       
        Picture[seclectedID].ShowBitmap();
        Name[seclectedID].ShowBitmap();
        Id[seclectedID].ShowBitmap();
    }
    int Seclecter::GetCharacterID() {
        return seclectedID;
    }
    Seclecter::~Seclecter(){
        TRACE("~Seclecter");
    }
    ////////////////////////////////////////////// PhotoSticker (Derived) //////////////////////////////////////////////
    PhotoSticker::PhotoSticker(int ind) {

        posistion_XY.reserve(1);  //Beta =>info.resize(1);->info.resize(2);
        photoSticker_XY.reserve(2);
        seclectedID = 0;
        posID = ind;
        Initialize(posID);
    }
    void PhotoSticker::Load(int bitmap, int picID, int picName) {
        pic.LoadBitmap(bitmap);
        id.LoadBitmap(picID);
        name.LoadBitmap(picName);

    }
    void PhotoSticker::Initialize(int ind) {
        /* Beta
        //for (int i = 0; i < 3; i++) {
        //    info.push_back(new CMovingBitmap);
        //}
        //int cnt = 0;
        */
        if (ind > 3) {      // 頭貼位置初始化
            photoSticker_XY.push_back(155 + posID * 152);
            photoSticker_XY.push_back(358);
        }
        else {
            photoSticker_XY.push_back(155 + posID * 152);
            photoSticker_XY.push_back(136);

        }
     /*  for (auto &i : posistion_XY) {// 名字 與 ID 位置初始化
     //    if (ind > 3) {
     //        i.push_back(154 * (ind - 4));
     //    }
     //    else {
     //        i.push_back(154 * ind);
     //    }
     //    i.push_back(240 + 20 * cnt);
     //    cnt++;
     //}*/
    }

    void PhotoSticker::OnShow() {
        pic.SetTopLeft(photoSticker_XY[0], photoSticker_XY[1]-20);// 頭貼位置設定
        id.SetTopLeft(photoSticker_XY[0] + 60,241);
        name.SetTopLeft(photoSticker_XY[0] + 40, 261);

        pic.ShowBitmap();
        id.ShowBitmap();
        name.ShowBitmap();
    }
    PhotoSticker::~PhotoSticker() {
        TRACE("~PhotoSticker");
    }

}

