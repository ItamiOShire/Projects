import cv2
import numpy as numpy
import os

import detect_plates


def main():
    img = cv2.imread("4.jpg")
    if img is None:
        print("error while reading image!")
        os.system("pause")
        return

    possible_plates = detect_plates.detect_plates(img)
    print(len(possible_plates))

    for plate in possible_plates:
        print(plate.chars_len)
        cv2.imshow("plate", plate.plate_img)
        cv2.waitKey(0)


if __name__ == "__main__":
    main()
