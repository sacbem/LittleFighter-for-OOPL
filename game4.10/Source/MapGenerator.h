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
        vector<vector<int>>landsPosXY{ {0, 300},{210, 390},{385, 374},{170, 385} };
        vector<double>skyPosXY{ -800,0 ,800};
        void SetLandPosition();
        void Initialize(int);
        void SetSkyPosition();
        CMovingBitmap *backGreen;
        vector<CMovingBitmap*> weeds,trees,mountains, sky;
    };
}