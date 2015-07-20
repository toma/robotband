#!/usr/bin/python

from Tkinter import Tk, Listbox, BOTH, END, X
from ttk import Frame, Button, Style

import os

# run pip install pyserial
import serial

WAVE_PATH = os.path.expanduser('~') + "/wav/"
musicians = [ serial.Serial('/dev/tty.usbmodem1411', 9600),
              serial.Serial('/dev/tty.usbmodem1451', 9600)]

class HouseManager(Frame):
  def __init__(self, parent):
    Frame.__init__(self, parent)
    self.parent = parent
    self.initUI()
  
  def initUI(self):
    self.parent.title("House Manager")
    self.style = Style()
    self.style.theme_use("default")

    songList = Listbox(self)
    songList.bind("<Double-Button-1>", self.playSong)

    nextSongButton = Button(self, text="Stop Song", 
        command=self.stopSong)

    self.pack(fill=BOTH, expand=1)
    nextSongButton.pack(side="bottom", fill=X)
    songList.pack(side="top", fill="both", expand=True)

    for item in os.listdir(WAVE_PATH):
      songList.insert(END, item.rsplit('.', 1)[0])

  def playSong(self, event):
    widget = event.widget
    songTitle = widget.get(widget.curselection()[0])
    command = songTitle + '.CSV'
    self.sendCommand(command.upper())
    self.playWav(songTitle)

  def stopSong(self):
    self.sendCommand('STOP')
    self.stopMusic

  def sendCommand(self, command):
    print "Send play song command for " + command
    for musician in musicians:
      musician.write(command + '\n')

  def playWav(self, songTitle):
    # print "Starting the song " + songTitle
    wavfile = WAVE_PATH + songTitle
    os.system("open " + wavfile + '.wav')

  def stopMusic():
    print "Stop the music!"

def main():
  root = Tk()
  root.geometry("250x500+300+300")
  app = HouseManager(root)
  root.mainloop()  


if __name__ == '__main__':
  main()