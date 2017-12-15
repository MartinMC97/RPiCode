#Temperature and humidity report using DHT11 sensor and IFTTT
import requests
import Adafruit_DHT as DHT
import json
import os

sensor = DHT.DHT11
pin = 14

humidity, temperature = DHT.read_retry(sensor, pin)
temp_str = str(temperature) + " ℃"
humid_str = str(humidity) + " %"

result = {"value1": temp_str, "value2": humid_str}
url = "https://maker.ifttt.com/trigger/DHT_Sensor_Read/with/key/($key)"

r = requests.post(url, json = result)
#os.system("curl -X POST -H \"Content-Type: application/json\" -d "+ str(result) +" https://maker.ifttt.com/trigger/DHT_Sensor_Read/with/key/($key)")

