#include <vector>
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class提供可以用鍵盤或滑鼠控制的擦子
    // 看懂就可以改寫成自己的程式了
    /////////////////////////////////////////////////////////////////////////////

    class MenuBtn
    {
    public:
        MenuBtn();
        void Initialize(vector<vector<int>> positionXY);// 設定圖形初始值
        virtual void OnShow()= 0;					// 將圖形貼到畫面
        virtual void buttonTouch() = 0;
        virtual void Load() = 0;
    
    protected:
        vector<vector<int>> posistion_XY;					// 圖形左上角座標  
        vector <CMovingBitmap> Btn;
        CMovingBitmap btnNClick;
        CMovingBitmap btnClick;
    };

    class StartBtn :public MenuBtn {
    public:
        StartBtn();
        virtual void buttonTouch() override;
        virtual void Load() override;
        virtual void OnShow() override;
        ~StartBtn();
    
    };
    class SettingBtn :public MenuBtn {
    public:
        SettingBtn();
        virtual void buttonTouch() override;
        virtual void Load() override;
        virtual void OnShow() override;
        ~SettingBtn();
    };
}