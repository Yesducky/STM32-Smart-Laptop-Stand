from PIL import Image, ImageDraw
import os
import time
import matplotlib.pyplot as plt

w = 320
h = 240
def pixel_2_data(pixel_data):

    output = os.getcwd() + "\\output1.jpeg"

    print("drawing...")

    RGB = []
    for x in range(0, w * h * 2, 2):
        f1 = pixel_data[x]
        f2 = pixel_data[x + 1]

        s = (f2 << 8) + f1
        # RGB565 -> Grayscale
        r = (s & 0xF800) >> 11 
        g = (s & 0x7E0) >> 5
        b = (s & 0x1F)

        RGB.append(r + g + b)

    image = Image.new('L', (w, h))
    draw = ImageDraw.Draw(image)
    i = 0
    for y in range(h):
        for x in range(w):
            draw.point((x, y), fill=RGB[i])
            i += 1

    image.save(output, 'jpeg')
    
    # Display the image using matplotlib
    img = plt.imread(output)
    plt.imshow(img)
    plt.show()
    
    time.sleep(1)
    image.close()

    
