# Speaker system

Default skin: flat black cabinets, two large woofers each, silver concentric rings, thin outline border (see the reference image in assets/speaker_cabinets).
- 4 cabinets left, 4 right, 16 drivers total (do not hardcode 16).
- Physics (excursion, inertia, damping, resonance) is separate from rendering and from skins.
- Driven by one shared audio analysis stream (FFT, RMS, peaks, left/right) also used by the DB meter and visualizers.
- Left channel drives left drivers, right drives right; bass drives the strongest movement.
- Speaker visibility (slide out) is independent of cone animation.
- dB meter shows dBFS, not real-world SPL.
