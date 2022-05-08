import os
import cv2

width=328
height=249
count=0;
img = cv2.imread('woody_ball_mirror.bmp')

for i in range(0,height,83):
    for j in range(1,width,82):
        cv2.imwrite(str('woody_ball_reverse_'+str(count)+'.bmp'),img[i:i+82,j:j+81])
        count+=1


cv2.imshow('img',img[240:320,80:160])
cv2.waitKey(0)
cv2.destroyAllWindows()