#include <vector>
namespace  game_framework {
    class SelectCharacterMenu {
    public : 
        SelectCharacterMenu();
        virtual void OnShow();
        void Load(int);
        void Initialize();
        int seclectedID, posID;
        ~SelectCharacterMenu();
        //int seclectedID, posID;  // �ݭק�
    protected:
        vector<vector<int>> posistion_XY;					// �ϧΥ��W���y��  
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
