# 4d-plugin-get-dpi
Get screen DPI

Remarks
---

Requires Windows 8.1 or later, OS X 10.7 or later.

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|🆗|🆗|🆗|🆗|

Commands
---

```c
// --- DPI
GET_SCREEN_DPI
```

Examples
---

```
GET SCREEN DPI ($dpi_x;$dpi_y)

  //12in MacBook Retina
  //282, 282 (1440 x 900)
  //250.999984741211, 251.000015258789 default (1280 x 800)
  //200.999984741211, 201.000015258789 (1024 x 640)
  //226.000015258789, 226.000015258789 (1152 x 7620)
```
