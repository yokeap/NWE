import numpy as np
import cv2
import screeninfo

screen_id = 1

#get the size of the  screen
screen = screeninfo.get_monitors()[screen_id]
width, height = screen.width, screen.height

img = cv2.imread('Lenna2.png',1)

cv2.namedWindow('image', cv2.WINDOW_NORMAL)
cv2.moveWindow('image', screen.x -1, screen.y -1)
cv2.setWindowProperty("image",cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
