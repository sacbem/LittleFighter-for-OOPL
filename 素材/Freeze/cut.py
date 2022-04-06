import os
import cv2

width=800
height=560
count=0;
img = cv2.imread('freeze_2_mirror.bmp')

for i in range(0,height,80):
    for j in range(0,width,80):
        cv2.imwrite(str('freeze_2_reverse_'+str(count)+'.bmp'),img[i:i+80,j:j+80])
        count+=1


cv2.imshow('img',img[240:320,80:160])
cv2.waitKey(0)
cv2.destroyAllWindows()