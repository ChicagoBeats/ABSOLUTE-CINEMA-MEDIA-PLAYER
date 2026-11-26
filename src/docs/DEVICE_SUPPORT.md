# Device support (file_browser / android_connect)

Goal: browse and play media from anything Windows can see, with no per-device code.

## Two kinds of device
1. **Drive-letter devices (mass storage):** SD/microSD readers, USB flash drives, external HDD/SSD, many cameras. Read with normal file APIs. Detect plug/unplug with WM_DEVICECHANGE; list with GetLogicalDrives. Handle FAT32, exFAT and NTFS.
2. **Portable devices (MTP/PTP):** Android phones/tablets and many cameras. No drive letter. Use the Windows Portable Devices (WPD) API. Phone must be set to "File transfer" (Android defaults to charging only).

## Provider design
`DeviceProvider` interface: list devices, list folders, read file stream, thumbnail, eject.
- `DriveLetterProvider`: mass storage
- `PortableDeviceProvider`: MTP/PTP via WPD
- `AndroidCompanionProvider`: optional Wi-Fi link via the companion app (android/companion)
The browser, gallery and player only talk to the interface.

## Playback from devices
- MTP seeking is limited and slow for large 4K/8K files: copy to a local cache (or buffer ahead) before playing; show progress.
- Read-only by default. Never write or delete without an explicit action.
- Camera media is usually in DCIM; include photo, RAW and video types the playback engine supports.
- Show device name, free space, and a safe-eject action.

## Testing
Test phone: model GN2200, Android 12. Also test: SD card, USB stick, external HDD, camera, FAT32/exFAT/NTFS, unplug during playback.
