# Architecture

`ofApp` is the openFrameworks UI and I/O layer. It handles the window, drag-and-drop, file picker, image display, and conversion between OpenCV images and openFrameworks pixels.

The `lpr` namespace is the reusable computer-vision core:

- `ImagePreprocessor`: grayscale conversion, blur, Canny, morphology closing.
- `PlateDetector`: contours, geometry filters, scoring, crop extraction.
- `LicensePlateReader`: orchestration.
- `OcrEngine`: replaceable recognition boundary.

The detector is shared for German and Iranian plates. A future `PlateFormat` strategy can provide format validation, script, expected character structure, and OCR language without duplicating localization.
