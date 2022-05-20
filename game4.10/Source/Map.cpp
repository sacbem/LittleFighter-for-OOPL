#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <utility>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
using namespace mapConfiguration;
namespace game_framework {
	Map::Map(int mapID) {
		for (int i = 0; i < 4; i++) {
			mapBordary.push_back(true);
		}
		for (int i = 0; i < 4; i++) {
			characterInBorder.push_back(false);
		}
		map.reserve(30);
		InitializeAllObjs(mapID);
		mapId = mapID;

		cameraEnable = mapId == HKC ? false : true;
	
	}
	void Map::InitializeAllObjs(int mapID) {
		
		rubberMode = 0;
		gameScencePos.first = 0;
		gameScencePos.second = 794;
		
		for (auto& i : map) {
			for (int o = 0; o < 10; o++) {
				i.push_back(0);
			}
		}
		switch (mapID) {
		case Forest:

			for (int floorNum = 0; floorNum < 3; floorNum++) {
				floors.push_back(new GameObject("Scenes"));
			}
			for (int weedNum = 0; weedNum < 3; weedNum++) {
				floorObjs.push_back(new GameObject("Scenes"));
			}
			for (int treeNum = 0; treeNum < 10; treeNum++) {
				backgroundFrontObjs.push_back(new GameObject("Scenes"));
			}
			for (int mountainNum = 0; mountainNum < 1; mountainNum++) {
				backgroundBackObjs.push_back(new GameObject("Scenes"));
			}
			for (int skyNum = 0; skyNum < 3; skyNum++) {
				backgroundSkyObjs.push_back(new GameObject("Scenes"));
			}
			break;
		case HKC:
			for (int backgroundBackNum = 0; backgroundBackNum < 2; backgroundBackNum++) {
				backgroundBackObjs.push_back(new GameObject("Scenes"));
			}
			for (int floorNum = 0; floorNum < 1; floorNum++) {
				floors.push_back(new GameObject("Scenes"));
			}
			for (int skyNum = 0; skyNum < 1; skyNum++) {
				backgroundSkyObjs.push_back(new GameObject("Scenes"));
			}
			break;
		case BC:
			for (int backgroundBackNum = 0; backgroundBackNum < 3; backgroundBackNum++) {
				backgroundBackObjs.push_back(new GameObject("Scenes"));
			}
			for (int backgroundFrontNum = 0; backgroundFrontNum < 4; backgroundFrontNum++) {
				backgroundFrontObjs.push_back(new GameObject("Scenes"));
			}
			for (int floorNum = 0; floorNum < 3; floorNum++) {
				floors.push_back(new GameObject("Scenes"));
			}
			break;
		default:
			break;
			}
		}
	
