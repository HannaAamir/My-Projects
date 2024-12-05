import cv2
import numpy as np
import matplotlib.pyplot as plt
#Hanna Aamir

imageA = cv2.imread('elephant.jpeg', cv2.IMREAD_GRAYSCALE)
imageC = cv2.imread('cheetah.jpeg', cv2.IMREAD_GRAYSCALE)


if imageA is None or imageC is None:
    raise FileNotFoundError("One of the images could not be loaded. Check the file paths.")


def low_pass_filter(image, kernel_size=15):
    return cv2.GaussianBlur(image, (kernel_size, kernel_size), 0)

low_passed_A = low_pass_filter(imageA)


def high_pass_filter(image, kernel_size=15):
    low_pass = cv2.GaussianBlur(image, (kernel_size, kernel_size), 0)
    high_pass = cv2.subtract(image, low_pass)
    return high_pass

high_passed_C = high_pass_filter(imageC)


if low_passed_A.shape != high_passed_C.shape:
    high_passed_C = cv2.resize(high_passed_C, (low_passed_A.shape[1], low_passed_A.shape[0]))


low_passed_A = low_passed_A.astype('float32')
high_passed_C = high_passed_C.astype('float32')


hybrid_image = cv2.addWeighted(low_passed_A, 0.5, high_passed_C, 0.5, 0)


fig, axs = plt.subplots(1, 3, figsize=(15, 5))
axs[0].imshow(low_passed_A, cmap='gray')
axs[0].set_title('Low-pass Filtered Image A')
axs[0].axis('off')

axs[1].imshow(high_passed_C, cmap='gray')
axs[1].set_title('High-pass Filtered Image C')
axs[1].axis('off')

axs[2].imshow(hybrid_image, cmap='gray')
axs[2].set_title('Hybrid Image')
axs[2].axis('off')

plt.show()


cv2.imwrite('low_passed_elephant.jpg', low_passed_A)


cv2.imwrite('high_passed_cheetah.jpg', high_passed_C)


cv2.imwrite('hybrid_image.jpg', hybrid_image)


