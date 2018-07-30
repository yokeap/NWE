import sys
sys.path.append('/usr/local/lib/python2.7/site-packages')

import numpy as np
import cv2
#import screeninfo



screen_id = 1

window_width = 800
window_height = 600

#get the size of the  screen
#screen = screeninfo.get_monitors()[screen_id]
#width, height = screen.width, screen.height

#img = cv2.imread('Lenna2.png',1)

# Create blank image as black

blank_image = np.zeros((600,1024,1), np.uint8)

# 32(2^5) strip binary generator, each strip has 32 px width
for w in range(0, 1024, 64):
    blank_image[:,w:w+32] = np.ones((600,32,1), np.uint8) * 255

#print(blank_image[:,:16])

cv2.namedWindow('image', cv2.WINDOW_NORMAL)
#cv2.resizeWindow('image', 600,600)
#cv2.moveWindow('image', screen.x -1, screen.y -1)
#cv2.setWindowProperty("image",cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_NORMAL)
cv2.imshow('image', blank_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
