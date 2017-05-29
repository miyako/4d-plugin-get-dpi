# 4d-plugin-get-dpi
Get screen DPI

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />

**Remarks**: Requires Windows 8.1 or later, OS X 10.7 or later.

Related proejct: https://github.com/miyako/4d-plugin-dpi-util

## Syntax

```
GET SCREEN DPI (dpi_x;dpi_y;screen)
```

Parameter|Type|Description
------------|------------|----
dpi_x|REAL|
dpi_y|REAL|
screen|LONGINT|screen number

[GetDpiForMonitor](https://msdn.microsoft.com/en-us/library/windows/desktop/dn280510(v=vs.85).aspx), [GetDeviceCaps](https://msdn.microsoft.com/en-us/library/windows/desktop/dd144877(v=vs.85).aspx) on Windows, ``NSScreen`` ``deviceDescription`` on macOS.

Examples
---

```
GET SCREEN DPI ($dpi_x;$dpi_y)

  //12in MacBook Retina
  //282, 282 (1440 x 900)
  //250.999984741211, 251.000015258789 default (1280 x 800)
  //200.999984741211, 201.000015258789 (1024 x 640)
  //226.000015258789, 226.000015258789 (1152 x 7620)
  //192, 192 VMWARE FUSION, Windows 10 (2560 x 1600, custom zoom rate)
```