	void Map::Load() {
		int cnt = 0;
		switch (mapId) {
		case Forest:
			for (int i = 0; i < floorObjs.size() - 1;i++) {
				floorObjs[i]->Load(BITMAP_FOREST_L1 + i);
			}
			floorObjs[2]->Load(BITMAP_FOREST_L4);

			for (auto& tree : backgroundFrontObjs) {
				tree->Load(BITMAP_FOREST_T1, RGB(0, 0, 0));
			}
			for (auto& floor : floors) {
				floor->Load(BITMAP_GREEN);    
			}
			for (auto& sky : backgroundSkyObjs) {
				sky->Load(BITMAP_FOREST_M5, RGB(0, 0, 0));
			}
			backgroundBackObjs[0]->Load(BITMAP_BACKSCENE_FOREST, RGB(0, 0, 0));
		   
			break;
		case HKC:
			floors[0]->Load(".\\res\\hkc\\gray.bmp");
			backgroundBackObjs[0]->Load(".\\res\\hkc\\hkc_back1.bmp");
			backgroundBackObjs[1]->Load(".\\res\\hkc\\hkc_back2.bmp");
			backgroundSkyObjs[0]->Load(".\\res\\hkc\\hkc_sky.bmp");

			break;
		case BC:
			backgroundBackObjs[0]->Load(".\\res\\bc\\bc1.bmp");
			backgroundBackObjs[1]->Load(".\\res\\bc\\bc2.bmp");
			backgroundBackObjs[2]->Load(".\\res\\bc\\bc3.bmp");
			backgroundFrontObjs[0]->Load(".\\res\\bc\\bc4.bmp", RGB(0, 0, 0));
			backgroundFrontObjs[1]->Load(".\\res\\bc\\bc4.bmp", RGB(0, 0, 0));
			backgroundFrontObjs[2]->Load(".\\res\\bc\\bc4.bmp", RGB(0, 0, 0));
			backgroundFrontObjs[3]->Load(".\\res\\bc\\bc4.bmp", RGB(0, 0, 0));
			floors[0]->Load(".\\res\\bc\\bg5_x3.bmp", RGB(0, 0, 0));
			floors[1]->Load(".\\res\\bc\\bg5_x3.bmp", RGB(0, 0, 0));
			floors[2]->Load(".\\res\\bc\\bg5_x3.bmp", RGB(0, 0, 0));

			break;
		default:
			break;
		}
		InitializeMap();
	}
	void Map::GenerateLand() {
		switch (mapId){
		case Forest:
			floorObjs[0]->SetTopLeft(0, 356);
			floorObjs[1]->SetTopLeft(300, 385);
			floorObjs[2]->SetTopLeft(600, 420);
			break;	
		case HKC:
			floors[0]->SetTopLeft(0, 336);
			break;
		case BC:
			floors[0]->SetTopLeft(-2500, 296);
			floors[1]->SetTopLeft(-600, 296);
			floors[2]->SetTopLeft(1150, 296);
			break;
		default:
			break;
		}
	}
	void Map::InitializeMap() {
		int cnt = 0;
		GenerateLand();
		switch (mapId) {
			case Forest:
				for (auto& tree : backgroundFrontObjs) {
					tree->SetTopLeft(-800 + 250 * cnt, 165);
					cnt++;
				}
				cnt = 0;
				for (auto& floor : floors) {
					floor->SetTopLeft(-1600 + 800 * cnt, 280);
					cnt++;
				}
				cnt = 0;
				for (auto& sky : backgroundSkyObjs) {
					sky->SetTopLeft(-800 + 800 * cnt, 80);
					cnt++;
				}
				backgroundBackObjs[0]->SetTopLeft(-800, 90);
				break;
			case HKC:
				backgroundBackObjs[0]->SetTopLeft(3,250);
				backgroundBackObjs[1]->SetTopLeft(3,250);
				backgroundSkyObjs[0]->SetTopLeft(3,100);
				break;

			case BC:
				for (int i = 0; i < backgroundBackObjs.size(); i++) {
					backgroundBackObjs[i]->SetTopLeft(460 * i, 129);
				}
				for (int i = 0; i < backgroundFrontObjs.size(); i++) {
					backgroundFrontObjs[i]->SetTopLeft(-798 + 800 * i, 261);
				}

			break;
			default:
			break;
		}

	}
	void Map::StopDynamic(boolean isLeft, int distance) {

		if (cameraEnable) {
			int SkyBordary;
			if (mapId == Forest) {
				SkyBordary = 0;
			}
			else if (mapId = BC) {
				SkyBordary = 0;
			}
			if (!backgroundSkyObjs.empty()) {
				if (backgroundSkyObjs[0]->GetPositionXY("X") == 0 || backgroundSkyObjs[backgroundSkyObjs.size() - 1]->GetPositionXY("X") == 0) {
					if (mapId == Forest) {
						mapBordary[1] = false;
						mapBordary[3] = false;
					}
					mapBordary[0] = false;
					
					if (distance != 0) {
						if (backgroundSkyObjs[0]->GetPositionXY("X") == 0 && !isLeft) {
							mapBordary[0] = true;
							if (mapId == Forest) {
								mapBordary[1] = true;
								mapBordary[3] = true;
							}
						}
						else if (backgroundSkyObjs[backgroundSkyObjs.size() - 1]->GetPositionXY("X") == 0 && isLeft) {
							mapBordary[0] = true;
							if (mapId == Forest) {
								mapBordary[1] = true;
								mapBordary[3] = true;
							}
						}
					}
				}
			}
			if (!backgroundFrontObjs.empty()) {
				int FrontBordary;
				if (mapId == Forest) {
					FrontBordary = 547;
				}
				else if (mapId = BC) {
					FrontBordary = 0;
				}
				if ((backgroundFrontObjs[0]->GetPositionXY("X") == 0 || backgroundFrontObjs[backgroundFrontObjs.size() - 1]->GetPositionXY("X") == FrontBordary)) {
					mapBordary[1] = false;
					if (distance != 0) {
						if (backgroundFrontObjs[0]->GetPositionXY("X") == 0 && !isLeft) {
							mapBordary[1] = true;
						}
						else if (backgroundFrontObjs[backgroundFrontObjs.size() - 1]->GetPositionXY("X") == FrontBordary && isLeft) {
							mapBordary[1] = true;
						}
					}
				}
			}
			
			if (!backgroundBackObjs.empty()) {
				int BackBordary;
				if (mapId == Forest) {
					BackBordary = -1600;
				}
				else if (mapId = BC) {
					BackBordary = 586;
				}
				
				if (backgroundBackObjs[0]->GetPositionXY("X") == 0 || backgroundBackObjs[backgroundBackObjs.size() - 1]->GetPositionXY("X") == BackBordary) {
					mapBordary[3] = false;
					if (mapId == BC) {
						mapBordary[0] = false;
						mapBordary[1] = false;
						mapBordary[2] = false;
					}
					if (backgroundBackObjs[0]->GetPositionXY("X") == 0 && !isLeft) {
						mapBordary[3] = true;
						if (mapId == BC) {
							mapBordary[0] = true;
							mapBordary[1] = true;
							mapBordary[2] = true;
						}
					}
					else if (backgroundBackObjs[backgroundBackObjs.size() - 1]->GetPositionXY("X") == BackBordary && isLeft) {
						mapBordary[3] = true;
						if (mapId == BC) {
							mapBordary[0] = true;
							mapBordary[1] = true;
							mapBordary[2] = true;
						}
					}
				}
			}
		}
	}
		
	
	boolean Map::ResetCharactAccumulator(int distance1, int distance2) {
		if (distance1 > forestSky_dx || distance2 > forestSky_dx) {
			return true;
		}
		else {
			return false;
		}
	}
	
