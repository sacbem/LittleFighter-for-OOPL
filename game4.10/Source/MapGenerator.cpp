#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <typeinfo>
#include "MapGenerator.h"
namespace game_framework {
    MapGenerator::MapGenerator(){

        weeds.reserve(4);
        trees.reserve(4);
        mountains.reserve(2);
        sky.reserve(2);
       
        backGreen = new CMovingBitmap();
        //landsPosXY.reserve(4);
        //wallPosXY.reserve(4);
    }
    void MapGenerator::Initialize(int) {
     
        for (int i = 0; i < 4; i++) {
            trees.push_back(new CMovingBitmap());
            weeds.push_back(new CMovingBitmap());
       }
        for (int i = 0; i < 2; i++) {
            mountains.push_back(new CMovingBitmap());
        }
        for (int i = 0; i < 3; i++) {
            sky.push_back(new CMovingBitmap());
        }

    }
    void MapGenerator::Load(int) {
        Initialize(0);
       
        backGreen->LoadBitmap(BITMAP_GREEN);
        for (auto &i : sky) {
            i->LoadBitmap(BITMAP_FOREST_M5);
        }
        for (int i = 0; i < 4;i++) {
            trees[i]->LoadBitmap(BITMAP_FOREST_T1, RGB(0, 0, 0));
            weeds[i]->LoadBitmap(BITMAP_FOREST_L1 + i);
        }
        mountains[0]->LoadBitmap(BITMAP_FOREST_Mex, RGB(0, 0, 0));
        mountains[1]->LoadBitmap(BITMAP_FOREST_M2, RGB(0, 0, 0));


        for (int i = 0; i < 4; i++) {
            trees[i]->SetTopLeft(250*i, 125);
            if (i < 2) {
                mountains[i]->SetTopLeft(500 * i, 75 - 5 * i);
            }
            if (i < 3) {
                sky[i]->SetTopLeft(skyPosXY[i], 50);
            }
        }

        weeds[0]->SetTopLeft(0, 280);
        weeds[1]->SetTopLeft(210, 370);
        weeds[2]->SetTopLeft(385, 250);
        weeds[3]->SetTopLeft(170, 365);

        backGreen->SetTopLeft(0, 280);
        
        
    }
    void  MapGenerator::SetLandPosition() {

        //4 :206*106
        //3 :232*95
        //2 :225*89
        //1 :175*74
        //t :253*162
        int cnt = 0;
        for (auto &i : weeds) {
            i->SetTopLeft(landsPosXY[cnt][0], landsPosXY[cnt][1]);
            cnt++;
        }

    }
    void MapGenerator::SetSkyPosition() {
        int cnt = 0;
        for (auto &i : sky) {
            i->SetTopLeft(skyPosXY[cnt], 50);
            cnt++;
        }

    }
    void MapGenerator::PrintMap() {
        backGreen->ShowBitmap();
       
        for (auto i : weeds) {
            i->ShowBitmap();
        }
        for (auto i : sky) {
            i->ShowBitmap();
        }
        for (auto i : mountains) {
            i->ShowBitmap();
        }

        for (auto i : trees) {
            i->ShowBitmap();
        }
    }
    void MapGenerator::ScenesCamera(boolean ISLEFT,int type) {
        if (type == 0) {    //  跑步時移動場景
            for (int x = 0; x < 4; x++) {
                if (ISLEFT) {
                    landsPosXY[x][0] -= 10;
                    if (x < 3) { 
                        skyPosXY[x] -= 5; 
                        if (skyPosXY[x] < -1600) {
                            skyPosXY[x] = 800;
                        }
                    }
                    if (landsPosXY[x][0] < 0) {
                        landsPosXY[x][0] = 750;
                    }
                }
                else {
                    landsPosXY[x][0] += 10;
                    if (x < 3) { 
                        skyPosXY[x] += 5; 
                        if (skyPosXY[x] > 1600) {
                            skyPosXY[x] = -800;
                        }
                    }
                    if (landsPosXY[x][0] >= 800) {
                        landsPosXY[x][0] = 0;
                    }
                }
            }
        }
        else if (type == 1) {       //  走路時 走一定距離移動場景
            for (int x = 0; x < 50; x++) {  
                for (int i = 0; i < 4; i++) {
                    if (ISLEFT) {
                        landsPosXY[i][0] -= 1;
                        if (i < 3) {
                            skyPosXY[i] -= 0.5;
                            if (skyPosXY[i] < -1600) {
                                skyPosXY[i] = 800;
                            }
                        }
                        if (landsPosXY[i][0] < 0) {
                            landsPosXY[i][0] = 750;
                        }
                    }
                    else {
                        landsPosXY[i][0] += 1;
                        if (i < 3) { 
                            skyPosXY[i] += 0.5; 
                            if (skyPosXY[i] > 1600) {
                                skyPosXY[i] = -800;
                            }
                        }
                        if (landsPosXY[i][0] >= 800) {
                            landsPosXY[i][0] = 0;
                        }
                    }
                }
            }
        }
        SetSkyPosition();
        SetLandPosition();
    }

	MapGenerator::~MapGenerator() {
		delete backGreen;

		for (size_t i = 0; i < mountains.size(); ++i)
		{
			delete mountains[i];
		}
		mountains.clear();
		for (size_t i = 0; i < trees.size(); ++i)
		{
			delete trees[i];
		}
		trees.clear();
		for (size_t i = 0; i < sky.size(); ++i)
		{
			delete sky[i];
		}
		sky.clear();
		for (size_t i = 0; i < weeds.size(); ++i)
		{
			delete weeds[i];
		}
		weeds.clear();
	}
}

/*

//lands[0].SetTopLeft(0, 300);//1
//lands[1].SetTopLeft(0, 370);//2
//lands[2].SetTopLeft(0, 450 - 3);//1

//lands[3].SetTopLeft(0 + 170, 300);//3
//lands[4].SetTopLeft(0 + 210, 300 + 90);//1
//lands[5].SetTopLeft(0 + 170, 390 + 65 - 23);//2

//lands[6].SetTopLeft(170 + 220, 300);//1
//lands[7].SetTopLeft(205 + 170, 300 + 74);//1
//lands[8].SetTopLeft(165 + 220, 373 + 74);//1

//lands[9].SetTopLeft(170 + 220 + 170, 300);//1
//lands[10].SetTopLeft(205 + 170 + 170, 300 + 74 );//1
//lands[11].SetTopLeft(165 + 220 + 170, 373 + 74 );//1
*/