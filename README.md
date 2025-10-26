# CH32V003J4M6 Sample Code

## Hardware
- [CH32V003J4M6](https://akizukidenshi.com/catalog/g/g118062/)
- [SOP8 to DIP8 Adapter](https://akizukidenshi.com/catalog/g/g105154/)
- [WCH-LinkE](https://akizukidenshi.com/catalog/g/g118065/)

## Software
- [VSCode](https://code.visualstudio.com/) + [PlatformIO](https://platformio.org/)
- [CH32V003 Platform](https://github.com/Community-PIO-CH32V/platform-ch32v)
- [WCH-LinkE Driver](https://www.wch-ic.com/downloads/CH32V003SW_PDF.html) (Windows only)

## Pinout
![pinout](https://qiita-user-contents.imgix.net/https%3A%2F%2Fqiita-image-store.s3.ap-northeast-1.amazonaws.com%2F0%2F111210%2F18d5bc5e-325c-edfb-d6e4-cfa114412d27.png?ixlib=rb-4.0.0&auto=format&gif-q=60&q=75&s=ead8630cc17d4958d2bb588ed380d08a)

## Examples

| Example | Environment | Description |
|---------|-------------|-------------|
| **GPIO/Digital-Write-SDK** | `GPIO-Digital-Write-SDK` | Digital write using SDK functions |
| **GPIO/Digital-Write-Register** | `GPIO-Digital-Write-Register` | Digital write using registers |
| **GPIO/Digital-Read-Pullup** | `GPIO-Digital-Read-Pullup` | Digital read with pull-up resistor |
| **EXTI/Pin-Falling** | `EXTI-Pin-Falling` | External interrupt on falling edge |
| **Standby/AWU** | `Standby-AWU` | Standby mode with auto wake-up timer |
| **Standby/GPIO-EXTI** | `Standby-GPIO-EXTI` | Standby mode with GPIO EXTI wake-up |
| **Standby/EXTI-User-Code** | `Standby-EXTI-User-Code` | Standby with EXTI interrupt handler |
| **UART/DMA** | `UART-DMA` | UART communication using DMA |

## Usage

```bash
# Build example
pio run -e GPIO-Digital-Write-SDK

# Upload to board
pio run -e GPIO-Digital-Write-SDK --target upload
```

Or select the environment in PlatformIO IDE.

## Notes

**Serial:** UART TX remapped to PA1 (Pin 1), baudrate 115200

**EXTI in C++:** Declare handler with `extern "C"`:
```cpp
extern "C" {void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));}
void EXTI7_0_IRQHandler(void) {
  if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
    // your code here
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}
```

## Reference
- [WCH CH32V003 Reference Manual](https://www.wch-ic.com/downloads/CH32V003RM_PDF.html)
- [WCH CH32V003 Datasheet](https://www.wch-ic.com/downloads/CH32V003DS0_PDF.html)
- [Community PlatformIO Platform](https://github.com/Community-PIO-CH32V/platform-ch32v)
- [wagiminator Development Boards](https://github.com/wagiminator/Development-Boards)
