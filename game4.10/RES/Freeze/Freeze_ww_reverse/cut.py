import os
import cv2

width=800
height=320
count=0;
img = cv2.imread('freeze_ww_mirror.bmp')

for i in range(0,height,160):
    for j in range(1,width,160):
        cv2.imwrite(str('freeze_ww_reverse_'+str(count)+'.bmp'),img[i:i+159,j:j+159])
        count+=1


cv2.imshow('img',img[240:320,80:160])
cv2.waitKey(0)
cv2.destroyAllWindows()