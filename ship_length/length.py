import cv2
import numpy as np
import math

scale = 0
state = 0

def distance(point1, point2):
    """Calculates the Euclidean distance between two points."""
    return math.sqrt((point2[0] - point1[0])**2 + (point2[1] - point1[1])**2)
    #return math.sqrt((point2[0] - point1[0])**2 )

def click_event(event, x, y, flags, param):
    global state
    global scale
    """Handles mouse clicks to store point coordinates and calculate distance."""
    if event == cv2.EVENT_LBUTTONDOWN:
        points.append((x, y))
        cv2.circle(img, (x, y), 3, (255, 0, 0), -1)
        if len(points) == 2 and state == 0:
            dist = distance(points[-1], points[-2])
            cv2.line(img, points[-1], points[-2], (0, 255, 0), 1)

            # The first two clicks are the known pipe length: 2.1 cm
            scale = dist / 2.1

            state = 1
            points.clear()

        if len(points) == 2 and state == 1:
            dist = distance(points[-1], points[-2])
            size = dist / scale

            cv2.putText(img, f"Size: {size:.2f} cm", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

        cv2.imshow("image", img)

# Load the image
img = cv2.imread("pipe.jpg") # Replace with your image file path
if img is None:
    raise FileNotFoundError(
        "Could not load 'pipe.jpg'. Check that the file exists in this "
        "directory and the path/name is correct."
    )
points = []

# Create a window and bind the click event
while True:
    cv2.imshow("image", img)
    cv2.setMouseCallback("image", click_event)
    if (cv2.waitKey(25) & 0xFF) == ord('q'):
        cv2.destroyAllWindows()
        break
