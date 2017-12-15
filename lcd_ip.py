#Display IP address on LCD1602
import Adafruit_CharLCD as LCD
from requests import get

lcd_rs        = 27
lcd_en        = 22
lcd_d4        = 25
lcd_d5        = 24
lcd_d6        = 23
lcd_d7        = 18

lcd_columns = 16
lcd_rows    = 2

lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7,
                           lcd_columns, lcd_rows)
				
ip = get('https://api.ipify.org').text

lcd.message("Current IP:\n" + ip)