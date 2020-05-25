#!/usr/bin/env python2.7
# coding: utf-8
# Compatible Python3

# Programme pour RaspberryPi
# Joue une playliste de vidéos avec omxplayer
# Pilotage des vidéos et de la playliste avec une télécommande IR via un Arduino + bluetooth


##################################
# Import des modules nécessaires #
##################################
from omxcontrol import *
import subprocess
import RPi.GPIO as GPIO
import time
import serial

#############
# Init GPIO #
#############
PIN_BRIGHTNESS = 12     # GPIO18, PWM de réglage de la luminosité
PIN_POWEROFF = 40       # GPIO21, Uniquement PowerOff logiciel. Le powerOn, via Arduino + switch RpiOnOff

GPIO.setmode(GPIO.BOARD) ## Use board pin numbering
GPIO.setup(PIN_BRIGHTNESS, GPIO.OUT)
GPIO.setup(PIN_POWEROFF, GPIO.OUT)

bluetoothSerial = serial.Serial("/dev/rfcomm0",baudrate=115200)
print("Bluetooth connected")

#####################
# Ressources Vidéos #
#####################
def Selection(i):
    switcher={
        0:'/home/pi/deathsml_15-07-2015_1cc_h264-21.mp4',
        1:'/home/pi/dodonpachi_23-02-2014_montage.mp4',
        2:'/home/pi/espgal_26-02-2015_1cc_x264_crf23.mp4',
        3:'/home/pi/galaxian.mp4',
        }
    return switcher.get(i,"Séléction Invalide")

#############
# Variables #
#############
vid = 0
brightness = 100
pwm = GPIO.PWM(PIN_BRIGHTNESS, 130) # channel et frequence en Hz, meilleur résultat à 120 et 130Hz

##########################
# Démarrage (facultatif) #
##########################
os.system('sudo pkill omxplayer')       # S'assure qu'aucune instance omxplayer ne tourne encore, en cas de plantage
# omxplayer /home/pi/deathsml_15-07-2015_1cc_h264-21.mp4 --aspect-mode stretch -o local
pwm.start(brightness)	# Démarrage de la PWM du rétroéclairage LCD au max (100)

###############################
# Fonctions pour Télécommande #
###############################

def bouton_VOLUMEMOINS():
    # baisse le volume
    print("Volume -")
    omx.action(OmxControl.ACTION_DECREASE_VOLUME)

def bouton_VOLUMEPLUS():
    # augmente le volume
    print("Volume +")
    omx.action(OmxControl.ACTION_INCREASE_VOLUME)

def bouton_LUMMOINS():
    global brightness
    # Baisser la luminosité de l'écran LCD
    brightness = brightness - 10
    if brightness <= 10:
        brightness = 10
        print("Luminosité baissée au max")
    print("Baisse la luminosite :", brightness)
    pwm.ChangeDutyCycle(brightness)

def bouton_LUMPLUS():
    global brightness
    # Augmenter la luminosité de l'écran LCD
    brightness = brightness + 10
    if brightness >= 100:
        brightness = 100
        print("Luminosité augmentée au max")
    print("Augmente la luminosite :", brightness)
    pwm.ChangeDutyCycle(brightness)

def bouton_BACK():
    # un petit saut un arriére dans la vidéo
    print('<<')
    omx.action(OmxControl.ACTION_SEEK_BACK_SMALL)

def bouton_PRECEDENT():
    global vid
    # Stopper la lecture et tombe donc en erreur via Try > Except de la boucle principale
    print('Vidéo Précédente')
    omx.action(OmxControl.ACTION_EXIT)
    vid = vid - 1       # pour lire la vidéo précédente
    if vid == -1:
        vid = 3
    print('vid : ',vid)
    omx.action(OmxControl.ACTION_PAUSE)

def bouton_FORWARD():
    # un petit saut en avant dans la vidéo
    print('>>')
    omx.action(OmxControl.ACTION_SEEK_FORWARD_SMALL)

def bouton_SUIVANT():
    global vid
    # Stopper la lecture et tombe donc en erreur via Try > Except de la boucle principale
    print('Vidéo Suivante')
    omx.action(OmxControl.ACTION_EXIT)
    vid = vid + 1       # pour lire la vidéo suivante
    if vid == 4:
        vid = 0
    print('vid : ',vid)
    omx.action(OmxControl.ACTION_PAUSE)

def bouton_PLAY():
    # Pause/Play la vidéo
    print('Pause/Play')
    omx.action(OmxControl.ACTION_PAUSE)

