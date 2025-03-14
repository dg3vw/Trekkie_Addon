# Trekkie_Addon - USS Enterprise SAO

my contribution to Hackaday Europe 2025 Badge SAO

uss enterprise

compatible to 2024 Supercon 8 prototyp I2C prototyping pedal add on, using CH32v003 (https://github.com/Hack-a-Day/2024-Supercon-8-Add-On-Badge/blob/main/hardware/sao/i2c_proto_petal/sao_proto.pdf) 

I added a few leds, two switches and a buzzer. Every LED is connected to a gpio separately.



### PINOUT: 
* PC0 - buzzer
* PC3 - front dish top led
* PC4 - gondel left back
* PC5 - gondel right back
* PC6 - gondel left front
* PC7 - gondel right front
* PD0 - deflecor led
* PD1 - programming pin. connected to SAO connector pin 2
* PD2 - dish top left
* PD3 - dish top right
* PD4 - dish bottom left
* PD5 - dish bottom right
* PD6 - SWITCH 2
* PD7 - SWITCH 1 (reset (NRST), can be changed to regular gpio using minichlink -D (from ch32fun)
