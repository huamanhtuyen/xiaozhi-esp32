# Hướng dẫn Phát triển Bảng Mạch Tùy Chỉnh

Hướng dẫn này giới thiệu cách tùy chỉnh chương trình khởi tạo cho một bảng mạch phát triển mới cho dự án robot trò chuyện AI Xiao Zhi. Xiao Zhi AI hỗ trợ hơn 70 bảng mạch phát triển ESP32 series, mã khởi tạo của mỗi bảng mạch được đặt trong thư mục tương ứng.

## Lưu Ý Quan Trọng

> **Cảnh báo**: Đối với bảng mạch tùy chỉnh, khi cấu hình IO khác với bảng mạch gốc, tuyệt đối không được ghi đè trực tiếp cấu hình bảng mạch gốc để biên dịch firmware. Phải tạo loại bảng mạch mới, hoặc qua cấu hình builds trong file config.json với name khác nhau và macro sdkconfig để phân biệt. Sử dụng `python scripts/release.py [tên thư mục bảng mạch]` để biên dịch và đóng gói firmware.
>
> Nếu ghi đè trực tiếp cấu hình gốc, khi OTA nâng cấp trong tương lai, firmware tùy chỉnh của bạn có thể bị firmware chuẩn của bảng mạch gốc ghi đè, dẫn đến thiết bị không hoạt động bình thường. Mỗi bảng mạch có định danh duy nhất và kênh nâng cấp firmware tương ứng, việc giữ tính duy nhất của định danh bảng mạch rất quan trọng.

## Cấu Trúc Thư Mục

Cấu trúc thư mục của mỗi bảng mạch thường bao gồm các file sau:

- `xxx_board.cc` - Mã khởi tạo cấp bảng mạch chính, triển khai khởi tạo và chức năng liên quan đến bảng mạch
- `config.h` - File cấu hình cấp bảng mạch, định nghĩa ánh xạ chân phần cứng và các mục cấu hình khác
- `config.json` - Cấu hình biên dịch, chỉ định chip mục tiêu và các tùy chọn biên dịch đặc biệt
- `README.md` - Tài liệu giải thích liên quan đến bảng mạch

## Các Bước Tùy Chỉnh Bảng Mạch

### 1. Tạo Thư Mục Bảng Mạch Mới

Trước tiên tạo một thư mục mới trong thư mục `boards/`, ví dụ `my-custom-board/`:

```bash
mkdir main/boards/my-custom-board
```

### 2. Tạo File Cấu Hình

#### config.h

Trong `config.h` định nghĩa tất cả cấu hình phần cứng, bao gồm:

- Tỷ lệ lấy mẫu âm thanh và cấu hình chân I2S
- Địa chỉ chip codec âm thanh và cấu hình chân I2C
- Cấu hình chân nút bấm và LED
- Tham số màn hình hiển thị và cấu hình chân

Tham khảo ví dụ (từ lichuang-c3-dev):

```c
#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

// Cấu hình âm thanh
#define AUDIO_INPUT_SAMPLE_RATE  24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

#define AUDIO_I2S_GPIO_MCLK GPIO_NUM_10
#define AUDIO_I2S_GPIO_WS   GPIO_NUM_12
#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_8
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_7
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_11

#define AUDIO_CODEC_PA_PIN       GPIO_NUM_13
#define AUDIO_CODEC_I2C_SDA_PIN  GPIO_NUM_0
#define AUDIO_CODEC_I2C_SCL_PIN  GPIO_NUM_1
#define AUDIO_CODEC_ES8311_ADDR  ES8311_CODEC_DEFAULT_ADDR

// Cấu hình nút bấm
#define BOOT_BUTTON_GPIO        GPIO_NUM_9

// Cấu hình màn hình hiển thị
#define DISPLAY_SPI_SCK_PIN     GPIO_NUM_3
#define DISPLAY_SPI_MOSI_PIN    GPIO_NUM_5
#define DISPLAY_DC_PIN          GPIO_NUM_6
#define DISPLAY_SPI_CS_PIN      GPIO_NUM_4

#define DISPLAY_WIDTH   320
#define DISPLAY_HEIGHT  240
#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y false
#define DISPLAY_SWAP_XY true

#define DISPLAY_OFFSET_X  0
#define DISPLAY_OFFSET_Y  0

#define DISPLAY_BACKLIGHT_PIN GPIO_NUM_2
#define DISPLAY_BACKLIGHT_OUTPUT_INVERT true

#endif // _BOARD_CONFIG_H_
```

#### config.json

Trong `config.json` định nghĩa cấu hình biên dịch:

```json
{
    "target": "esp32s3",  // Loại chip mục tiêu: esp32, esp32s3, esp32c3 v.v.
    "builds": [
        {
            "name": "my-custom-board",  // Tên bảng mạch
            "sdkconfig_append": [
                // Cấu hình biên dịch bổ sung cần thiết
                "CONFIG_ESPTOOLPY_FLASHSIZE_8MB=y",
                "CONFIG_PARTITION_TABLE_CUSTOM_FILENAME=\"partitions/v2/8m.csv\""
            ]
        }
    ]
}
```

### 3. Viết Mã Khởi Tạo Cấp Bảng Mạch

Tạo file `my_custom_board.cc`, triển khai tất cả logic khởi tạo của bảng mạch.

Định nghĩa lớp bảng mạch cơ bản bao gồm các phần sau:

1. **Định nghĩa lớp**: Kế thừa từ `WifiBoard` hoặc `Ml307Board`
2. **Hàm khởi tạo**: Bao gồm khởi tạo I2C, màn hình hiển thị, nút bấm, IoT v.v.
3. **Ghi đè hàm ảo**: Như `GetAudioCodec()`, `GetDisplay()`, `GetBacklight()` v.v.
4. **Đăng ký bảng mạch**: Sử dụng macro `DECLARE_BOARD` để đăng ký bảng mạch

```cpp
#include "wifi_board.h"
#include "codecs/es8311_audio_codec.h"
#include "display/lcd_display.h"
#include "application.h"
#include "button.h"
#include "config.h"
#include "mcp_server.h"

#include <esp_log.h>
#include <driver/i2c_master.h>
#include <driver/spi_common.h>

#define TAG "MyCustomBoard"

class MyCustomBoard : public WifiBoard {
private:
    i2c_master_bus_handle_t codec_i2c_bus_;
    Button boot_button_;
    LcdDisplay* display_;

    // Khởi tạo I2C
    void InitializeI2c() {
        i2c_master_bus_config_t i2c_bus_cfg = {
            .i2c_port = I2C_NUM_0,
            .sda_io_num = AUDIO_CODEC_I2C_SDA_PIN,
            .scl_io_num = AUDIO_CODEC_I2C_SCL_PIN,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .intr_priority = 0,
            .trans_queue_depth = 0,
            .flags = {
                .enable_internal_pullup = 1,
            },
        };
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &codec_i2c_bus_));
    }

    // Khởi tạo SPI (dùng cho màn hình hiển thị)
    void InitializeSpi() {
        spi_bus_config_t buscfg = {};
        buscfg.mosi_io_num = DISPLAY_SPI_MOSI_PIN;
        buscfg.miso_io_num = GPIO_NUM_NC;
        buscfg.sclk_io_num = DISPLAY_SPI_SCK_PIN;
        buscfg.quadwp_io_num = GPIO_NUM_NC;
        buscfg.quadhd_io_num = GPIO_NUM_NC;
        buscfg.max_transfer_sz = DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t);
        ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));
    }

    // Khởi tạo nút bấm
    void InitializeButtons() {
        boot_button_.OnClick([this]() {
            auto& app = Application::GetInstance();
            if (app.GetDeviceState() == kDeviceStateStarting && !WifiStation::GetInstance().IsConnected()) {
                ResetWifiConfiguration();
            }
            app.ToggleChatState();
        });
    }

    // Khởi tạo màn hình hiển thị (lấy ST7789 làm ví dụ)
    void InitializeDisplay() {
        esp_lcd_panel_io_handle_t panel_io = nullptr;
        esp_lcd_panel_handle_t panel = nullptr;
        
        esp_lcd_panel_io_spi_config_t io_config = {};
        io_config.cs_gpio_num = DISPLAY_SPI_CS_PIN;
        io_config.dc_gpio_num = DISPLAY_DC_PIN;
        io_config.spi_mode = 2;
        io_config.pclk_hz = 80 * 1000 * 1000;
        io_config.trans_queue_depth = 10;
        io_config.lcd_cmd_bits = 8;
        io_config.lcd_param_bits = 8;
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(SPI2_HOST, &io_config, &panel_io));

        esp_lcd_panel_dev_config_t panel_config = {};
        panel_config.reset_gpio_num = GPIO_NUM_NC;
        panel_config.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB;
        panel_config.bits_per_pixel = 16;
        ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(panel_io, &panel_config, &panel));
        
        esp_lcd_panel_reset(panel);
        esp_lcd_panel_init(panel);
        esp_lcd_panel_invert_color(panel, true);
        esp_lcd_panel_swap_xy(panel, DISPLAY_SWAP_XY);
        esp_lcd_panel_mirror(panel, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y);
        
        // Tạo đối tượng màn hình hiển thị
        display_ = new SpiLcdDisplay(panel_io, panel,
                                    DISPLAY_WIDTH, DISPLAY_HEIGHT, 
                                    DISPLAY_OFFSET_X, DISPLAY_OFFSET_Y, 
                                    DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y, DISPLAY_SWAP_XY);
    }

    // Khởi tạo MCP Tools
    void InitializeTools() {
        // Tham khảo tài liệu MCP
    }

public:
    // Constructor
    MyCustomBoard() : boot_button_(BOOT_BUTTON_GPIO) {
        InitializeI2c();
        InitializeSpi();
        InitializeDisplay();
        InitializeButtons();
        InitializeTools();
        GetBacklight()->SetBrightness(100);
    }

    // Lấy codec âm thanh
    virtual AudioCodec* GetAudioCodec() override {
        static Es8311AudioCodec audio_codec(
            codec_i2c_bus_, 
            I2C_NUM_0, 
            AUDIO_INPUT_SAMPLE_RATE, 
            AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_GPIO_MCLK, 
            AUDIO_I2S_GPIO_BCLK, 
            AUDIO_I2S_GPIO_WS, 
            AUDIO_I2S_GPIO_DOUT, 
            AUDIO_I2S_GPIO_DIN,
            AUDIO_CODEC_PA_PIN, 
            AUDIO_CODEC_ES8311_ADDR);
        return &audio_codec;
    }

    // Lấy màn hình hiển thị
    virtual Display* GetDisplay() override {
        return display_;
    }
    
    // Lấy điều khiển backlight
    virtual Backlight* GetBacklight() override {
        static PwmBacklight backlight(DISPLAY_BACKLIGHT_PIN, DISPLAY_BACKLIGHT_OUTPUT_INVERT);
        return &backlight;
    }
};

// Đăng ký bảng mạch
DECLARE_BOARD(MyCustomBoard);
```