	//void Map::DynamicScence(boolean IsLeft,int walkedDistance) {
	//	StopDynamic(IsLeft, walkedDistance);
	//	int direction = IsLeft ? 1 : -1; // ���k : 1 ���� : -1 
	//	if (cameraEnable) {
	//		if (mapBordary[0]) {
	//			if (walkedDistance > forestSky_dx) {
	//				for (auto& i : backgroundSkyObjs) {
	//					i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
	//				}
	//			}
	//		}
	//		if (mapBordary[1]) {
	//			switch (mapId) {
	//			case Forest:
	//				if (walkedDistance > forestTree_dx) {
	//					for (auto& i : backgroundFrontObjs) {
	//						i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
	//					}
	//				}
	//				break;
	//			case BC:
	//				if (walkedDistance > bcBackScence_dx) {
	//					for (auto& i : backgroundFrontObjs) {
	//						i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
	//					}
	//				}
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//		if (mapBordary[2]) {
	//			switch (mapId){
	//			case Forest:
	//				if (walkedDistance > forestTree_dx) {
	//					for (auto& i : floorObjs) {
	//						i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
	//					}
	//				}
	//				break;
	//			case BC:
	//				if (walkedDistance > bcLand_dx) {
	//					if (walkedDistance > bcLand_dx) {
	//						floorObjs[0]->SetTopLeft(floorObjs[0]->GetPositionXY("X") + 1 * direction, floorObjs[0]->GetPositionXY("Y"));
	//					}
	//				}
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//		if (mapBordary[3]) {
	//			switch (mapId){
	//			case Forest:
	//				if (walkedDistance > forestMountain_dx2) {
	//						backgroundBackObjs[0]->SetTopLeftSpical(backgroundBackObjs[0]->GetPositionXY("X") + 1 * direction, backgroundBackObjs[0]->GetPositionXY("Y"));
	//				}
	//			break;
	//			case  BC:
	//				if (walkedDistance > forestMountain_dx2) {
	//					for (int i = 0; i < 3; i++) {
	//						backgroundBackObjs[0]->SetTopLeftSpical(backgroundBackObjs[0]->GetPositionXY("X") + 1 * direction, backgroundBackObjs[0]->GetPositionXY("Y"));
	//					}
	//				}
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//}

