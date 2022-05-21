#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameObject.h"
namespace game_framework {
    GameObject::GameObject(const string type) {
        Initialize(type);
        anotherDestructorEnable = false;
    }
    
    GameObject::GameObject(int num,const string type) {
        imgs.resize(num);
        Pos_imgs.resize(num);
        Initialize(type);
        anotherDestructorEnable = true;
    }
    void  GameObject::Initialize(const string type) {
        if (type == "Scenes") {
            IsScenes = true;
            IsWeapon = IsItem = IsEffect = false;
        }
        else if (type == "Weapon") {
            IsWeapon = true;
            IsScenes = IsItem = IsEffect = false;
        }
        else if (type == "Item") {
            IsItem = true;
            IsScenes = IsWeapon = IsEffect = false;
        }
        else if (type == "Effect") {
            IsEffect = true;
            IsScenes = IsWeapon = IsItem = false;
        }
    }
    
    void  GameObject::Load(char* path, COLORREF color) {
        img.LoadBitmap(path, color);
    }
    
    void  GameObject::Load(int bitmap, COLORREF color) {
        img.LoadBitmap(bitmap, color);
    }
    
    void  GameObject::Load(int imgID,char* path, COLORREF color) {
        //TRACE("imgID %d\n", imgID);
        imgs[imgID].push_back(new CMovingBitmap());
        //TRACE("size %d\n", imgs[imgID].size());
        Pos_imgs[imgID].push_back(pair<int, int>(0, 0));
        imgs[imgID][imgs[imgID].size()-1]->LoadBitmap(path, color);
    }
   
    void  GameObject::Load(int imgID,int bitmap, COLORREF color) {
        imgs[imgID].push_back(new CMovingBitmap());
        Pos_imgs[imgID].push_back(pair<int, int>(0, 0));
        imgs[imgID][imgs[imgID].size() - 1]->LoadBitmap(bitmap, color);
    }

    void GameObject::SetTopLeft(int x, int y) { 
        xPos = x>=1600 ? 1600 :x; 
        xPos = x <= -800 ? -800 : x;
        yPos = y;
        img.SetTopLeft(xPos, yPos);
    }
    
    void GameObject::SetTopLeftSpical(int x, int y) {
        xPos = x >= 1600 ? 1600 : x;
        xPos = x <= -1600 ? -1600 : x;
        yPos = y;
        img.SetTopLeft(xPos, yPos);
    }
    
    void GameObject::SetTopLeft(int id_x, int id_y,int x, int y) {
        //xPos = x >= 500 ? 500 : x;
        //xPos = x <= 0 ? 0 : x;

        Pos_imgs[id_x][id_y].first = x;
        Pos_imgs[id_x][id_y].second = y;
        imgs[id_x][id_y]->SetTopLeft(x, y);
    }
   
    string GameObject::GetClassification() {
        if (IsWeapon) {
            return "Weapon";
        }
        if (IsItem) {
            return "Item";
        }
        if (IsScenes) {
            return "Scenes";
        }
        if (IsEffect) {
            return "Effect";
        }
        return "Type did not be set.";
    }
    int GameObject::GetPositionXY(const string type) {
        return type == "X" ? xPos : yPos;
    }
    int GameObject::GetPositionXY(int id_x, int id_y, const string type) {
        return type == "X" ? Pos_imgs[id_x][id_y].first : Pos_imgs[id_x][id_y].second;
    }
    void GameObject::OnShow() {
        img.ShowBitmap();
    }
    void GameObject::OnShow(int id_x, int id_y) {
        imgs[id_x][id_y]->ShowBitmap();
    }
    GameObject::~GameObject() {
        if (anotherDestructorEnable) {
            for (auto& i : imgs) {
                for (auto x : i) {
                    delete x;
                }
            }
        }
    }
}