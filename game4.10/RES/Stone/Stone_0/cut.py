import os
import cv2

width=455
height=60
count=0;
img = cv2.imread('weapon1.bmp')

for i in range(0,height,59):
    for j in range(0,width,59):
        cv2.imwrite(str('stone_'+str(count)+'.bmp'),img[i:i+58,j:j+58])
        count+=1


cv2.imshow('img',img[0:58,0:58])
cv2.waitKey(0)
cv2.destroyAllWindows()