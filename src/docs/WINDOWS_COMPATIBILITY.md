# Windows compatibility

Target: Windows 7 and 8/8.1. Open decisions (to be verified before coding):
- UI and rendering technology (must run on Win7/8; no Win10/11-only dependencies)
- Video decoding path for 4K/8K (hardware decode support on older GPUs, software fallback)
- Audio capture/analysis path for the shared analyzer
- Packaging (see packaging/windows7, windows8)
Rendering has Low/Balanced/High/Ultra modes, separate for speakers and video.
