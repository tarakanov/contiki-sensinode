#include "contiki-conf.h"
#include "dev/lcd.h"
#include "cc253x.h"
#include "dev/uart1.h"
#include "sys/clock.h"

#define LCD_MODE_PIN P0_0
#define LCD_FLASH_RESET_PIN P0_1
#define LCD_CS_PIN   P1_2
#define LCD_MODE_MASK 0x01
#define LCD_FLASH_RESET_MASK 0x02
#define LCD_CS_MASK   0x04


#define SET_DDRAM_ADDR(charIndex)       lcd_control(0x80 | (charIndex))

#define LCD_DO_CONTROL()                LCD_MODE_PIN = 0x00
#define LCD_DO_WRITE()                  LCD_MODE_PIN = 0x01
#define SPI_BEGIN()                     LCD_CS_PIN = 0x00
#define SPI_END()                       LCD_CS_PIN = 0x01
#define LCD_ACTIVATE_RESET()            LCD_FLASH_RESET_PIN = 0x00
#define LCD_RELEASE_RESET()             LCD_FLASH_RESET_PIN = 0x01

#define LCD_MAX_LINE_COUNT              3
#define LCD_MAX_LINE_LENGTH             16
#define LCD_MAX_BUF                     25

/* Function Set */
#define CGROM                           0x00
#define CGRAM                           0x01
#define COM_FORWARD                     0x00
#define COM_BACKWARD                    0x02
#define TWO_LINE                        0x00
#define THREE_LINE                      0x04
#define FUNCTION_SET(options)           lcd_control(0x10 | (options))
/* Set ICONRAM address */
#define CONTRAST_CTRL_REGISTER          0x10
#define SET_ICONRAM_ADDR(addr)          lcd_control(0x40 | (addr))

/*---------------------------------------------------------------------------*/
void
lcd_init(void)
{
  P0SEL &= ~LCD_MODE_MASK;
  P0DIR |= LCD_MODE_MASK;
  P0SEL &= ~LCD_FLASH_RESET_MASK;
  P0DIR |= LCD_FLASH_RESET_MASK;
  P1SEL &= ~LCD_CS_MASK;
  P1DIR |= LCD_CS_MASK;
  LCD_CS_PIN = 0x01;
  LCD_FLASH_RESET_PIN = 0x01;
  LCD_MODE_PIN = 0x01;

  LCD_ACTIVATE_RESET();
  clock_delay(15000);
  LCD_RELEASE_RESET();
  clock_delay(15);

  FUNCTION_SET(CGRAM | COM_FORWARD | THREE_LINE);

  lcd_setcontrast(15);
  lcd_clear();

}
/*---------------------------------------------------------------------------*/
void
lcd_control(uint8_t cmd)
{
  SPI_BEGIN();
  LCD_DO_CONTROL();
  spi1_writeb(cmd);
  SPI_END();
}
/*---------------------------------------------------------------------------*/
void lcd_write(uint8_t data)
{
  SPI_BEGIN();
  LCD_DO_WRITE();
  spi1_writeb(data);
  SPI_END();
}
/*---------------------------------------------------------------------------*/
void lcd_clear(void)
{
  uint8_t n;
  SET_DDRAM_ADDR(0x00);
  for (n = 0; n < (LCD_MAX_LINE_COUNT * LCD_MAX_LINE_LENGTH); n++)
  {
    lcd_write(' ');
  }
}
/*---------------------------------------------------------------------------*/
void lcd_writechar(uint8_t line, uint8_t col, char text)
{
  SET_DDRAM_ADDR((line-1) * LCD_MAX_LINE_LENGTH + col);
  lcd_write(text);
}
/*---------------------------------------------------------------------------*/
void lcd_writeline(uint8_t line, char *text)
{
  uint8_t count;
  uint8_t totallength = (uint8_t)strlen(text);
  for (count = 0; count < totallength; count++) {
    lcd_writechar(line, count, (*(text++)));
  }
  for(count=totallength; count<LCD_MAX_LINE_LENGTH;count++)
  {
    lcd_writechar(line, count, ' ');
  }
}
/*---------------------------------------------------------------------------*/
void lcd_setcontrast(uint8_t value)
{
  SET_ICONRAM_ADDR(CONTRAST_CTRL_REGISTER);
  lcd_write(value);
}
/*---------------------------------------------------------------------------*/

