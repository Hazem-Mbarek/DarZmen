import threading
import cv2
from deepface import DeepFace


cap=cv2.VideoCapture(0,cv2.CAP_DSHOW)

cap.set(cv2.CAP_PROP_FRAME_WIDTH,640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,480)

counter=0

face_match=False

reference_img = cv2.imread("C:\\Users\\kills\\Desktop\\facial recognition\\reference.jpg")


def check_face(frame):
    global face_match
    try:
        if DeepFace.verify(frame,reference_img.copy())['verified']:
            face_match=True
            #with open("face_recognition_result.txt", "w") as file:
             #   file.write("MATCH")
        else:
            face_match=False
            #with open("face_recognition_result.txt", "w") as file:
            #    file.write("NO MATCH")
    except ValueError:
        face_match=False
        
        

while True:
    ret, frame=cap.read()

    if ret:
        if counter%30==0:
            try:
                threading.Thread(target=check_face,args=(frame.copy(),)).start()
            except ValueError:
                pass
        counter+=1
        if face_match:
            print("MATCH")
            break
        else:
           
            cv2.putText(frame, "q pour quitter", (20, 450), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 3)
        cv2.imshow("video", frame)

    key = cv2.waitKey(1)
    if key == ord("q") or key == ord("Q"):
        print("NO MATCH")
        break

cv2.destroyAllWindows()

