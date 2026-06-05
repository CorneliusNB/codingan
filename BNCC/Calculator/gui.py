from pathlib import Path
from tkinter import Tk, Canvas, Text, Button, PhotoImage

OUTPUT_PATH = Path(__file__).parent
ASSETS_PATH = OUTPUT_PATH / Path(r"/home/cornel/codingan/Calculator/build/assets/frame0")

def relative_to_assets(path: str) -> Path:
    return ASSETS_PATH / Path(path)

def button_click(value):
    current = entry_1.get("1.0", "end-1c")
    entry_1.delete("1.0", "end")
    entry_1.insert("end", current + str(value))

def button_clear():
    entry_1.delete("1.0", "end")


def button_backspace():
    current = entry_1.get("1.0", "end-1c")
    if current:
        entry_1.delete("1.0", "end")
        entry_1.insert("end", current[:-1])


def button_equal():
    expression = entry_1.get("1.0", "end-1c")
    try:
        result = eval(expression.replace("×", "*").replace("÷", "/"))
        entry_1.delete("1.0", "end")
        entry_1.insert("end", str(result))
    except Exception:
        entry_1.delete("1.0", "end")
        entry_1.insert("end", "Error")

window = Tk()
window.geometry("324x531")
window.configure(bg="#FFFFFF")

canvas = Canvas(
    window,
    bg="#FFFFFF",
    height=531,
    width=324,
    bd=0,
    highlightthickness=0,
    relief="ridge"
)
canvas.place(x=0, y=0)
canvas.create_rectangle(0.0, 0.0, 324.0, 531.0, fill="#E3DEDA", outline="")
canvas.create_rectangle(5.0, 22.0, 319.0, 148.0, fill="#1B1B1B", outline="")

entry_image_1 = PhotoImage(file=relative_to_assets("entry_1.png"))
entry_bg_1 = canvas.create_image(162.0, 85.5, image=entry_image_1)
entry_1 = Text(bd=0, bg="#BFBFA2", fg="#000716", highlightthickness=0)
entry_1.place(x=9.0, y=28.0, width=306.0, height=113.0)

canvas.create_rectangle(9.0, 203.0, 315.0, 515.0, fill="#9D938C", outline="")

button_image_3 = PhotoImage(file=relative_to_assets("button_3.png"))
button_3 = Button(image=button_image_3, borderwidth=0, command=lambda: button_click("7"))
button_3.place(x=19.0, y=230.0, width=64.7, height=59.1)

button_image_12 = PhotoImage(file=relative_to_assets("button_12.png"))
button_12 = Button(image=button_image_12, borderwidth=0, command=lambda: button_click("8"))
button_12.place(x=101.6, y=230.0, width=64.7, height=59.1)

button_image_10 = PhotoImage(file=relative_to_assets("button_10.png"))
button_10 = Button(image=button_image_10, borderwidth=0, command=lambda: button_click("9"))
button_10.place(x=184.3, y=230.0, width=64.7, height=59.1)

button_image_13 = PhotoImage(file=relative_to_assets("button_13.png"))
button_13 = Button(image=button_image_13, borderwidth=0, command=lambda: button_click("4"))
button_13.place(x=19.0, y=301.7, width=64.7, height=59.1)

button_image_11 = PhotoImage(file=relative_to_assets("button_11.png"))
button_11 = Button(image=button_image_11, borderwidth=0, command=lambda: button_click("5"))
button_11.place(x=101.6, y=301.7, width=64.7, height=59.1)

button_image_9 = PhotoImage(file=relative_to_assets("button_9.png"))
button_9 = Button(image=button_image_9, borderwidth=0, command=lambda: button_click("6"))
button_9.place(x=184.3, y=301.7, width=64.7, height=59.1)

button_image_8 = PhotoImage(file=relative_to_assets("button_8.png"))
button_8 = Button(image=button_image_8, borderwidth=0, command=lambda: button_click("1"))
button_8.place(x=19.0, y=378.9, width=64.7, height=59.1)

button_image_6 = PhotoImage(file=relative_to_assets("button_6.png"))
button_6 = Button(image=button_image_6, borderwidth=0, command=lambda: button_click("2"))
button_6.place(x=101.6, y=378.9, width=64.7, height=59.1)

button_image_4 = PhotoImage(file=relative_to_assets("button_4.png"))
button_4 = Button(image=button_image_4, borderwidth=0, command=lambda: button_click("3"))
button_4.place(x=184.3, y=378.9, width=64.7, height=59.1)

button_image_7 = PhotoImage(file=relative_to_assets("button_7.png"))
button_7 = Button(image=button_image_7, borderwidth=0, command=lambda: button_click("0"))
button_7.place(x=19.0, y=449.0, width=148.0, height=58.5)

button_image_5 = PhotoImage(file=relative_to_assets("button_5.png"))
button_5 = Button(image=button_image_5, borderwidth=0, command=lambda: button_click("."))
button_5.place(x=184.0, y=449.0, width=64.7, height=59.1)

button_image_14 = PhotoImage(file=relative_to_assets("button_14.png"))
button_14 = Button(image=button_image_14, borderwidth=0, command=lambda: button_click("+"))
button_14.place(x=261.0, y=230.0, width=48.0, height=30.0)

button_image_21 = PhotoImage(file=relative_to_assets("button_21.png"))
button_21 = Button(image=button_image_21, borderwidth=0, command=lambda: button_click("-"))
button_21.place(x=261.0, y=262.0, width=48.0, height=30.0)

button_image_20 = PhotoImage(file=relative_to_assets("button_20.png"))
button_20 = Button(image=button_image_20, borderwidth=0, command=lambda: button_click("×"))
button_20.place(x=261.0, y=302.0, width=48.0, height=30.0)

button_image_19 = PhotoImage(file=relative_to_assets("button_19.png"))
button_19 = Button(image=button_image_19, borderwidth=0, command=lambda: button_click("÷"))
button_19.place(x=261.0, y=334.0, width=48.0, height=30.0)

button_image_17 = PhotoImage(file=relative_to_assets("button_17.png"))
button_17 = Button(image=button_image_17, borderwidth=0, command=lambda: button_click("%"))
button_17.place(x=261.0, y=379.0, width=48.0, height=59.0)

button_image_18 = PhotoImage(file=relative_to_assets("button_18.png"))
button_18 = Button(image=button_image_18, borderwidth=0, command=button_equal)
button_18.place(x=261.0, y=448.0, width=48.0, height=59.0)


button_image_1 = PhotoImage(
    file=relative_to_assets("button_1.png"))
button_1 = Button(
    image=button_image_1,
    borderwidth=0,
    highlightthickness=0,
    command=button_clear,
    relief="flat"
)
button_1.place(
    x=243.0,
    y=155.0,
    width=72.0,
    height=36.0
)

button_image_2 = PhotoImage(
    file=relative_to_assets("button_2.png"))
button_2 = Button(
    image=button_image_2,
    borderwidth=0,
    highlightthickness=0,
    command=button_backspace,
    relief="flat"
)
button_2.place(
    x=167.0,
    y=155.0,
    width=72.0,
    height=36.0
)






canvas.create_text(
    9.0,
    159.0,
    anchor="nw",
    text="Calculator\nBy Cornelius",
    fill="#000000",
    font=("Inter", 12 * -1)
)

window.resizable(False, False)
window.mainloop()

