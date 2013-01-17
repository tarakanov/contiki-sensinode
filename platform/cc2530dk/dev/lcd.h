#ifndef __LCD_H__
#define __LCD_H__

void lcd_init(void);
void lcd_control(uint8_t cmd);
void lcd_clear(void);
void lcd_writechar(uint8_t line, uint8_t col, char text);
void lcd_writeline(uint8_t line, char *text);
void lcd_setcontrast(uint8_t value);
#endif /* __LCD_H__ */	
