# Công Cụ Flash/Web End Flash Firmware (Không Cần Môi Trường Phát Triển IDF)

## Cách 1: Flash Phần Mềm Trên Máy Tính (Không Cần Môi Trường IDF)

Hiện tại firmware Xiao Zhi AI phù hợp với các board phát triển chip chủ ESP32 series, cụ thể vui lòng tham khảo bảng đối chiếu tải firmware.

**Lưu Ý:** 1) v0.X.X_ML307.zip là phiên bản firmware 4G, phiên bản WiFi mặc định vui lòng tải v0.X.X_bread-compact-wifi.zip (x.x đại diện số phiên bản).  
2) Tài liệu này là ví dụ hoạt động flash firmware, khi flash khuyên nên flash phiên bản firmware mới nhất.

Cài đặt công cụ tải Flash: https://www.espressif.com.cn/zh-hans/support/download/other-tools.

Hoặc trực tiếp tải gói nén bên dưới giải nén mở ra chính là công cụ tải:

Kết nối USB JTAG/serial của board phát triển ESP32 S3 với máy chủ, chạy công cụ tải Flash, sử dụng chế độ UART để flash merged-binary.bin đã giải nén vào địa chỉ 0x0.

### Chuẩn Bị Công Việc

Trên hệ thống Windows, hiện tại công cụ tải/flash khuyến nghị phiên bản Flash download_tool 3.9.7, các phiên bản khác miễn không quá cũ cũng có thể sử dụng.

Sau khi tải giải nén flash_download_tool_3.9.7_1.zip vào thư mục chỉ định trên ổ cứng là được, không cần cài đặt, vào thư mục trực tiếp double-click flash_download_tool_3.9.7.exe là có thể chạy.

**Lưu ý**, công cụ flash cũng đừng đặt trong thư mục tiếng Trung, nếu không có thể không tải được file.

### Tải Firmware

(1) Tải và giải nén

Click mở danh sách firmware: v1.5.5 Phiên bản firmware mới nhất terminal Xiao Zhi AI tải

**Lưu ý:** Sau khi tải lưu trên ổ cứng local máy tính của tôi, đường dẫn khuyên không chứa ký tự tiếng Trung, nếu không có thể không tải flash được.

Hình dưới chỉ là ví dụ tham khảo, khi hoạt động cụ thể vui lòng tải phiên bản firmware mới nhất.

Vui lòng theo tình huống board phát triển và module ngoại vi bạn sử dụng, chọn phiên bản tương ứng tải firmware vào ổ cứng local máy tính.

**Lưu ý:** bread đầu là firmware breadboard (tự mua board phát triển ESP32s3-WROOM-1/1U-N16R8 và module lắp ráp, theo sơ đồ kết nối, sử dụng breadboard, dây dupont hoặc tự hàn), mặc định chọn phiên bản WIFI, nếu lắp thêm module ML307R (AT) 4G, vui lòng chọn phiên bản ML307.

Sản phẩm breadboard wifi tương ứng: vx.x.x_bread-compact-wifi.zip 

Phiên bản 4G breadboard tương ứng vx.x.x_bread-compact-ml307.zip (vx.x.x đại diện số phiên bản ví dụ v1.5.5)

Firmware tương ứng board phát triển/sản phẩm hiển thị tiếng Trung là pinyin hoặc tiếng Anh tương ứng (vui lòng chú ý), vui lòng tham khảo hình dưới:

| Số thứ tự | Loại board phát triển/sản phẩm | Gói chương trình BIN firmware (vx.x.x đại diện số phiên bản ví dụ v1.5.5) |
| ---- | ---- | ---- |
| 1 | Breadboard mới kết nối (WIFI) 0.91OLED (44 hoặc 42 chân board phát triển esp32s3-wroom-1) BOARD_TYPE_BREAD_COMPACT_WIFI | vx.x.x_bread-compact-wifi.zip |
| 2 | Breadboard mới kết nối (WIFI) +LCD (44 hoặc 42 chân board phát triển esp32s3-wroom-1) BOARD_TYPE_BREAD_COMPACT_WIFI_LCD | Vui lòng tự biên dịch firmware theo độ phân giải màn hình LCD |
| 3 | Breadboard mới kết nối (ML307 AT) BOARD_TYPE_BREAD_COMPACT_ML307 | vx.x.x_bread-compact-ml307.zip |
| 4 | ESP BOX 3 (Le Xin) BOARD_TYPE_ESP_BOX_3 | vx.x.x_esp-box-3.zip |
| 5 | Kevin Box 1 BOARD_TYPE_KEVIN_BOX_1 | vx.x.x_kevin-box-1.zip |
| 6 | Kevin Box 2 BOARD_TYPE_KEVIN_BOX_2 | vx.x.x_kevin-box-2.zip |
| 7 | Kevin C3 BOARD_TYPE_KEVIN_C3 | vx.x.x_kevin-c3.zip |
| 8 | Board phát triển Kevin SP V3 BOARD_TYPE_KEVIN_SP_V3_DEV | vx.x.x_kevin-sp-v3.zip |
| 9 | Board phát triển ESP32-S3 Thực Chiến LiChuang BOARD_TYPE_LICHUANG_DEV | vx.x.x_lichuang-dev.zip |
| 10 | Board phát triển ESP32-C3 Thực Chiến LiChuang BOARD_TYPE_LICHUANG_C3 | vx.x.x_lichuang-c3-dev.zip |
| 11 | Nút Thần Kỳ Magiclick_2.4 BOARD_TYPE_MAGICLICK_2P4 | vx.x.x_magiclick-2p4.zip |
| 12 | Nút Thần Kỳ Magiclick_C3 BOARD_TYPE_MAGICLICK C3 | vx.x.x_magiclick-c3.zip |
| 13 | M5Stack CoreS3 BOARD_TYPE_M5STACK CORE S3 | vx.x.x_m5stack-core-s3.zip |
| 14 | AtomS3 + Echo Base BOARD_TYPE_ATOMS3_ECHO_BASE | vx.x.x_atoms3-echo-base.zip |
| 15 | AtomS3R + Echo Base BOARDTYPE_ATOMS3R_ECHO_BASE | vx.x.x_atoms3r-echo-base.zip |
| 16 | AtomMatrix+ Echo Base BOARDTYPE ATOMMATRIX ECHO BASE | vx.x.x_atommatrix-echo-base.zip |
| 17 | Xa Ca Mini C3 BOARD TYPE_XMINI_C3 | vx.x.x_xmini-c3.zip |
| 18 | Board phát triển ESP32S3 KORV02 V3 BOARDTYPEESP32S3_KORV02_V3 | vx.x.x_esp32s3-korvo2-v3.zip |
| 19 | Board phát triển ESP-SparkBot (xe tăng) BOARD_TYPE_ESP SPARKBOT | vx.x.x_esp-sparkbot.zip |
| 20 | Waveshare ESP32-S3-Touch-AMOLED-1.8 (Vi Tuyết) BOARD_TYPE_ESP32S3_Touch_AMOLED_1_8 | vx.x.x_esp32