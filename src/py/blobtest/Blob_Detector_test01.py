import cv2
import numpy as np

# Load image
img = cv2.imread("blobs_c02.jpg")

imgB, imgG, imgR = cv2.split(img)

cv2.imshow("Original", img)
cv2.imshow("Kanal B", imgB)
cv2.imshow("Kanal G", imgG)
cv2.imshow("Kanal R", imgR)


cv2.waitKey(1)

# Set up the SimpleBlobDetector with default parameters
params = cv2.SimpleBlobDetector_Params()

# Set the threshold
params.minThreshold = 10
params.maxThreshold = 200

# Set the area filter
params.filterByArea = True
params.minArea = 100
params.maxArea = 1000

# Set the circularity filter
params.filterByCircularity = True
params.minCircularity = 0.1
params.maxCircularity = 1

# Set the convexity filter
params.filterByConvexity = True
params.minConvexity = 0.87
params.maxConvexity = 1

# Set the inertia filter
params.filterByInertia = True
params.minInertiaRatio = 0.01
params.maxInertiaRatio = 1

# Create a detector with the parameters
# detector = cv2.SimpleBlobDetector_create(params)
# Create detector with defaults
detector = cv2.SimpleBlobDetector_create()

# Detect blobs
keypoints = detector.detect(img)

# Draw detected blobs as red circles
# img_with_keypoints = cv2.drawKeypoints(img, keypoints, np.array([]), (0, 0, 255),
#                                       cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

# Show the image with detected blobs
img_blobs = img

# detect colors of blobs
# loop all keypoints
for i in range(len(keypoints)):
    x = round(keypoints[i].pt[0])
    y = round(keypoints[i].pt[1])
    size = round(keypoints[i].size)
    print(x)
    print(y)
    print(size)
    center = (x, y)
    radius = size
    color = (255, 0, 0)
    thickness = 2
    img_blobs = cv2.circle(img_blobs, center, radius, color, thickness)
    cv2.imshow("Blobs", img_blobs)

    cv2.waitKey(0)
# crop small rectangle

# calculate color

cv2.waitKey(0)
cv2.destroyAllWindows()
