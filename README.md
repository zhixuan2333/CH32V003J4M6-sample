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

## Samples

- GPIO
    - digital read with pullup
    - digital write (SDK)
    - digital write (register)
- stanby
    - AWU
    - GPIO EXTI
- EXTI
    - PIN Falling

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
