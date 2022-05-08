import os
import cv2

width=770
height=440
count=0;
img = cv2.imread('freeze_col_mirror.bmp')

for i in range(0,height,110):
    for j in range(1,width,110):
        cv2.imwrite(str('freeze_col_reverse_'+str(count)+'.bmp'),img[i:i+109,j:j+109])
        count+=1


cv2.imshow('img',img[240:320,80:160])
cv2.waitKey(0)
cv2.destroyAllWindows()