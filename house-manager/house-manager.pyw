#!/usr/bin/python

from Tkinter import * #Tk, Listbox, BOTH, END, X
from ttk import * #Frame, Button, Style, Entry, Label, Radiobutton

import os

# run pip install pyserial
import serial

WAVE_PATH = os.path.expanduser('~') + "/wav/"

musicians = []

colors =  ['off', 'dimWhite', 'darkTeal', 'brightTeal', 
           'purple', 'violet', 'red', 'fireRed', 'gold',
           'darkGreen', 'green', 'lightGreen', 'brightWhite']

bpms = [123, 98, 96, 91, 80, 75, 74, 72, 60]




class HouseManager(Frame):
  def __init__(self, parent):
    Frame.__init__(self, parent)
    self.parent = parent
    self.initUI()
  
  def initUI(self):
    self.colorVal = StringVar()
    self.bpmVal = IntVar()

    self.parent.title("House Manager")
    self.style = Style()
    self.style.theme_use("default")

    songList = Listbox(self)
    songList.bind("<Double-Button-1>", self.playSong)

    musicianList = Listbox(self)

    self.commandInput = Entry(self)
    commandSend = Button(self, text="Send Command",
        command=self.sendCommand)

    stopSongButton = Button(self, text="Stop Song", 
        command=self.stopSong)

    self.colorList = Listbox(self)
    
    self.pack(fill=BOTH, expand=1)
    stopSongButton.pack(side="bottom", fill=X)
    commandSend.pack(side="bottom", fill=X)
    
    # self.commandInput.pack(side="bottom", fill=X)
    # songList.pack(side="bottom", fill="both", expand=True)
    
    for bpm in bpms:
      Radiobutton(self, text=bpm, variable=self.bpmVal, value=bpm).pack(side="bottom")

    for color in colors:
      Radiobutton(self, text=color, variable=self.colorVal, value=color).pack(side="bottom")

    # self.colorList.pack(side="bottom", fill="both", expand=True)
    musicianList.pack(side="bottom", fill="both", expand=True)

    self.commandInput.bind('<Return>', self.enterKeypressed)  

    for item in os.listdir(WAVE_PATH):
      songList.insert(END, item.rsplit('.', 1)[0])

    for color in colors:
      self.colorList.insert(END, color)


    for tty in os.listdir('/dev/'):
      if tty.startswith('tty.usbmodem') or tty.startswith('cu.wchusbserial'):
        connection = serial.Serial('/dev/' + tty, 9600)
        connection.readline()
        connection.write('WHOAMI\n')
        musicianName = connection.readline()
        print(musicianName)
        musicianList.insert(END, musicianName)
        musicians.append(connection)

  def playSong(self, event):
    widget = event.widget
    songTitle = widget.get(widget.curselection()[0])
    command = songTitle + '.CSV'
    self.sendCommand(command.upper())
    self.playWav(songTitle)

  def stopSong(self):
    self.sendCommand('STOP')
    self.stopMusic

  def sendCommand(self, command = None):
    if command is None:
      command = "HSF%d" % self.bpmVal.get()

    color = colors.index(self.colorVal.get())
    toSend = "%s:%i" % (command, color)

    print "Send command %s" % toSend
    for musician in musicians:
      musician.write("%s\n" % toSend)

  def playWav(self, songTitle):
    # print "Starting the song " + songTitle
    wavfile = WAVE_PATH + songTitle
    os.system("open " + wavfile + '.wav')

  def stopMusic():
    print "Stop the music!"

  def enterKeypressed(self, arg2):
    print("Enter key pressed!")
    self.sendCommand()
  

def main():
  root = Tk()
  root.geometry("250x700+300+300")
  app = HouseManager(root)
  root.mainloop()  


if __name__ == '__main__':
  main()