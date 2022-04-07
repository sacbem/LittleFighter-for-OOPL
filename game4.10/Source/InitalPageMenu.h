#include <vector>
namespace game_framework {


    class MenuBtn
    {
    public:
        MenuBtn();
        virtual void OnShow()= 0;					// 將圖形貼到畫面
        virtual void buttonTouch() = 0;
        virtual void Load() = 0;
    
    protected:
        vector<vector<int>> posistion_XY;					// 圖形左上角座標  
        vector <CMovingBitmap> Btn;
        CMovingBitmap btnNClick;
        CMovingBitmap btnClick;
    };
    /////////////////////////////////////// StartBtn(Derived) ///////////////////////////////////////
    class StartBtn :public MenuBtn {
    public:
        StartBtn();
        virtual void buttonTouch() override;
        virtual void Load() override;
        virtual void OnShow() override;
        ~StartBtn();
    
    };
    /////////////////////////////////////// SettingBtn(Derived) ///////////////////////////////////////
    class SettingBtn :public MenuBtn {
    public:
        SettingBtn();
        virtual void buttonTouch() override;
        virtual void Load() override;
        virtual void OnShow() override;
        ~SettingBtn();
    };
}