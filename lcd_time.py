#A Real time clock using LCD1602 display
import Adafruit_CharLCD as LCD
import time

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
						   
try:
	while(1):
		if(int(time.strftime("%S")) == 0):
		#list = time.ctime().split(' ') #['Wed', 'Apr', '26', '18:26:47', '2017']
			lcd.clear()
			lcd.message(time.strftime(" %Y-%m-%d %a"))
			lcd.message('\n')
			lcd.message(time.strftime("     %H:%M"))
			#time.sleep(1)
			time.sleep(59)
except KeyboardInterrupt:
	pass

	
lcd.clear()