	void Map::ScenesCamera(boolean mapMove, boolean IsRunning, boolean IsLeft, int walkedDistance) {
		int direction = IsLeft  ?  1 : -1; 
		
		//if (mapMove && cameraEnable) {
			StopDynamic(IsLeft, walkedDistance);
			if (mapBordary[0]) {
				if (mapId == Forest) {
					if (walkedDistance > forestSky_dx) {
						for (auto& i : backgroundSkyObjs) {
							i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
						}
					}
				}
			}
			if (mapBordary[1]) {
				if (mapId == Forest) {
					if (walkedDistance > forestMountain_dx2) {
						for (auto& i : backgroundFrontObjs) {
							i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
						}
					}
				}
				else if (mapId == BC) {
					if (walkedDistance > bcFrontScence_dx) {
						for (auto& i : backgroundFrontObjs) {
							i->SetTopLeftSpical(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"), mapId);
						}
					}
				}
			}
			if (mapBordary[2]) {
				if (mapId == Forest) {
					if (walkedDistance > 2) {
						for (auto& i : floorObjs) {
							i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
						}
					}
				}
				else if (mapId == BC) {
					if (walkedDistance > bcLand_dx) {
						for (auto& i : floors) {
							i->SetTopLeftSpical(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"), mapId);
						}
					}
				}
			}
			if (mapBordary[3]) {
				if (mapId == Forest) {
					if (walkedDistance > forestMountain_dx2) {
						backgroundBackObjs[0]->SetTopLeftSpical(backgroundBackObjs[0]->GetPositionXY("X") + 1 * direction, backgroundBackObjs[0]->GetPositionXY("Y"), mapId);
					}
				}
				else if (mapId == BC) {
					if (walkedDistance > forestMountain_dx2) {
						for (int i = 0; i < 3; i++) {
							backgroundBackObjs[i]->SetTopLeftSpical(backgroundBackObjs[i]->GetPositionXY("X") + 1 * direction, backgroundBackObjs[i]->GetPositionXY("Y"),mapId);
						}
					}
				}
			}
		//}
	}

	void Map::PrintMap(boolean showStates) {

		if (!backgroundSkyObjs.empty()) {
			for (auto& i : backgroundSkyObjs) {
				i->OnShow();
			}
		}
		if (!backgroundBackObjs.empty()) {
			if (mapId == HKC && showStates) {
				backgroundBackObjs[0]->OnShow();
			}
			else if (mapId != HKC) {
				for (auto& i : backgroundBackObjs) {
					i->OnShow();
				}
			}
			else {
				backgroundBackObjs[1]->OnShow();
			}
			
		}
		if (!floors.empty()) {
			for (auto i : floors) {
				i->OnShow();
			}
		}
		if (!backgroundFrontObjs.empty()) {
			for (auto& i : backgroundFrontObjs) {
				i->OnShow();
			}
		}
		if (!floorObjs.empty()) {
			for (auto i : floorObjs) {
				i->OnShow();
			}
		}
	}
	Map::~Map() {
		if (!floorObjs.empty()) {
			for (auto& i : floors) {
				delete i;
			}
		}
		if (!floorObjs.empty()) {
			for (auto& i : floorObjs) {
				delete i;
			}
		}
		if (!backgroundFrontObjs.empty()) {
			for (auto& i : backgroundFrontObjs) {
				delete i;
			}
		}
		if (!backgroundSkyObjs.empty()) {
			for (auto& i : backgroundSkyObjs) {
				delete i;
			}
		}
		if (!backgroundBackObjs.empty()) {
			for (auto& i : backgroundBackObjs) {
				delete i;
			}
		}
	
		//floors.clear();
	}
   
}
	/// <summary> friend int GetScenesPos(Map &map,const string type);
	/// GameObject :    �����W�Ҧ��������O(�Z���B�����B�D��)
	/// </summary>
	/// <param name="type"></param>

