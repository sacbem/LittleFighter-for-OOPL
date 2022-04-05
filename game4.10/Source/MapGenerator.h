namespace game_framework {
    class MapGenerator {
    public:
        MapGenerator();
        ~MapGenerator();
        void ScenesCamera( boolean,int );
        void Load(int);
        void PrintMap();
        
    private:
        //vector<CMovingBitmap*>  lands, walls;
        //
        vector<CMovingBitmap>lands, walls;
        vector<vector<int>>landsPosXY{ {0, 300},{210, 390},{385, 374},{170, 385} }, wallPosXY;
        void SetLandPosition();
        void Initialize(int);
        void SetWallPosition();
        CMovingBitmap backGreen;
        CMovingBitmap *weed1,* weed2, *weed3, *weed4;
        vector<CMovingBitmap*> weeds;
    };
}