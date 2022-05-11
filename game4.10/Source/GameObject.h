#pragma once

namespace game_framework {
	class GameObject {
		//friend  void  SetPosition_Scenes(Map &map,int x, int y);;
	public:
		GameObject(const string type);
		void Initialize(const string type);
		void Load(int bitmap);
		void Load(int bitmap, int RGB); //¥h­I¥Î
		void Load(char*, COLORREF = CLR_INVALID);
		void SetTopLeft(int x, int y);
		void SetTopLeftSpical(int x, int y);
		string GetClassification();
		int GetPositionXY(const string type);
 
		void OnShow();
		~GameObject();
	private:
		int xPos, yPos;
		int index;
		boolean IsWeapon, IsItem, IsScenes,IsEffect;
		CMovingBitmap img;
	};
}
