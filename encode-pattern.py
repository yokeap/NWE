import numpy as np
import cv2

img = cv2.imread('lenna2.png',1)

cv2.namedWindow('image', cv2.WINDOW_NORMAL)
cv2.setWindowProperty("image",cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_NORMAL)
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
