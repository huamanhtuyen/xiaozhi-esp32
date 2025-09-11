/* Dòng 1: Include header <esp_log.h> từ ESP-IDF để sử dụng các hàm logging (ghi log) cho debug.
   Logging rất quan trọng trong nhúng vì không có console đầy đủ; log gửi qua UART hoặc WiFi.
   Các hàm như ESP_LOGI (info), ESP_LOGW (warning) dùng tag để phân loại. Nếu không include, không log được. */
#include <esp_log.h>
/* Dòng 2: Include <esp_err.h> cho hệ thống xử lý lỗi. Định nghĩa esp_err_t (enum mã lỗi như ESP_OK thành công, ESP_ERR_NO_MEM hết bộ nhớ).
   Trong nhúng, lỗi phần cứng phổ biến; dùng mã lỗi thay exception để tiết kiệm overhead. Macro ESP_ERROR_CHECK() dùng sau để kiểm tra. */
#include <esp_err.h>
/* Dòng 3: Include <nvs.h> cho Non-Volatile Storage (NVS), lưu trữ key-value trên flash memory.
   Giống database nhỏ, dùng lưu config (như WiFi SSID/password) bền vững qua reset. Dựa trên flash partition, giới hạn ghi ~100k cycles. */
#include <nvs.h>
/* Dòng 4: Include <nvs_flash.h> để khởi tạo NVS trên flash. Cung cấp nvs_flash_init() để mount partition NVS.
   Flash ESP32 chia partition (qua CSV file); NVS ở partition "nvs". Xử lý low-level flash access, dễ corrupt nếu power loss. */
#include <nvs_flash.h>
/* Dòng 5: Include <driver/gpio.h> cho GPIO driver. GPIO là chân pin để kết nối hardware (LED, sensor).
   Cung cấp hàm config direction (input/output), set level (high/low). ESP32 có ~40 GPIO, một số dành riêng cho flash. Nền tảng tương tác phần cứng. */
#include <driver/gpio.h>
/* Dòng 6: Include <esp_event.h> cho event loop system. Xử lý asynchronous events (WiFi connect, button press).
   Event loop dựa trên FreeRTOS queue, cho multitasking không block. Default loop dùng cho WiFi/IP events. */
#include <esp_event.h>

/* Dòng 8: Include header custom "application.h" (local project). Định nghĩa class Application, có lẽ singleton quản lý app (WiFi, audio, display).
   Dấu "" tìm file trong project dir (main/). OOP C++ để tổ chức code modular trong nhúng phức tạp. */
#include "application.h"
/* Dòng 9: Include "system_info.h" custom. Định nghĩa SystemInfo để lấy info hệ thống (chip ID, version, memory).
   Dùng detect hardware variant (ESP32-S3, etc.) để config GPIO/display khác nhau. */
#include "system_info.h>

/* Dòng 11: Định nghĩa macro TAG = "main" cho logging. Preprocessor thay thế TAG bằng "main" lúc compile, tiết kiệm bộ nhớ.
   Dùng trong ESP_LOGW(TAG, msg) để prefix log [main], giúp filter debug theo component. */
#define TAG "main"

/* Dòng 13: Khai báo hàm app_main() là entry point. extern "C" dùng C linkage (không name mangling C++), vì ESP-IDF gọi tên chính xác app_main sau boot.
   Thay vì main() chuẩn; chạy sau init hardware cơ bản (clock, memory). Void: không param, không return (app chạy mãi). */
extern "C" void app_main(void)
/* Dòng 14: Mở body hàm app_main(). */
{
    /* Dòng 15: Comment gốc giải thích init event loop. */
    // Initialize the default event loop
/* Dòng 16: Tạo default event loop bằng esp_event_loop_create_default(). ESP_ERROR_CHECK() kiểm tra return: nếu != ESP_OK, log lỗi và abort().
   Event loop xử lý events không block, dựa trên FreeRTOS; cần cho WiFi events, tránh app "đơ". */
    ESP_ERROR_CHECK(esp_event_loop_create_default());

/* Dòng 18: Comment gốc: Init NVS cho WiFi config. */
    // Initialize NVS flash for WiFi configuration
/* Dòng 19: Gọi nvs_flash_init() để mount NVS, lưu kết quả vào ret (esp_err_t). Nếu fail (partition hỏng), ret != ESP_OK. */
    esp_err_t ret = nvs_flash_init();
/* Dòng 20: Kiểm tra lỗi cụ thể: hết trang free hoặc version NVS mới (sau OTA). Nếu đúng, fix bằng erase. Defensive programming cho flash corrupt. */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
/* Dòng 21: Log warning khi erase NVS. ESP_LOGW in ra UART/console với level WARNING, prefix [main]. Giúp debug vấn đề flash. */
        ESP_LOGW(TAG, "Erasing NVS flash to fix corruption");
/* Dòng 22: Xóa toàn bộ NVS partition bằng nvs_flash_erase(). Kiểm tra lỗi; mất data cũ (config WiFi cần setup lại), mất vài giây. */
        ESP_ERROR_CHECK(nvs_flash_erase());
/* Dòng 23: Thử init NVS lại sau erase, cập nhật ret. Sau erase, thường thành công trừ hardware hỏng. */
        ret = nvs_flash_init();
    }
/* Dòng 25: Kiểm tra final ret. Nếu vẫn fail, crash với log. Đảm bảo NVS sẵn sàng trước khi dùng cho config. */
    ESP_ERROR_CHECK(ret);

/* Dòng 27: Comment gốc: Khởi chạy app. */
    // Launch the application
/* Dòng 28: Lấy reference (&) đến singleton Application bằng GetInstance(). auto suy luận kiểu (C++11). Singleton: một instance duy nhất quản lý app. */
    auto& app = Application::GetInstance();
/* Dòng 29: Gọi Start() để init components (WiFi, display, tasks FreeRTOS?). Setup events, load NVS config. */
    app.Start();
/* Dòng 30: Chạy MainEventLoop(): vòng lặp chính xử lý events mãi mãi (poll WiFi, UI, input). App kết thúc chỉ khi reset. */
    app.MainEventLoop();
/* Dòng 31: Đóng body app_main(). Kết thúc file; chương trình chạy vô hạn từ đây. */
}
