import serial   # pip install pyserial
import time
import tkinter as tk

# Configure serial port
ser = serial.Serial('/dev/ttyACM0', 9600)  # Replace '/dev/ttyUSB0' with your port name

# Create the Tkinter window
window = tk.Tk()
window.title("Serial Data Display")

# Create a text widget to display the data
# text_widget = tk.Text(window)
text_widget = tk.Text(window, font=("Arial", 12))
text_widget.pack(fill="both", expand=True)

def update_text():
    try:
        # Read serial data
        line = ser.readline().decode().strip()
        text_widget.insert(tk.END, f"{line}\n")
        text_widget.see(tk.END)  # Scroll to the bottom
        window.after(100, update_text)  # Schedule the next update
    except KeyboardInterrupt:
        print("Exiting...")
        ser.close()
        window.quit()
    except Exception as e:
        print(f"Error: {e}")
        window.after(1000, update_text)  # Retry after 1 second

# Start the update process
update_text()

# Run the Tkinter event loop
window.mainloop()