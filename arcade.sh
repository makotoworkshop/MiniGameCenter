#!/bin/bash

sudo modprobe fbtft_device custom name=fb_ili9341 gpios=reset:24,dc:25,led:18 speed=64000000 fps=60 bgr=1 rotate=270
#sudo SDL_VIDEODRIVER=fbcon SDL_FBDEV=/dev/fb1 mplayer -vo sdl -framedrop /home/pi/deathsml_15-07-2015_1cc_Xvid.avi

sleep 4
/usr/local/bin/fbcp &

#mplayer 01-Bridge\ Burning.mp3
#omxplayer /home/pi/deathsml_15-07-2015_1cc_h264-21.mp4 --aspect-mode stretch -o local
/usr/bin/python3 /home/pi/omxcontrol/VideoOMXcontrol_GPIO_DeuxFonction.py
