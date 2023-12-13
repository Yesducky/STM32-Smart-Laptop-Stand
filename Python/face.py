import cvzone
from cvzone.FaceDetectionModule import FaceDetector
import cv2
import matplotlib.pyplot as plt
import time

# Initialize the FaceDetector object
# minDetectionCon: Minimum detection confidence threshold
# modelSelection: 0 for short-range detection (2 meters), 1 for long-range detection (5 meters)
def Find_face(filename):
    
    detector = FaceDetector(minDetectionCon=0.2, modelSelection=0)

    img = cv2.imread(filename)
        # Detect faces in the image
        # img: Updated image
        # bboxs: List of bounding boxes around detected faces

    img, bboxs = detector.findFaces(img, draw=False)
    center = 0

    # If there are faces detected
    if bboxs:

        for bbox in bboxs:
            # bbox contains 'id', 'bbox', 'score', 'center'

            c = bbox["center"]
            center = 240-c[1]
            x, y, w, h = bbox['bbox']
            score = int(bbox['score'][0] * 100)

            cv2.circle(img, c, 5, (255, 0, 255), cv2.FILLED)
            cvzone.putTextRect(img, f'{score}%', (x, y - 10))
            cvzone.cornerRect(img, (x, y, w, h))
            
        #print("center: ", center)

    cv2.imwrite('outputface2.jpg', img)
    
    if not bboxs:
        return 0
    
    img = plt.imread("outputface2.jpg")
    plt.imshow(img)
    plt.show()
    

    return center

