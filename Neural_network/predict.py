import tensorflow as tf
from PIL import Image
import os

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

import matplotlib.pyplot as plt
import numpy as np
from tensorflow import keras


load_model = tf.keras.models.load_model
saved_model = load_model('model.h5')
def predict_image(img_path, model):
    img = Image.open(img_path).convert('L')
    img = img.resize((28, 28))
    img_arr = np.array(img)
    plt.imshow(img_arr)
    plt.show()

    pred = model.predict(img_arr.reshape((1, 28 * 28)))
    pred_class = np.argmax(pred)


    return pred_class

print(["T-Shirt", "Trousers"][predict_image('cos6.png',saved_model)])