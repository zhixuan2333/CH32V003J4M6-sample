# CH32V003J4M6 Sample Code

## BOM
- [CH32V003J4M6](https://akizukidenshi.com/catalog/g/g118062/)
- [SOP8 to DIP8 Adapter](https://akizukidenshi.com/catalog/g/g105154/)
- [WCH-LinkE](https://akizukidenshi.com/catalog/g/g118065/)
- Below is optional
    - LED
    - Push Button
    - etc...

## Requirements

- [VSCode](https://code.visualstudio.com/)
- [PlatformIO](https://platformio.org/)
- [CH32V003 PlatformIO Platform](https://github.com/Community-PIO-CH32V/platform-ch32v)
- [WCH-LinkE Driver](https://www.wch-ic.com/downloads/CH32V003SW_PDF.html) (Windows only)


## pin out
![pinout](https://qiita-user-contents.imgix.net/https%3A%2F%2Fqiita-image-store.s3.ap-northeast-1.amazonaws.com%2F0%2F111210%2F18d5bc5e-325c-edfb-d6e4-cfa114412d27.png?ixlib=rb-4.0.0&auto=format&gif-q=60&q=75&s=ead8630cc17d4958d2bb588ed380d08a)
> from qitta user content

## Examples

This repository contains multiple example projects organized by category. Each example is in its own folder and has a corresponding PlatformIO environment.

### GPIO Examples

#### GPIO-Digital-Write-SDK
- **Environment:** `GPIO-Digital-Write-SDK`
- **Folder:** `src/GPIO/Digital-Write-SDK/`
- **Description:** Digital write example using SDK functions (GPIO_WriteBit)
- **Build:** `pio run -e GPIO-Digital-Write-SDK`
- **Upload:** `pio run -e GPIO-Digital-Write-SDK --target upload`

#### GPIO-Digital-Write-Register
- **Environment:** `GPIO-Digital-Write-Register`
- **Folder:** `src/GPIO/Digital-Write-Register/`
- **Description:** Digital write example using direct register manipulation
- **Build:** `pio run -e GPIO-Digital-Write-Register`
- **Upload:** `pio run -e GPIO-Digital-Write-Register --target upload`

#### GPIO-Digital-Read-Pullup
- **Environment:** `GPIO-Digital-Read-Pullup`
- **Folder:** `src/GPIO/Digital-Read-Pullup/`
- **Description:** Digital read example with internal pull-up resistor
- **Build:** `pio run -e GPIO-Digital-Read-Pullup`
- **Upload:** `pio run -e GPIO-Digital-Read-Pullup --target upload`

### EXTI Examples

#### EXTI-Pin-Falling
- **Environment:** `EXTI-Pin-Falling`
- **Folder:** `src/EXTI/Pin-Falling/`
- **Description:** External interrupt on falling edge with debouncing
- **Build:** `pio run -e EXTI-Pin-Falling`
- **Upload:** `pio run -e EXTI-Pin-Falling --target upload`

### Standby Examples

#### Standby-AWU
- **Environment:** `Standby-AWU`
- **Folder:** `src/Standby/AWU/`
- **Description:** Standby mode with Auto Wake-Up (AWU) timer
- **Build:** `pio run -e Standby-AWU`
- **Upload:** `pio run -e Standby-AWU --target upload`

#### Standby-GPIO-EXTI
- **Environment:** `Standby-GPIO-EXTI`
- **Folder:** `src/Standby/GPIO-EXTI/`
- **Description:** Standby mode with GPIO EXTI wake-up
- **Build:** `pio run -e Standby-GPIO-EXTI`
- **Upload:** `pio run -e Standby-GPIO-EXTI --target upload`

#### Standby-EXTI-User-Code
- **Environment:** `Standby-EXTI-User-Code`
- **Folder:** `src/Standby/EXTI-User-Code/`
- **Description:** Standby mode with EXTI interrupt handler (user code example)
- **Build:** `pio run -e Standby-EXTI-User-Code`
- **Upload:** `pio run -e Standby-EXTI-User-Code --target upload`

## How to Use

1. Clone this repository
2. Open in VSCode with PlatformIO extension installed
3. Select the example you want to build/upload using one of these methods:
   - **Method 1:** Click on the PlatformIO icon, then select the environment from the list
   - **Method 2:** Use the command line: `pio run -e <environment-name>`
4. Build and upload to your CH32V003J4M6 board

## Serial

I remap the UART TX to PA1(Pin 1).
Connect PA1 to a USB to RX pin.
- Baudrate: 115200

## Attention

### EXTI

If you wanna to use EXTI in cpp file, you need to declare the handler function like below.
[Reference](https://www.reddit.com/r/embedded/comments/1kujnyj/ch32v003_exti_isr_handler_registation_not_working/)

```cpp
extern "C" {void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));}
void EXTI7_0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    // you code here
    EXTI_ClearITPendingBit(EXTI_Line2); /* Clear Flag */
  }
}

```


## Reference


- [WCH](https://www.wch-ic.com/)
    - [Reference Manual](https://www.wch-ic.com/downloads/CH32V003RM_PDF.html)
    - [Datasheet](https://www.wch-ic.com/downloads/CH32V003DS0_PDF.html)
- [Community-PIO-CH32V/platform-ch32v](https://github.com/Community-PIO-CH32V/platform-ch32v)
- [wagiminator/Development-Boards](https://github.com/wagiminator/Development-Boards)
