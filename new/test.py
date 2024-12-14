import numpy as np
import cv2

def analyse(img):
    imgGry = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    ret , thrash = cv2.threshold(imgGry, 240 , 255, cv2.CHAIN_APPROX_NONE)
    contours , hierarchy = cv2.findContours(thrash, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    for contour in contours:
        approx = cv2.approxPolyDP(contour, 0.01* cv2.arcLength(contour, True), True)
        cv2.drawContours(img, [approx], 0, (0, 0, 0), 5)
        x = approx.ravel()[0]
        y = approx.ravel()[1] - 5
        if len(approx) == 4 or len(approx) == 1:
            print("ligne")
        elif len(approx) == 3:
            print("triangle")
        elif len(approx) == 8 :
            x, y , w, h = cv2.boundingRect(approx)
            aspectRatio = float(w)/h
            if aspectRatio >= 0.95 and aspectRatio < 1.05:
                print("carré")

            else:
                print("rectangle")
        elif len(approx) == 5 :
            print("pentagone")
        elif len(approx) == 10 :
            print("étoile")



def main():
    base = cv2.imread('base_circuit.png')
    imgs = []
    k = 1
    l = 1
    for i in range(0, 10):
        for j in range(0, 10):
            imgs.append(base[i*150:150+i*150, j*150:150+j*150])

    for img in imgs:
        print(k)
        print(l)
        l+=1
        if(l==11):
            l = 1
            k+=1
        analyse(img)

if __name__ == "__main__":
    main()




