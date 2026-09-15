# Architecture

`LicensePlateReader` orchestrates three collaborators:

- `ImagePreprocessor`: grayscale conversion, Gaussian blur, Canny edges, and morphology closing.
- `PlateDetector`: contours, geometry filters, scoring, and crop extraction.
- `OcrEngine`: abstract recognition boundary. `PlaceholderOcr` makes the baseline build without Tesseract.

The reader owns its preprocessor and detector by value. The OCR pointer is non-owning and must outlive the reader. If runtime ownership is needed later, use `std::unique_ptr` or `std::shared_ptr` according to the ownership relationship.

## Multi-format extension

Add a `PlateFormat` strategy with validation, expected aspect ratio, script, and OCR-language settings. Implement `GermanFormat` and `IranianFormat`; keep localization shared and select recognition/validation by format.
