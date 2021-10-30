import tkinter as tk
from tkinter import filedialog
import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

filename = ""
def selectFile():
    global filename
    filename = filedialog.askopenfilename(initialdir="/Users/sidsr/Documents", title = "Choose File")
    print(filename)
    f = open(filename)
    x = f.read().splitlines()
    arr = []
    print(x)
    for i in x:
        arr.append(float(i.split()[0]))
    series = np.arange(0, len(arr))
    fig = plt.Figure(figsize = (20, 20),
                 dpi = 100)
    plot1 = fig.add_subplot(111)
    plot1.set_xlabel("Reading #")
    plot1.set_ylabel("Force (N)")
    plot1.set_title("Your Force Values")
    plot1.plot(series, arr)
    canvas = FigureCanvasTkAgg(fig,
                               master = window)
    canvas.draw()
    canvas.get_tk_widget().pack()
    print(len(arr), series.size)
#Window init
window = tk.Tk()

#Top bar
frametitle = tk.Frame()
apptitle = tk.Label(master=frametitle, text="Welcome to the Parkinson's Detector")
apptitle.pack()

framebutton = tk.Frame()
button = tk.Button(
    master=framebutton,
    text="Display data",
    command = selectFile
)
button.pack()


frametitle.pack()
framebutton.pack()

window.mainloop()
