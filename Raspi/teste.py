
import time

lastMessageTime = time.time()
isPaused = False

while True:
    if (time.time() - lastMessageTime) > 0.5 and isPaused == False:
        print(time.time() - lastMessageTime)
        isPaused = True
    time.sleep(0.1)