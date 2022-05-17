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
		void Load(int mapID);
		void GenerateLand(int mapID);
		void PrintMap(boolean showStates);
		void DynamicScence(boolean IsLeft,int walkedDistance);
		boolean ResetCharactAccumulator(int distance1,int distance2);
		~Map();
		
	private:
		void InitializeAllObjs(int mapID);
		void StopDynamic(boolean isLeft, int distance);
		void InitializeMap(int mapID);
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

	#define MapWidth_abonormal 794
	#define MapWidth_normal 3200 * 0.75

	constexpr auto forestSky_dx = MapWidth_normal / 800 * 0.75;
	constexpr auto forestMountain_dx1 = MapWidth_normal / 1100 * 0.75;
	constexpr auto forestMountain_dx2 = MapWidth_normal / 1400 * 0.75;
	constexpr auto forestTree_dx = 1.5 * MapWidth_normal / 2900 * 0.75;
	constexpr auto forestLand_dx1 = MapWidth_normal / 2950 * 0.75;
	constexpr auto forestLand_dx2 = MapWidth_normal / 3070 * 0.75;
	constexpr auto forestLand_dx3 = MapWidth_normal / 3200 * 0.75;


}