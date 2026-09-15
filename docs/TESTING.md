# Testing and Memory Checks

## Normal build

Build the openFrameworks Visual Studio project in Debug and Release configurations. Run the synthetic detector test and manually test the GUI with several legal sample images.

## Sanitizer check

On Windows, use Visual Studio Diagnostic Tools, the CRT debug heap, and the AddressSanitizer option available in recent MSVC toolsets. Enable AddressSanitizer in the project properties, build Debug, and run the test/application while processing several images. Record a screenshot of the clean output.

The code avoids manual `new`/`delete`. OpenCV `cv::Mat`, `std::vector`, `std::string`, and openFrameworks image/pixel objects manage their own resources through RAII. A clean run is evidence, not a mathematical proof, so the report should state exactly which checks were run.
