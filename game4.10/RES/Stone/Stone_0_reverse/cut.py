import os
import cv2

width=455
height=59
count=0;
img = cv2.imread('weapon1_mirror.bmp')

for i in range(0,height,59):
    for j in range(456,0,-59):
        cv2.imwrite(str('box_reverse_'+str(count)+'.bmp'),img[i:i+58,j:j+58])
        count+=1


cv2.imshow('img',img[0:58,0:58])
cv2.waitKey(0)
cv2.destroyAllWindows()