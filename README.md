# License Plate Reader

A C++17/openFrameworks application with an OpenCV classical-vision pipeline for locating license plates in still images.

## Current verified demo

- Windows Server VMware VM accessed through RDP.
- Mesa3D software OpenGL runtime beside the executable.
- Release x64 build succeeds.
- PNG vehicle image loads through the `O` file picker.
- Annotated plate and crop are displayed.
- Current OCR output is explicitly `OCR_NOT_CONFIGURED`; OCR integration is not yet implemented.

## Run

1. Generate or update the Visual Studio project with the openFrameworks Project Generator.
2. Select Release/x64.
3. Build the solution.
4. Run the executable.
5. Press `O` to select a PNG vehicle image or drag an image into the window.

## Pipeline

Grayscale → Gaussian blur → Canny edges → horizontal morphology closing → contours → geometry/score filters → annotation/crop → replaceable OCR boundary.

## Limitations

- The detector is a classical baseline and depends on image quality, perspective, and plate geometry.
- JPEG loading should be verified with the deployed OpenCV codec/runtime set; PNG was used for the verified demo.
- OCR is currently a placeholder interface.
- Do not report recognition accuracy without a labeled evaluation set.
