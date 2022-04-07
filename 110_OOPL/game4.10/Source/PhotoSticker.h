#include<memory>
namespace game_framework {
    class PhotoSticker {

    public:
        PhotoSticker(int);
        void OnShow();
        void Load();
        ~PhotoSticker();
    protected:
        void Initialize(int ind);
        vector<int>photoSticker_XY;
        vector<vector<int>> posistion_XY;
        vector < CMovingBitmap >info;
        CMovingBitmap infoA, infoB, infoC;
    };
}