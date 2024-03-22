import tensorflow as tf
from PIL import Image
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import numpy as np
from tensorflow import keras

# Load the MNIST Fashion dataset
(train_images, train_labels), (test_images, test_labels) = keras.datasets.fashion_mnist.load_data()

# Define the desired classes (t-shirt and trousers)
desired_classes = [0, 1]  # Class 0: T-shirt/top, Class 1: trousers
# Filter the training data
train_indices = np.isin(train_labels, desired_classes)
train_images = train_images[train_indices]
train_labels = train_labels[train_indices]

# Filter the test data
test_indices = np.isin(test_labels, desired_classes)
test_images = test_images[test_indices]
test_labels = test_labels[test_indices]

# Normalize the pixel values of the images
train_images = train_images / 255.0
test_images = test_images / 255.0

# Reshape the images to match the input shape expected (28x28x1)
train_images=train_images.reshape(train_images.shape[0],28*28)
test_images=test_images.reshape(test_images.shape[0],28*28)

# Convert the labels to encoded format
num_classes = len(desired_classes)
train_labels = keras.utils.to_categorical(train_labels, num_classes)
test_labels = keras.utils.to_categorical(test_labels, num_classes)

# Build your model
model = keras.models.Sequential()
model.add(keras.layers.Dense(64, activation="sigmoid", input_shape=(784,)))
model.add(keras.layers.Dense(num_classes, activation="softmax"))
model.summary()

# Compile the model
model.compile(optimizer='adam', loss='mean_squared_error', metrics=['accuracy'])

# Train the model and save it into the appropriate file
model.fit(train_images, train_labels, epochs=50, batch_size=64, validation_data=(test_images, test_labels))

model.save('model.h5')