# Yellowdig Draft 3 — Architecture and Testing

**Tag:** Project 1 — License Plate Reader — [Team Name]

I separated preprocessing, plate detection, OCR, and orchestration into different classes. OCR is currently an interface with a placeholder implementation, so the detector can be tested without pretending that text recognition is complete. I added a synthetic detector test and documented Windows memory-check options. Next I will test the GUI with real images, capture outputs, and package the project manual and learning log.
