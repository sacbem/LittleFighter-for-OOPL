#include <vector>
namespace  game_framework {
    class SelectCharacterMenu {
    public : 
        SelectCharacterMenu();
        virtual void OnShow();
        void Load(int);
        void Initialize();
        ~SelectCharacterMenu();
        int seclectedID, posID;  // 需修改
    protected:
        vector<vector<int>> posistion_XY;					// 圖形左上角座標  
        CMovingBitmap pic;
        
       
    };

    class Seclecter :public SelectCharacterMenu {
    public:
        Seclecter(int );
        virtual void OnShow() override;
        void SetXY(int , int );
        void Load(vector<int>, vector<int>, vector<int>);
        //void Load(vector<int>);
        void IsSeclected(int);
        int GetCharacterID();
        void Initialize(int );
        ~Seclecter();
    protected:

        vector<int>photoSticker_XY;
        vector<CMovingBitmap> Picture, Name, Id;
        CMovingBitmap PicA, PicB, PicC,nameA,nameB,nameC,idA,idB,idC;
   
    };

    class PhotoSticker :public SelectCharacterMenu {

    public:
        PhotoSticker(int );
        void Load(int, int, int);
        virtual void OnShow() override;
        void Initialize(int );
        ~PhotoSticker();

    protected:
        vector<int>photoSticker_XY;
        CMovingBitmap name, id;
    };
}