### 4. Tạo README.md

Trong README.md giải thích đặc tính bảng mạch, yêu cầu phần cứng, các bước biên dịch và flash:

## Các Thành Phần Bảng Mạch Phổ Biến

### 1. Màn Hình Hiển Thị

Dự án hỗ trợ nhiều driver màn hình hiển thị, bao gồm:
- ST7789 (SPI)
- ILI9341 (SPI)
- SH8601 (QSPI)
- v.v...

### 2. Codec Âm Thanh

Các codec được hỗ trợ bao gồm:
- ES8311 (phổ biến)
- ES7210 (mảng microphone)
- AW88298 (công suất khuếch đại)
- v.v...

### 3. Quản Lý Nguồn

Một số bảng mạch sử dụng chip quản lý nguồn:
- AXP2101
- Các PMIC khác có sẵn

### 4. Điều Khiển Thiết Bị MCP

Có thể thêm các công cụ MCP khác nhau để AI có thể sử dụng:
- Speaker (điều khiển loa)
- Screen (điều chỉnh độ sáng màn hình)
- Battery (đọc mức pin)
- Light (điều khiển đèn)
- v.v...

## Mối Quan Hệ Kế Thừa Lớp Bảng Mạch

- `Board` - Lớp cấp bảng mạch cơ bản
  - `WifiBoard` - Bảng mạch kết nối Wi-Fi
  - `Ml307Board` - Bảng mạch sử dụng module 4G
  - `DualNetworkBoard` - Bảng mạch hỗ trợ chuyển đổi giữa Wi-Fi và 4G

## Mẹo Phát Triển

1. **Tham khảo bảng mạch tương tự**: Nếu bảng mạch mới của bạn tương tự với bảng mạch hiện có, có thể tham khảo triển khai hiện có
2. **Debug từng bước**: Trước tiên triển khai chức năng cơ bản (như hiển thị), sau đó thêm chức năng phức tạp hơn (như âm thanh)
3. **Ánh xạ chân**: Đảm bảo cấu hình đúng tất cả ánh xạ chân trong config.h
4. **Kiểm tra tính tương thích phần cứng**: Xác nhận tính tương thích của tất cả chip và driver

## Các Vấn Đề Có Thể Gặp Phải

1. **Màn hình hiển thị bất thường**: Kiểm tra cấu hình SPI, thiết lập gương và thiết lập đảo màu
2. **Không có đầu ra âm thanh**: Kiểm tra cấu hình I2S, chân kích hoạt PA và địa chỉ codec
3. **Không thể kết nối mạng**: Kiểm tra thông tin xác thực Wi-Fi và cấu hình mạng
4. **Không thể giao tiếp với máy chủ**: Kiểm tra cấu hình MQTT hoặc WebSocket

## Tài Liệu Tham Khảo

- Tài liệu ESP-IDF: https://docs.espressif.com/projects/esp-idf/
- Tài liệu LVGL: https://docs.lvgl.io/
- Tài liệu ESP-SR: https://github.com/espressif/esp-sr