import serial
import re
import time
import win32com.client

class Speaker(object):
    def __init__(self):
        self.TooDry = "Oh, it seems a little dry"
        self.TooCold = "Ah, it seems a little cold here"
        self.TooNoise = "Keep it down,I can hear you"
        self.Light = "Ah, how dazzling"
        self.Dark = "Ah, it so dark"
        self.speaker = win32com.client.Dispatch("SAPI.SpVoice")
        self.Sensor = serial.Serial('COM3', 9600, timeout=0.2)

    def feedback(self):
        # 接收返回的信息
        strs = self.Sensor.readline().decode('utf-8')
        if strs.strip()!='':
            print(strs)
            if (re.match(r"broken",strs)):
                self.speaker.Speak(self.TooDry)
            elif (re.match(r"blush",strs)):
                self.speaker.Speak(self.Dark)
            elif (re.match(r"sad",strs)):
                self.speaker.Speak(self.TooCold)
            elif (re.match(r"angry",strs)):
                self.speaker.Speak(self.TooNoise)

def main():
    speaker = Speaker()
    while True:
        speaker.feedback()
        # time.sleep(1)

if __name__ == "__main__":
    main()


