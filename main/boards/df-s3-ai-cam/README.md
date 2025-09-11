# Mô Đun Camera Thông Minh AI ESP32-S3 DFRobot

## Giới Thiệu

ESP32-S3 AI CAM là mô đun camera thông minh được thiết kế dựa trên chip ESP32-S3, chuyên biệt cho xử lý video hình ảnh và tương tác giọng nói, phù hợp cho các dự án AI như giám sát video, nhận dạng hình ảnh biên, đối thoại giọng nói v.v.
![](https://ws.dfrobot.com.cn/FsTrGbrX2NZAwzWS8OSQGOGikuYA)

[Click để xem giới thiệu chi tiết](https://wiki.dfrobot.com.cn/SKU_DFR1154_ESP32_S3_AI_CAM)

[Click để xem demo chức năng thị giác](https://www.bilibili.com/video/BV1ktjSzNEUU/)

# Tính Năng
* Sử dụng microphone PDM
* Camera OV3660 tích hợp trên board

## Cấu Hình Nút Bấm
* BOOT: Nhấn ngắn - Ngắt/Đánh thức

## Lệnh Cấu Hình Biên Dịch

**Cấu hình mục tiêu biên dịch là ESP32S3:**

```bash
idf.py set-target esp32s3
```

**Mở menuconfig:**

```bash
idf.py menuconfig
```

**Chọn board:**

```
Xiaozhi Assistant -> Board Type -> Mô Đun Camera Thông Minh AI ESP32-S3 DFRobot
```

**Sửa đổi cấu hình psram:**

```
Component config -> ESP PSRAM -> SPI RAM config -> Mode (QUAD/OCT) -> Octal Mode PSRAM
```

**Sửa đổi công suất phát WiFi là 10:**

```
Component config -> PHY -> (10)Max WiFi TX power (dBm)
```

**Biên dịch:**

```bash
idf.py build