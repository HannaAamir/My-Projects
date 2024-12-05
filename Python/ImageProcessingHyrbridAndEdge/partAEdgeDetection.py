import numpy as np
import cv2
import matplotlib.pyplot as plt
#Hanna Aamir

image = cv2.imread('grayscaleimage.jpeg', cv2.IMREAD_GRAYSCALE)



def apply_gaussian_smoothing(image, kernel_size=3, sigma=1.0):
    ax = np.linspace(-(kernel_size // 2), kernel_size // 2, kernel_size)
    gauss = np.exp(-0.5 * np.square(ax) / np.square(sigma))
    kernel = np.outer(gauss, gauss)
    kernel = kernel / np.sum(kernel)
    smoothed_image = cv2.filter2D(image, -1, kernel)
    return smoothed_image


smoothed_image = apply_gaussian_smoothing(image)



def sobel_operator(image):
    Kx = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    Ky = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]])

    Gx = cv2.filter2D(image, -1, Kx)
    Gy = cv2.filter2D(image, -1, Ky)
    return Gx, Gy


Gx, Gy = sobel_operator(smoothed_image)


gradient_magnitude = np.sqrt(Gx ** 2 + Gy ** 2)
gradient_magnitude = np.uint8(gradient_magnitude)


plt.imshow(gradient_magnitude, cmap='gray')
plt.title("Edge Detection using Sobel Operator")
plt.axis("off")
plt.savefig('gradient_magnitude_plot.png', bbox_inches='tight', dpi=300)
plt.show()

