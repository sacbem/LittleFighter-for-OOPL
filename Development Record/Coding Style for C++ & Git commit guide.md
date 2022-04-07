---
title: Coding Style for C++ & Git commit guide
---

## Coding Style 

- ## basic 
    - 縮排 : 4 個空白
    - 型別
        -非必要時不要用 auto，除非無法預測

    - 變數
        - 以單字敘述，除非為公認的縮寫，ex:`pwd`,
        - 變數命名使用峰駝式命名小寫開頭 :`widthOfBox` 
    
            `int indexScalar=100;`
        
        - 指標 :
            - 使用 `int *p`
            - 解參考 `p->index`
        - 參考:
            <pre>
                int &x = l;
            </pre> 

    - 類別
        - 類別命名使用峰駝式命名大寫開頭 : `MyClass`
        - `private` 置頂
    
                Class gameFramework{
                    public:

                    private:
                };
     
    - 函式
        - 函式命名使用峰駝式命名小寫開頭 : `myFunction()`

                void keyIn(int key){

                };
        
    - 全域變數
        - 開頭加上 `g` 及底線 `g_widthOfBox`


- ## 迴圈與敘述
    - if ... else...
        
            if(condition){

            }
            else{

            }
       
    -  若無負邏輯，仍需實作
         
            if(condition){

            }
            else{
                return 0; //負邏輯
            }
        
    - for / while 
     
             for (int i=0 ; i<9 ; i++){

             }
             for (auto i :x){

             }    
             for (auto &i :x){

             } 

## Git commit guide
- 可以使用 Conventional Commits (vscode套件)產生commit內容
- 每次做完一個功能就push一次，不然codereview很難做