def bouton_STOP():
    # Stoppe la vidéo
    print('Stop')
    omx.action(OmxControl.ACTION_EXIT)

def bouton_POWEROFF():
    # activer le gpio21
    GPIO.output(PIN_POWEROFF, GPIO.HIGH)
    print('PowerOFF')

#####################
# Boucle Principale #
#####################
while True:
    try:
        omx = OmxControl()      # appel librairie OmxControl

        data = bluetoothSerial.readline()	# donnée reçue via bluetooth
        print(data)
        print(type(data))	# Si python2 c'est un string, si python3 c'est un byte
        print('debut',data,'fin')	# Permet de révéler que la valeur envoyer présent \r\n en fin de mot
        time.sleep(0.1)

        if data.decode("utf-8") == 'R2\r\n' :	# .decode("utf-8") pour convertir le byte en string en python3 (pas d'impact sur le résultat en python2)
            bouton_VOLUMEMOINS() # Vol-
        elif data.decode("utf-8") == 'G2\r\n':
            bouton_VOLUMEPLUS()	# Vol+
        elif data.decode("utf-8") == 'B2\r\n':
            bouton_LUMMOINS()	# Lum-
        elif data.decode("utf-8") == 'STROBE\r\n':
            bouton_LUMPLUS()	# lum+
        elif data.decode("utf-8") == 'R3\r\n':
            bouton_BACK()	# <<
        elif data.decode("utf-8") == 'G3\r\n':
            bouton_FORWARD()	# >>
        elif data.decode("utf-8") == 'B3\r\n':
            bouton_PRECEDENT()	# précédent
        elif data.decode("utf-8") == 'FADE\r\n':
            bouton_SUIVANT()	# suivant
        elif data.decode("utf-8") == 'R4\r\n':
            bouton_PLAY()	# Play/Pause
        elif data.decode("utf-8") == 'G4\r\n':
            bouton_STOP()	# Stop
        elif data.decode("utf-8") == 'SMOOTH\r\n':
            bouton_POWEROFF()	# Power off

    except OmxControlError as ex:       # si le controle ne voit plus D-Bus, relance la vidéo
        print("ERREUR de contrôle D-Bus, relance de la vidéo")
        print('Selection : ',Selection(vid))
        subprocess.Popen(['omxplayer','--aspect-mode', 'stretch', '-o', 'local', Selection(vid)], stdin=subprocess.PIPE)
        time.sleep(3)   # tempo pour laisser le temps au player vidéo de démarrer
        omx = OmxControl()      # appel librairie OmxControl
        omx.action(OmxControl.ACTION_DECREASE_VOLUME)
        omx.action(OmxControl.ACTION_DECREASE_VOLUME)
        omx.action(OmxControl.ACTION_DECREASE_VOLUME)
        omx.action(OmxControl.ACTION_DECREASE_VOLUME)
        omx.action(OmxControl.ACTION_DECREASE_VOLUME)
        omx.action(OmxControl.ACTION_DECREASE_VOLUME)	# -18 db

# on réinitialise les ports GPIO en sortie de script
GPIO.cleanup()


#####################################################
# Fonctions disponible dans la librairie OmxControl #
#####################################################
#ACTION_DECREASE_SPEED
#ACTION_INCREASE_SPEED
#ACTION_REWIND
#ACTION_FAST_FORWARD
#ACTION_SHOW_INFO
#ACTION_PREVIOUS_AUDIO
#ACTION_NEXT_AUDIO
#ACTION_PREVIOUS_CHAPTER
#ACTION_NEXT_CHAPTER
#ACTION_PREVIOUS_SUBTITLE
#ACTION_NEXT_SUBTITLE
#ACTION_TOGGLE_SUBTITLE
#ACTION_DECREASE_SUBTITLE_DELAY
#ACTION_INCREASE_SUBTITLE_DELAY
#ACTION_EXIT
#ACTION_PAUSE
#ACTION_DECREASE_VOLUME
#ACTION_INCREASE_VOLUME
#ACTION_SEEK_BACK_SMALL
#ACTION_SEEK_FORWARD_SMALL
#ACTION_SEEK_BACK_LARGE
#ACTION_SEEK_FORWARD_LARGE
#ACTION_SEEK_RELATIVE
#ACTION_SEEK_ABSOLUTE
#ACTION_STEP
#ACTION_BLANK
#ACTION_MOVE_VIDEO
#ACTION_HIDE_VIDEO
#ACTION_UNHIDE_VIDEO
#ACTION_HIDE_SUBTITLES
