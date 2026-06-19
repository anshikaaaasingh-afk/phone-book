from PIL import Image
import numpy as np
import imageio.v3 as iio
filenames = ['gif/gif image 1.png', 'gif/gif image 2.png','gif/gif image 3.png','gif/gif image 4.png','gif/gif image 5.png','gif/gif image 6.png']
images = []
for filename in filenames:
    img= Image.open(filename)
    img =img.resize((835,830))
    images.append(np.array(img))
iio.imwrite('bot.gif', images, duration = 500, loop=0)