# Yellowdig Draft 2 — Preprocessing

**Tag:** Project 1 — License Plate Reader — [Team Name]

The first image-processing stage now converts the image to grayscale, applies Gaussian blur, and produces a Canny edge map. I am using a horizontal structuring element for closing because plate characters create nearby edge fragments. The current obstacle is false positives from grilles and other rectangular regions, so I am adding area, aspect-ratio, and rectangularity filters instead of selecting the largest contour.
