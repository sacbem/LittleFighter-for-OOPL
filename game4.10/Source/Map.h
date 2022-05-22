#pragma once
#include "GameObject.h"
//#include "Character.h"
namespace game_framework{
	class Map {
		//friend 
	public:
		
		Map(int mapID);
		int GetScenesPos(const string type);
		void ScenesCamera(boolean mapMove, boolean IsRunning, boolean IsLeft, int walkedDistance);
		void Load();
		void GenerateLand();
		void PrintMap(boolean showStates);
		void DynamicScence(boolean IsLeft,int walkedDistance);
		int GetMapID();
		boolean ResetCharactAccumulator(int distance1,int distance2);
		~Map();
		
	private:
		void InitializeAllObjs();
		void StopDynamic(boolean isLeft, int distance);
		void InitializeMap();
		int rubberBandAccumulator(boolean IsRunning, boolean InBorder);
		int rubberMode; // rubberMode:  0 => Mode => 1 => Mode : Walking, 2 => Mode : Runing
		int mapId;
		boolean  cameraEnable;
		pair <int, int> gameScencePos; // first -> ScenceMinPosition; second -> ScenceMaxPosition 
		vector<boolean>mapBordary;//1:sky 2:tree 3:land 4: mountain
		vector<vector<int>> map;  // 2400*600 80*60 per blank;  30 * 10
	
		vector<boolean> characterInBorder;
		vector<GameObject*> floors, floorObjs, backgroundFrontObjs, backgroundBackObjs, backgroundSkyObjs;
		/// <summary>
		/// floors :　場景地面
		/// floorObjs: 場景地面上物件
		/// backgroundFrontObjs : 場景-前景
		/// backgroundBackObjs: 場景-後景
		/// backgroundSkyObjs:場景-天空
		/// </summary>
		/// 
	};


	
}
namespace mapConfiguration {
	#define Forest 0
	#define HKC 1
	#define BC 2

	
	#define MapWidth_Forest 3200 * 0.75
	#define MapWidth_HKC 794
	#define MapWidth_BC 1500

	constexpr int forestSky_dx = MapWidth_Forest / 800 * 0.75;
	constexpr int forestMountain_dx1 = MapWidth_Forest / 1100 * 0.75;
	constexpr int forestMountain_dx2 = MapWidth_Forest / 1400 * 0.75;
	constexpr int forestTree_dx = 8 * MapWidth_Forest / 2900 * 0.75;
	constexpr int forestLand_dx1 = MapWidth_Forest / 2950 * 0.75;
	constexpr int forestLand_dx2 = MapWidth_Forest / 3070 * 0.75;
	constexpr int forestLand_dx3 = MapWidth_Forest / 3200 * 0.75;


	constexpr int bcBackScence_dx = MapWidth_BC / 1379;
	constexpr int bcFrontScence_dx = MapWidth_BC / 1500;
	constexpr int bcLand_dx = MapWidth_BC /1500;
	
}