#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameObject.h"
namespace game_framework {
    GameObject::GameObject(const string type,int ind) {
        Initialize(type);
        index = ind;
    }
    void  GameObject::Initialize(const string type) {
        if (type == "Scenes") {
            IsScenes = true;
            IsWeapon = IsItem = false;
        }
        else if (type == "Weapon") {
            IsWeapon = true;
            IsScenes = IsItem = false;
        }
        else if (type == "Item") {
            IsItem = true;
            IsScenes = IsWeapon = false;
        }
    }
    void GameObject::Load(int bitmap) {
        img.LoadBitmap(bitmap);
    }
    void  GameObject::Load(int bitmap, int RGB) {
        img.LoadBitmap(bitmap, RGB);
    }
    void GameObject::SetTopLeft(int x, int y) { 
        //xPos = x>=1600 ? 1600 :x;  xPos = x <= -800 ? -800 : x;
        //yPos = x >= 600 ? 600 : y;
        xPos = x; 
        yPos = y;
        img.SetTopLeft(xPos, yPos);
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
    }
    int GameObject::GetPositionXY(const string type) {
        return type == "X" ? xPos : yPos;
    }
    void GameObject::OnShow() {
        img.ShowBitmap();
    }
    GameObject::~GameObject() {

    }
}