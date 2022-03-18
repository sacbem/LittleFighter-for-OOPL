namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class提供可以用鍵盤或滑鼠控制的擦子
    // 看懂就可以改寫成自己的程式了
    /////////////////////////////////////////////////////////////////////////////

    class MenuBtn
    {
    public:
        MenuBtn();
        void Initialize(int positionX, int positionY);				// 設定圖形初始值
        void OnShow();					// 將圖形貼到畫面
        virtual void buttonTouch() = 0;
        virtual void Load() = 0;				// 載入圖形
        //void SetXY(int nx, int ny);		// 設定左上角座標
       
    protected:
        int x, y;					// 圖形左上角座標  
        CMovingBitmap Btn;
    };

    class StartBtn :public MenuBtn {
    public:
        StartBtn();
        void status();
        virtual void buttonTouch() override;
        virtual void Load() override;
        ~StartBtn();
    };
    class SettingBtn :public MenuBtn {
    public:
        SettingBtn();
        void status();
        virtual void buttonTouch() override;
        virtual void Load() override;
        ~SettingBtn();
    };
}