namespace  game_framework {
    class SelectCharacterMenu {
    public : 
        SelectCharacterMenu();
        void OnShow();
        void Load(vector<int>);
        ~SelectCharacterMenu();
    protected:
        vector<vector<int>> posistion_XY;					// 圖形左上角座標  
        vector <CMovingBitmap> characterPic;
        vector<CMovingBitmap> Picture;
        void Initialize();
     
    };
}
