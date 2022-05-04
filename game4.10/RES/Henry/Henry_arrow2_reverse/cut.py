import os
import cv2

width=294
height=96
count=0;
img = cv2.imread('henry_arrow2_mirror.bmp')

for i in range(0,height,48):
    for j in range(1,width,49):
        cv2.imwrite(str('henry_arrow2_reverse_'+str(count)+'.bmp'),img[i:i+47,j:j+48])
        count+=1


cv2.imshow('img',img[240:320,80:160])
cv2.waitKey(0)
cv2.destroyAllWindows()