# Trekkie_Addon - USS Enterprise SAO

my contribution to Hackaday Europe 2025 Badge SAO

## NCC-1701-D - USS Enterprise 
![PXL_20250314_204249380 MP~2](https://github.com/user-attachments/assets/0bc40702-85f7-4b31-984d-9b69915c3f4d)

### general 
* hardware compatible to 2024 Supercon 8 I2C prototyping petal SAO, using CH32v003 (see: https://github.com/Hack-a-Day/2024-Supercon-8-Add-On-Badge/tree/main/hardware/sao/i2c_proto_petal#prototyping-i2c-sao-petal-for-supercon-8)
* I added a few leds, two switches and a buzzer. Every LED is connected to a single gpio pin.
* you can change the light and sound as you wish, also with the PIpico on the badge

if u use my firmware, dont fire to much ;-)

### PINOUT: 
* PC0 - buzzer
* PC3 - front dish top led
* PC4 - engine nacelles left back
* PC5 - engine nacelles back
* PC6 - engine nacelles front
* PC7 - engine nacelles front
* PD0 - deflecor led
* PD1 - programming pin. connected to SAO connector pin 2
* PD2 - dish top left
* PD3 - dish top right
* PD4 - dish bottom left
* PD5 - dish bottom right
* PD6 - SWITCH 2 - fire the plasma cannon
* PD7 - SWITCH 1 - power up or reset (NRST), that can be changed to regular gpio using minichlink -D (from ch32fun)

## some impressions from the making:
![PXL_20250307_085014307](https://github.com/user-attachments/assets/57941858-6c0b-466a-90ed-fad521e740f9)
![PXL_20250307_085021719](https://github.com/user-attachments/assets/a16376bf-064f-4304-97c0-cd55332c92a0)
![PXL_20250307_090016560](https://github.com/user-attachments/assets/8b0082a5-40ff-490a-8758-59bd5f4e3ac2)
![PXL_20250310_182050628](https://github.com/user-attachments/assets/07f6ccd0-0f0a-4226-9d20-6d4a7bfd3e9d)
![PXL_20250314_213640538](https://github.com/user-attachments/assets/db35dafc-988d-4545-a24f-d7f22d9a3a61)
![PXL_20250314_204246564 MP](https://github.com/user-attachments/assets/991760e8-ca20-46de-a9ac-b5e3fe2865fc)

