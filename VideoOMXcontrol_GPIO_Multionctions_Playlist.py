#!/usr/bin/env python2.7
# coding: utf-8
# on importe les modules nécessaires

# À FAIRE :
# - Démarrer les vidéos avec un niveau sonnore bas
# -

from omxcontrol import *
import subprocess
import RPi.GPIO as GPIO
import time

#############
# Init GPIO #
#############
PIN_PLAY = 31           # GPIO06, Play/Pause/Stop
PIN_VOLMOINS = 35       # GPIO19, Volume -
PIN_VOLPLUS = 37        # GPIO26, Volume +
PIN_PRECEDENT = 38      # GPIO20, Précédent
PIN_SUIVANT = 36        # GPIO16, Suivant

GPIO.setmode(GPIO.BOARD) ## Use board pin numbering
GPIO.setup(PIN_PLAY, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(PIN_VOLMOINS, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(PIN_VOLPLUS, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(PIN_PRECEDENT, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(PIN_SUIVANT, GPIO.IN, pull_up_down=GPIO.PUD_UP)

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
long_press = 1
very_long_press = 3
start = 0
end = 0

##########################
# Démarrage (facultatif) #
##########################
os.system('sudo pkill omxplayer')       # S'assure qu'aucune instance omxplayer ne tourne encore, en cas de plantage
# omxplayer /home/pi/deathsml_15-07-2015_1cc_h264-21.mp4 --aspect-mode stretch -o local
subprocess.Popen(['omxplayer','--aspect-mode', 'stretch', '-o', 'local', Selection(vid)], stdin=subprocess.PIPE)
time.sleep(3)

# fonction qui sera appelée quand on appuiera sur le bouton : PIN_VOLMOINS
def bouton_PIN_VOLMOINS(channel):
    global start
    global end
    if GPIO.input(channel) == GPIO.LOW:
        print("GPIO.LOW")
        start = time.time()
    if GPIO.input(channel) == GPIO.HIGH:
        print("GPIO.HIGH")
        end = time.time()
        elapsed = end - start
        print(elapsed)
        if (elapsed > very_long_press):
            print("very_long_press: ",very_long_press)
            # À DÉFINIR
            print('Fonction à définir')
        elif (elapsed > long_press):
            print("long_press :",long_press)
            # À DÉFINIR
            print('Fonction à définir')
        elif (elapsed > 0):
            print("short_press")
            # Baisser le Volume du son
            print("Button Volume - pressé")
            omx.action(OmxControl.ACTION_DECREASE_VOLUME)


def bouton_PIN_VOLPLUS(channel):
    global start
    global end
    if GPIO.input(channel) == GPIO.LOW:
        print("GPIO.LOW")
        start = time.time()
    if GPIO.input(channel) == GPIO.HIGH:
        print("GPIO.HIGH")
        end = time.time()
        elapsed = end - start
        print(elapsed)
        if (elapsed > very_long_press):
            print("very_long_press: ",very_long_press)
            # À DÉFINIR
            print('Fonction à définir')
        elif (elapsed > long_press):
            print("long_press :",long_press)
            # À DÉFINIR
            print('Fonction à définir')
        elif (elapsed > 0):
            print("short_press")
            # Monter le Volume du son
            print("Button Volume + pressé")
            omx.action(OmxControl.ACTION_INCREASE_VOLUME)


def bouton_PIN_PRECEDENT(channel):
    global vid
    global start
    global end
    if GPIO.input(channel) == GPIO.LOW:
        print("GPIO.LOW")
        start = time.time()
    if GPIO.input(channel) == GPIO.HIGH:
        print("GPIO.HIGH")
        end = time.time()
        elapsed = end - start
        print(elapsed)
        if (elapsed > very_long_press):
            print("very_long_press: ",very_long_press)
            # À DÉFINIR
            print('Fonction à définir')
        elif (elapsed > long_press):
            print("long_press :",long_press)
            # Stopper la lecture et tombe donc en erreur via Try > Except de la boucle principale
            print('Vidéo Précédente')
            omx.action(OmxControl.ACTION_EXIT)
            vid = vid - 1       # pour lire la vidéo précédente
            if vid == -1:
                vid = 3
            print('vid : ',vid)
        elif (elapsed > 0):
            print("short_press")
            # un petit saut un arriére dans la vidéo
            print('<<')
            omx.action(OmxControl.ACTION_SEEK_BACK_SMALL)


def bouton_PIN_SUIVANT(channel):
    global vid
    global start
    global end
    if GPIO.input(channel) == GPIO.LOW:
        print("GPIO.LOW")
        start = time.time()
    if GPIO.input(channel) == GPIO.HIGH:
        print("GPIO.HIGH")
        end = time.time()
        elapsed = end - start
        print(elapsed)
        if (elapsed > very_long_press):
            print("very_long_press: ",very_long_press)
            # À DÉFINIR
            print('Fonction à définir')
        elif (elapsed > long_press):
            print("long_press :",long_press)
            # Stopper la lecture et tombe donc en erreur via Try > Except de la boucle principale
            print('Vidéo Suivante')
            omx.action(OmxControl.ACTION_EXIT)
            vid = vid + 1       # pour lire la vidéo suivante
            if vid == 4:
                vid = 0
            print('vid : ',vid)
        elif (elapsed > 0):
            print("short_press")
            # un petit saut en avant dans la vidéo
            print('>>')
            omx.action(OmxControl.ACTION_SEEK_FORWARD_SMALL)


def bouton_PIN_PLAY(channel):
    global start
    global end
    if GPIO.input(channel) == GPIO.LOW:
        print("GPIO.LOW")
        start = time.time()
    if GPIO.input(channel) == GPIO.HIGH:
        print("GPIO.HIGH")
        end = time.time()
        elapsed = end - start
        print(elapsed)
        if (elapsed > very_long_press):
            print("very_long_press: ",very_long_press)
            # À DÉFINIR
            print('Fonction à définir')
        elif (elapsed > long_press):
            print("long_press :",long_press)
            # Stoppe la vidéo
            print('Stop')
            omx.action(OmxControl.ACTION_EXIT)	 # SORTIR DE LA BOUCLE PRINCIPALE sinon la vidéo se relancera
        elif (elapsed > 0):
            print("short_press")
            # Pause/Play la vidéo
            print('Pause/Play')
            omx.action(OmxControl.ACTION_PAUSE)


GPIO.add_event_detect(PIN_VOLMOINS, GPIO.BOTH, callback=bouton_PIN_VOLMOINS, bouncetime=100)
GPIO.add_event_detect(PIN_VOLPLUS, GPIO.BOTH, callback=bouton_PIN_VOLPLUS, bouncetime=100)
GPIO.add_event_detect(PIN_PRECEDENT, GPIO.BOTH, callback=bouton_PIN_PRECEDENT, bouncetime=100)
GPIO.add_event_detect(PIN_SUIVANT, GPIO.BOTH, callback=bouton_PIN_SUIVANT, bouncetime=100)
GPIO.add_event_detect(PIN_PLAY, GPIO.BOTH, callback=bouton_PIN_PLAY, bouncetime=100)

#####################
# Boucle Principale #
#####################
while True:
    try:
        omx = OmxControl()      # appel librairie OmxControl

    except OmxControlError as ex:       # si le controle ne voit plus D-Bus, relance la vidéo
        print("ERROR contrôle D-Bus")
        print('Selection : ',Selection(vid))
        subprocess.Popen(['omxplayer','--aspect-mode', 'stretch', '-o', 'local', Selection(vid)], stdin=subprocess.PIPE)
        time.sleep(3)   # tempo pour laisser le temps au player vidéo de démarrer

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

