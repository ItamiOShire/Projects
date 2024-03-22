import cv2
import numpy as np
import math

from Character import Character
from Plate import Plate

# constants for check_if_character
MIN_PIXEL_WIDTH = 2
MIN_PIXEL_HEIGHT = 8

MIN_ASPECT_RATIO = 0.25
MAX_ASPECT_RATIO = 1.0

MIN_PIXEL_AREA = 80

# constants for comparing two chars
MIN_DIAG_SIZE_MULTIPLE_AWAY = 0.3
MAX_DIAG_SIZE_MULTIPLE_AWAY = 5.0

MAX_AREA_RATIO = 0.5
MAX_WIDTH_RATIO = 0.8
MAX_HEIGHT_RATIO = 0.2

MAX_ANGLE_BETWEEN_CHARS = 12.0

# minimum value to be matched as license plate
MIN_NUMBER_OF_MATCHING_CHARS = 3

# plate padding factors
PLATE_WIDTH_PADDING_FACTOR = 1.3
PLATE_HEIGHT_PADDING_FACTOR = 1.5


def convert_to_grayscale(img):
    # convert to grayscale by extracting V value from HSV model
    imgHSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    _, _, V = cv2.split(imgHSV)

    return V


def maximise_contrast(gray_img):
    # maximize contrast by using tophat and blackhat morphology
    structuring_element = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
    img_top_hat = cv2.morphologyEx(
        gray_img, cv2.MORPH_TOPHAT, structuring_element)
    img_black_hat = cv2.morphologyEx(
        gray_img, cv2.MORPH_BLACKHAT, structuring_element)

    img_partial = cv2.add(gray_img, img_top_hat)

    return cv2.subtract(img_partial, img_black_hat)


def convert_to_threshold(gray_img):
    # convert to threshold
    img_contrast = maximise_contrast(gray_img)
    img_blurred = cv2.GaussianBlur(img_contrast, (5, 5), 0)

    return cv2.adaptiveThreshold(img_blurred, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 19, 9)


def check_if_character(character):
    # check if character fulfill requirements
    if (character.bounding_area < MIN_PIXEL_AREA):
        return False
    if (character.bounding_rect_width < MIN_PIXEL_WIDTH):
        return False
    if (character.bounding_rect_height < MIN_PIXEL_HEIGHT):
        return False
    if (character.aspect_ratio < MIN_ASPECT_RATIO):
        return False
    if (character.aspect_ratio > MAX_ASPECT_RATIO):
        return False

    return True


def find_characters(thresh_img):
    # find characters in thresh img using check_if_character
    found_characters = []
    thresh_copy = thresh_img.copy()

    contours, _ = cv2.findContours(
        thresh_copy, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        possible_character = Character(contour)
        if check_if_character(possible_character):
            found_characters.append(possible_character)

    return found_characters


def calculate_distance(first, second):
    # calculate distance between two characters
    x = abs(first.center_x - second.center_x)
    y = abs(first.center_y - second.center_y)

    return math.sqrt(x ** 2 + y ** 2)


def calculate_angle(first, second):
    # calculate angle between two characters
    adj = abs(first.center_x - second.center_x)
    opp = abs(first.center_y - second.center_y)

    if adj != 0.0:
        angle_rad = math.atan(opp / adj)
    else:
        return 90.0

    return angle_rad * (180.0 / math.pi)


def find_matching_characters(character, match_list):
    # compare characters to find simillar ones
    matching_characters = []

    for possible_match in match_list:
        if possible_match == character:
            continue

        distance_between = calculate_distance(character, possible_match)
        angle_between = calculate_angle(character, possible_match)

        area_ratio = abs(character.bounding_area -
                         possible_match.bounding_area) / character.bounding_area
        width_ratio = abs(character.bounding_rect_width -
                          possible_match.bounding_rect_width) / character.bounding_rect_width
        height_ratio = abs(character.bounding_rect_height -
                           possible_match.bounding_rect_height) / character.bounding_rect_height

        if distance_between > character.diagonal_length * MAX_DIAG_SIZE_MULTIPLE_AWAY:
            continue
        if angle_between > MAX_ANGLE_BETWEEN_CHARS:
            continue
        if area_ratio > MAX_AREA_RATIO:
            continue
        if width_ratio > MAX_WIDTH_RATIO:
            continue
        if height_ratio > MAX_HEIGHT_RATIO:
            continue

        matching_characters.append(possible_match)

    return matching_characters


def match_characters(characters):
    # match sets of characters (recursive)
    matching_characters_list = []

    for character in characters:
        matching_characters = find_matching_characters(character, characters)
        matching_characters.append(character)

        if len(matching_characters) < MIN_NUMBER_OF_MATCHING_CHARS:
            continue

        matching_characters_list.append(matching_characters)
        reduced_list = list(set(characters) - set(matching_characters))

        recursive_list = match_characters(reduced_list)  # recursive call
        for recursive_match in recursive_list:
            matching_characters_list.append(recursive_match)

        break

    return matching_characters_list


def extract_plate(img, characters):
    # extract possible plates around found sets of characters
    possible_plate = Plate()

    # sort characters from left to right
    characters.sort(key=lambda match: match.center_x)

    plate_center_x = (characters[0].center_x + characters[-1].center_x) / 2
    plate_center_y = (characters[0].center_y + characters[-1].center_y) / 2
    plate_center = (plate_center_x, plate_center_y)

    plate_width = int((characters[-1].bounding_rect_x + characters[-1].bounding_rect_width -
                       characters[0].bounding_rect_x) * PLATE_WIDTH_PADDING_FACTOR)

    total_height = 0
    for character in characters:
        total_height += character.bounding_rect_height

    average_height = total_height / len(characters)
    plate_height = int(average_height * PLATE_HEIGHT_PADDING_FACTOR)

    opposite = characters[-1].center_y - characters[0].center_y
    hypotenuse = calculate_distance(characters[0], characters[-1])
    correction_angle = math.asin(opposite / hypotenuse) * (180.0 / math.pi)

    possible_plate.location_on_img = (
        tuple(plate_center), (plate_width, plate_height), correction_angle)

    rotation_matrix = cv2.getRotationMatrix2D(
        tuple(plate_center), correction_angle, 1.0)

    height, width, _ = img.shape
    rotated_img = cv2.warpAffine(img, rotation_matrix, (width, height))
    cropped_img = cv2.getRectSubPix(
        rotated_img, (plate_width, plate_height), tuple(plate_center))

    possible_plate.plate_img = cropped_img

    return possible_plate


def detect_plates(img):
    # main function - detect possible licence plates on given img
    possible_plates = []
    height, width, _ = img.shape

    gray_img = np.zeros((height, width, 1), np.uint8)
    threshold_img = np.zeros((height, width, 1), np.uint8)
    contours_img = np.zeros((height, width, 3), np.uint8)

    gray_img = convert_to_grayscale(img)
    threshold_img = convert_to_threshold(gray_img)

    found_charecters = find_characters(threshold_img)
    matched_characters_array = match_characters(found_charecters)

    for matched_characters in matched_characters_array:
        possible_plate = extract_plate(img, matched_characters)
        possible_plate.chars_len = len(matched_characters)

        if possible_plate.plate_img is not None:
            possible_plates.append(possible_plate)

    # sort by number of found possible chars in plate from highest to lowest
    possible_plates.sort(key=lambda plate: plate.chars_len, reverse=True)

    return possible_plates
