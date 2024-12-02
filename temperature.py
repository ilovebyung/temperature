'''
Read temperature from a PC
'''
import serial
import time

# Configure serial port
ser = serial.Serial('/dev/ttyACM0', 9600)  # Replace '/dev/ttyUSB0' with your port name

while True:
    try:
        # Read serial data
        line = ser.readline().decode().strip()
        print(f"{line}")

    except KeyboardInterrupt:
        print("Exiting...")
        ser.close()
        break
    except Exception as e:
        print(f"Error: {e}")
        time.sleep(1)  # Pause for 1 second before retrying
