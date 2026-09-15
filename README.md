# LicensePlateReader

C++17/openFrameworks + OpenCV project for detecting a likely license-plate region in a still vehicle image.

## Planned progression

1. Project scaffold and openFrameworks window.
2. Image preprocessing and Canny edges.
3. Morphological closing and contour filtering.
4. OCR interface and placeholder implementation.
5. Drag-and-drop/file-picker application integration.
6. Tests, memory checks, and documentation.

The baseline is intentionally explainable and modular. OCR is isolated behind an interface so a real German or Persian OCR adapter can be added without rewriting plate localization.
