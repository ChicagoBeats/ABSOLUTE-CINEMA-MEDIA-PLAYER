# Cinematic intro and outro

## Default intro
1. The title (crown above "ABSOLUTE CINEMA") starts tiny at the top center of the canvas.
2. It approaches, growing continuously, with a rising sound.
3. It becomes huge and fades away while still growing.
4. Optional: lean-forward tilt with a bass hit at the end of the approach.
5. The visualizer is already running behind it and takes over.

The title is an overlay on the last-used or saved visualizer (or black).

## Outro
Reverse: the title starts large and recedes smaller, then fades before the app closes. Enabled separately from the intro.

## Presets
Each intro is a preset (see `src/settings/intro_presets/default.json`): motion, finish effect, sound, background, timing, final size. New intros are new presets, not new code.

## Rules
- Skippable instantly; reduced-motion mode; must not delay startup or block decoding or audio init.
- Original branding and sound only. No THX or other third-party logos.
