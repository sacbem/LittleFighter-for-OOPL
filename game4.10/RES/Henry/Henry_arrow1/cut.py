import os
import cv2

width=490
height=146
count=0;
img = cv2.imread('henry_arrow1.bmp')

for i in range(0,height,49):
    for j in range(0,width,49):
        cv2.imwrite(str('henry_arrow1_'+str(count)+'.bmp'),img[i:i+48,j:j+48])
        count+=1


cv2.imshow('img',img[240:320,80:160])
cv2.waitKey(0)
cv2.destroyAllWindows()