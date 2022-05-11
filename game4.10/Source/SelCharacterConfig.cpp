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

        posistion_XY[0].push_back(((SIZE_X - 776) / 2));
        posistion_XY[0].push_back((SIZE_Y - 536) / 2);
    }
    void SelectCharacterMenu::Load(int bitmap) {
        pic.LoadBitmap(bitmap);
    }
    void SelectCharacterMenu::OnShow() {
        pic.SetTopLeft(posistion_XY[0][0], posistion_XY[0][1]);
        pic.ShowBitmap();
    }
    void SelectCharacterMenu::SetSeclectedID(int id) {
        seclectedID = id;
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
        // 頭貼位置初始化
        photoSticker_XY.push_back(167 + ind * 169);
        photoSticker_XY.push_back(195);
        
    }
    void Seclecter::SetXY(int x ,int y) {
        this->photoSticker_XY[0] = x;
        this->photoSticker_XY[1] = y;
        for (auto &i : Picture) {
            i.SetTopLeft(x, y);
        }
        for (auto &i : Id) {
            i.SetTopLeft(x + 60, 291 + 40);
        }
        for (auto &i : Name) {
            i.SetTopLeft(x + 40, 315 + 40);
        }
    }
   
    void Seclecter::Load(vector<int> data, vector<int> picID, vector<int> picName) { //(int => vector<int>) /// 需處理 Picture[i] 大小與data的問題
         
         
        int cnt = 0;
        for (auto &i :Picture) {
            i.LoadBitmap(data[cnt]);
            i.SetTopLeft(photoSticker_XY[0], photoSticker_XY[1]);
            cnt++;
        }
        cnt = 0;
        for (auto &i : Id) {
            i.LoadBitmap(picID[cnt]);     
            i.SetTopLeft(photoSticker_XY[0] + 60, 291 + 40);
            cnt++;
        }
        cnt = 0;
        for (auto &i : Name){
            i.LoadBitmap(picName[cnt]);
            i.SetTopLeft(photoSticker_XY[0] + 40, 315 + 40);
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
         // 頭貼位置初始化
        photoSticker_XY.push_back(167 + posID * 169);
        photoSticker_XY.push_back(195);

    }

    void PhotoSticker::OnShow() {
        pic.SetTopLeft(photoSticker_XY[0], photoSticker_XY[1]);// 頭貼位置設定
        id.SetTopLeft(photoSticker_XY[0] + 60 ,291 + 40);
        name.SetTopLeft(photoSticker_XY[0] + 40, 315 + 40);

        pic.ShowBitmap();
        id.ShowBitmap();
        name.ShowBitmap();
    }
    PhotoSticker::~PhotoSticker() {
        TRACE("~PhotoSticker");
    }

}

