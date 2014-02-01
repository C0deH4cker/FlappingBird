#!/usr/bin/env python

import urllib
import Image
from StringIO import StringIO

url = "http://www.spriters-resource.com/resources/sheets/56/59537.png"
png = urllib.urlopen(url).read()
data = StringIO(png)

sprites = Image.open(data)

atlas = (
	((  0,  0, 144, 256), "background.png"),
	((264, 90, 281, 102), "bird.png"),
	((146,  0, 300,  56), "ground.png"),
	((302,  0, 328, 135), "pipe_top.png"),
	((330,  0, 356, 121), "pipe_bottom.png")
)

for sprite in atlas:
	sprites.crop(sprite[0]).save(sprite[1])
