import os
import cv2

width=328
height=166
count=0;
img = cv2.imread('henry_wind_mirror.bmp')

for i in range(0,height,83):
    for j in range(1,width,82):
        cv2.imwrite(str('henry_wind_mirror_'+str(count)+'.bmp'),img[i:i+82,j:j+81])
        count+=1


cv2.imshow('img',img[0:0,48:48])
cv2.waitKey(0)
cv2.destroyAllWindows()