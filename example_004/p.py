#!/usr/bin/python

import os
import io
import sys
from PIL import Image
import matplotlib.pyplot as plt


def f(W,H,DPI):

	# C++ API pass float arguments, we need integers
	W = int(W); H = int(H); DPI = int(DPI)
	fig = plt.figure(figsize=(W/DPI, H/DPI))

	# Plot whatever!
	plt.plot([0,1,2,3,4,5],[2,4,7,9,12,24])
	plt.tight_layout()

	# Save image to variable
	image = io.BytesIO()
	fig.savefig(image, format = "png", dpi = DPI)
	image.seek(0)
	im = Image.open(image)

	# Convert PNG graphics to RGB list
	rgb = im.convert('RGB')

	# Close image and pyplot
	im.close()
	plt.close()

	# Convert RGB values to R,G,B lists
	R = []
	G = []
	B = []
	for i in range(W*H):
		r,g,b = rgb.getpixel((i%W,i/W))
		R.append(r)
		G.append(g)
		B.append(b)

	return [R,G,B]
