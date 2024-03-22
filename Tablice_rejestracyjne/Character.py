import cv2
import math


class Character:
    def __init__(self, contour):
        self.bounding_rect = cv2.boundingRect(contour)

        [intX, intY, intWidth, intHeight] = self.bounding_rect

        self.bounding_rect_x = intX
        self.bounding_rect_y = intY
        self.bounding_rect_width = intWidth
        self.bounding_rect_height = intHeight

        self.bounding_area = self.bounding_rect_width * self.bounding_rect_height

        self.center_x = (self.bounding_rect_x * 2 +
                         self.bounding_rect_width) / 2
        self.center_y = (self.bounding_rect_y * 2 +
                         self.bounding_rect_height) / 2

        self.diagonal_length = math.sqrt(
            self.bounding_rect_width ** 2 + self.bounding_rect_height ** 2)
        self.aspect_ratio = float(
            self.bounding_rect_width) / float(self.bounding_rect_height)
