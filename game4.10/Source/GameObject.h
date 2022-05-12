#pragma once

namespace game_framework {
	class GameObject {
		//friend  void  SetPosition_Scenes(Map &map,int x, int y);;
	public:
		GameObject(const string type);
		GameObject(int num,const string type);
		void Initialize(const string type);
		void Load(int bitmap ,COLORREF = CLR_INVALID); 
		void Load(char*, COLORREF = CLR_INVALID);
		void Load(int imgID,int bitmap, COLORREF = CLR_INVALID);
		void Load(int imgID,char*, COLORREF = CLR_INVALID);
		void SetTopLeft(int x, int y);
		void SetTopLeft(int id_x, int id_y,int x, int y);
		void SetTopLeftSpical(int x, int y);
		string GetClassification();
		int GetPositionXY(const string type);
		int GetPositionXY(int id_x, int id_y,const string type);
		void OnShow();
		void OnShow(int id_x, int id_y);
		~GameObject();
	private:
		int xPos, yPos;
		int index;
		boolean anotherDestructorEnable;
		boolean IsWeapon, IsItem, IsScenes,IsEffect;
		CMovingBitmap img;
		vector<vector<CMovingBitmap*>> imgs;
		vector<vector<pair<int, int>>> Pos_imgs;
	};
}
