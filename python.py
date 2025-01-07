import tkinter as tk
from tkinter import messagebox
import sqlite3
import re

# إعداد قاعدة البيانات
def init_db():
    conn = sqlite3.connect("rooms.db")
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password TEXT
        )
    """)
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS rooms (
            id INTEGER PRIMARY KEY,
            room_type TEXT,
            capacity INTEGER,
            available TEXT
        )
    """)
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS reservations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            room_id INTEGER,
            date TEXT,
            time TEXT,
            client_name TEXT,
            client_phone TEXT,
            FOREIGN KEY (room_id) REFERENCES rooms(id)
        )
    """)
    # إضافة مستخدم افتراضي
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('admin', 'admin')")
    conn.commit()
    conn.close()

# تسجيل الدخول
current_user = None  # متغير لتخزين اسم المستخدم الحالي

def login():
    global current_user  # استخدم المتغير العام لتخزين اسم المستخدم
    username = entry_username.get()
    password = entry_password.get()
    
    conn = sqlite3.connect("rooms.db")
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username = ? AND password = ?", (username, password))
    user = cursor.fetchone()
    conn.close()
    
    if user:
        current_user = username  # تخزين اسم المستخدم الحالي
        messagebox.showinfo("Login Successful", "Welcome, " + username)
        login_window.destroy()
        main_app()
    else:
        messagebox.showerror("Login Failed", "Invalid username or password.")

# تسجيل مستخدم جديد
def register_user():
    def save_new_user():
        new_username = entry_new_username.get()
        new_password = entry_new_password.get()
        
        if new_username and new_password:
            conn = sqlite3.connect("rooms.db")
            cursor = conn.cursor()
            try:
                cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (new_username, new_password))
                conn.commit()
                messagebox.showinfo("Success", "User registered successfully!")
                register_window.destroy()
            except sqlite3.IntegrityError:
                messagebox.showerror("Error", "Username already exists!")
            finally:
                conn.close()
        else:
            messagebox.showwarning("Input Error", "Please fill in all fields.")
    
    # نافذة تسجيل مستخدم جديد
    register_window = tk.Toplevel(login_window)
    register_window.title("Register New User")
    
    tk.Label(register_window, text="New Username:").grid(row=0, column=0, padx=10, pady=5)
    entry_new_username = tk.Entry(register_window)
    entry_new_username.grid(row=0, column=1, padx=10, pady=5)
    
    tk.Label(register_window, text="New Password:").grid(row=1, column=0, padx=10, pady=5)
    entry_new_password = tk.Entry(register_window, show="*")
    entry_new_password.grid(row=1, column=1, padx=10, pady=5)
    
    tk.Button(register_window, text="Register", command=save_new_user).grid(row=2, columnspan=2, pady=10)

# التحقق من صحة التاريخ
def validate_date(date):
    pattern = r"\d{4}-\d{2}-\d{2}"
    return re.match(pattern, date)

# التحقق من صحة الوقت
def validate_time(time):
    pattern = r"\d{2}:\d{2}"
    return re.match(pattern, time)

# الواجهة الرئيسية
def main_app():
    root = tk.Tk()
    root.title("Room Reservation System")
    root.geometry("500x600")
    
    # إضافة الغرف (تظهر فقط إذا كان المستخدم "admin")
    if current_user == "admin":
        frame_rooms = tk.Frame(root)
        frame_rooms.pack(pady=20)

        tk.Label(frame_rooms, text="Add Room", font=("Helvetica", 14, "bold")).grid(row=0, columnspan=2, pady=10)

        tk.Label(frame_rooms, text="Room ID:").grid(row=1, column=0, padx=10, pady=5)
        entry_room_id = tk.Entry(frame_rooms)
        entry_room_id.grid(row=1, column=1, padx=10, pady=5)

        tk.Label(frame_rooms, text="Room Type:").grid(row=2, column=0, padx=10, pady=5)
        room_type_var = tk.StringVar(value="General")
        tk.OptionMenu(frame_rooms, room_type_var, "General", "Meeting", "Teaching").grid(row=2, column=1, padx=10, pady=5)

        tk.Label(frame_rooms, text="Capacity:").grid(row=3, column=0, padx=10, pady=5)
        entry_capacity = tk.Entry(frame_rooms)
        entry_capacity.grid(row=3, column=1, padx=10, pady=5)

        tk.Button(frame_rooms, text="Add Room", command=lambda: add_room(entry_room_id, room_type_var, entry_capacity)).grid(row=4, columnspan=2, pady=10)
        tk.Button(frame_rooms, text="Display Rooms", command=display_rooms).grid(row=5, columnspan=2, pady=10)
        
        # إضافة زر لحذف غرفة
        tk.Label(frame_rooms, text="Room ID to Delete:").grid(row=6, column=0, padx=10, pady=5)
        entry_room_id_delete = tk.Entry(frame_rooms)
        entry_room_id_delete.grid(row=6, column=1, padx=10, pady=5)
        tk.Button(frame_rooms, text="Delete Room", command=lambda: delete_room(entry_room_id_delete)).grid(row=7, columnspan=2, pady=10)

    # قسم الحجوزات
    frame_reservations = tk.Frame(root)
    frame_reservations.pack(pady=20)

    tk.Label(frame_reservations, text="Make Reservation", font=("Helvetica", 14, "bold")).grid(row=0, columnspan=2, pady=10)

    tk.Label(frame_reservations, text="Room ID:").grid(row=1, column=0, padx=10, pady=5)
    entry_res_room_id = tk.Entry(frame_reservations)
    entry_res_room_id.grid(row=1, column=1, padx=10, pady=5)

    tk.Label(frame_reservations, text="Date (YYYY-MM-DD):").grid(row=2, column=0, padx=10, pady=5)
    entry_date = tk.Entry(frame_reservations)
    entry_date.grid(row=2, column=1, padx=10, pady=5)

    tk.Label(frame_reservations, text="Time (HH:MM):").grid(row=3, column=0, padx=10, pady=5)
    entry_time = tk.Entry(frame_reservations)
    entry_time.grid(row=3, column=1, padx=10, pady=5)

    tk.Label(frame_reservations, text="Client Name:").grid(row=4, column=0, padx=10, pady=5)
    entry_client_name = tk.Entry(frame_reservations)
    entry_client_name.grid(row=4, column=1, padx=10, pady=5)

    tk.Label(frame_reservations, text="Client Phone:").grid(row=5, column=0, padx=10, pady=5)
    entry_client_phone = tk.Entry(frame_reservations)
    entry_client_phone.grid(row=5, column=1, padx=10, pady=5)

    tk.Button(frame_reservations, text="Make Reservation", command=lambda: make_reservation(entry_res_room_id, entry_date, entry_time, entry_client_name, entry_client_phone)).grid(row=6, columnspan=2, pady=10)
    tk.Button(frame_reservations, text="Display Reservations", command=display_reservations).grid(row=7, columnspan=2, pady=10)
    
    # إضافة زر لحذف الحجز
    tk.Label(frame_reservations, text="Reservation ID to Delete:").grid(row=8, column=0, padx=10, pady=5)
    entry_reservation_id_delete = tk.Entry(frame_reservations)
    entry_reservation_id_delete.grid(row=8, column=1, padx=10, pady=5)
    tk.Button(frame_reservations, text="Delete Reservation", command=lambda: delete_reservation(entry_reservation_id_delete)).grid(row=9, columnspan=2, pady=10)

    # تعديل الحجز
    tk.Button(root, text="Modify Reservation", command=modify_reservation).pack(pady=10)
    
    root.mainloop()

# إضافة غرفة
def add_room(entry_room_id, room_type_var, entry_capacity):
    room_id = entry_room_id.get()
    room_type = room_type_var.get()
    capacity = entry_capacity.get()
    if room_id and room_type and capacity:
        conn = sqlite3.connect("rooms.db")
        cursor = conn.cursor()
        cursor.execute("INSERT INTO rooms (id, room_type, capacity, available) VALUES (?, ?, ?, ?)",
                       (room_id, room_type, capacity, "Yes"))
        conn.commit()
        conn.close()

        # حفظ البيانات في ملف rooms.txt
        with open("rooms.txt", "a") as file:
            file.write(f"Room ID: {room_id}, Type: {room_type}, Capacity: {capacity}, Available: Yes\n")

        messagebox.showinfo("Success", "Room added successfully!")
        entry_room_id.delete(0, tk.END)
        entry_capacity.delete(0, tk.END)
    else:
        messagebox.showwarning("Input Error", "Please fill in all fields.")

# عرض الغرف مع إضافة اسكرول
def display_rooms():
    conn = sqlite3.connect("rooms.db")
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM rooms")
    rooms = cursor.fetchall()
    conn.close()
    
    rooms_text = "Room ID | Type | Capacity | Available\n" + "-"*40 + "\n"
    for room in rooms:
        rooms_text += f"{room[0]} | {room[1]} | {room[2]} | {room[3]}\n"
    
    # إنشاء نافذة جديدة لعرض الغرف مع اسكرول
    rooms_window = tk.Toplevel()
    rooms_window.title("Rooms List")
    
    canvas = tk.Canvas(rooms_window)
    scrollbar = tk.Scrollbar(rooms_window, orient="vertical", command=canvas.yview)
    canvas.configure(yscrollcommand=scrollbar.set)
    
    scrollbar.pack(side="right", fill="y")
    canvas.pack(side="left", fill="both", expand=True)
    
    frame = tk.Frame(canvas)
    canvas.create_window((0, 0), window=frame, anchor="nw")
    
    label = tk.Label(frame, text=rooms_text, font=("Courier", 10))
    label.pack(padx=10, pady=10)
    
    frame.update_idletasks()
    canvas.config(scrollregion=canvas.bbox("all"))

# حذف غرفة
def delete_room(entry_room_id_delete):
    room_id = entry_room_id_delete.get()
    if room_id:
        conn = sqlite3.connect("rooms.db")
        cursor = conn.cursor()
        cursor.execute("DELETE FROM rooms WHERE id = ?", (room_id,))
        conn.commit()
        conn.close()
        messagebox.showinfo("Success", "Room deleted successfully!")
        entry_room_id_delete.delete(0, tk.END)
    else:
        messagebox.showwarning("Input Error", "Please enter a room ID.")

# إضافة حجز
def make_reservation(entry_res_room_id, entry_date, entry_time, entry_client_name, entry_client_phone):
    room_id = entry_res_room_id.get()
    date = entry_date.get()
    time = entry_time.get()
    client_name = entry_client_name.get()
    client_phone = entry_client_phone.get()

    if not validate_date(date):
        messagebox.showwarning("Invalid Date", "Please enter a valid date (YYYY-MM-DD).")
        return
    
    if not validate_time(time):
        messagebox.showwarning("Invalid Time", "Please enter a valid time (HH:MM).")
        return
    
    if room_id and date and time and client_name and client_phone:
        conn = sqlite3.connect("rooms.db")
        cursor = conn.cursor()
        cursor.execute("INSERT INTO reservations (room_id, date, time, client_name, client_phone) VALUES (?, ?, ?, ?, ?)",
                       (room_id, date, time, client_name, client_phone))
        conn.commit()
        conn.close()
        messagebox.showinfo("Success", "Reservation made successfully!")
        entry_res_room_id.delete(0, tk.END)
        entry_date.delete(0, tk.END)
        entry_time.delete(0, tk.END)
        entry_client_name.delete(0, tk.END)
        entry_client_phone.delete(0, tk.END)
    else:
        messagebox.showwarning("Input Error", "Please fill in all fields.")

# عرض الحجوزات مع إضافة اسكرول
def display_reservations():
    conn = sqlite3.connect("rooms.db")
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM reservations")
    reservations = cursor.fetchall()
    conn.close()
    
    res_text = "Res ID | Room ID | Date | Time | Name | Phone\n" + "-"*50 + "\n"
    for res in reservations:
        res_text += f"{res[0]} | {res[1]} | {res[2]} | {res[3]} | {res[4]} | {res[5]}\n"
    
    # إنشاء نافذة جديدة لعرض الحجوزات مع اسكرول
    reservations_window = tk.Toplevel()
    reservations_window.title("Reservations List")
    
    canvas = tk.Canvas(reservations_window)
    scrollbar = tk.Scrollbar(reservations_window, orient="vertical", command=canvas.yview)
    canvas.configure(yscrollcommand=scrollbar.set)
    
    scrollbar.pack(side="right", fill="y")
    canvas.pack(side="left", fill="both", expand=True)
    
    frame = tk.Frame(canvas)
    canvas.create_window((0, 0), window=frame, anchor="nw")
    
    label = tk.Label(frame, text=res_text, font=("Courier", 10))
    label.pack(padx=10, pady=10)
    
    frame.update_idletasks()
    canvas.config(scrollregion=canvas.bbox("all"))

# حذف حجز
def delete_reservation(entry_reservation_id_delete):
    reservation_id = entry_reservation_id_delete.get()
    if reservation_id:
        conn = sqlite3.connect("rooms.db")
        cursor = conn.cursor()
        cursor.execute("DELETE FROM reservations WHERE id = ?", (reservation_id,))
        conn.commit()
        conn.close()
        messagebox.showinfo("Success", "Reservation deleted successfully!")
        entry_reservation_id_delete.delete(0, tk.END)
    else:
        messagebox.showwarning("Input Error", "Please enter a reservation ID.")

# تعديل حجز
def modify_reservation():
    modify_window = tk.Toplevel()
    modify_window.title("Modify Reservation")
    
    tk.Label(modify_window, text="Enter Reservation ID:").pack(padx=10, pady=5)
    entry_reservation_id = tk.Entry(modify_window)
    entry_reservation_id.pack(padx=10, pady=5)
    
    tk.Button(modify_window, text="Modify", command=lambda: modify_reservation_action(entry_reservation_id)).pack(pady=10)

def modify_reservation_action(entry_reservation_id):
    reservation_id = entry_reservation_id.get()
    if reservation_id:
        conn = sqlite3.connect("rooms.db")
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM reservations WHERE id = ?", (reservation_id,))
        reservation = cursor.fetchone()
        conn.close()
        if reservation:
            modify_reservation_details(reservation)
        else:
            messagebox.showwarning("Not Found", "Reservation ID not found.")
    else:
        messagebox.showwarning("Input Error", "Please enter a reservation ID.")

def modify_reservation_details(reservation):
    modify_window = tk.Toplevel()
    modify_window.title(f"Modify Reservation {reservation[0]}")

    tk.Label(modify_window, text="Room ID:").pack(padx=10, pady=5)
    entry_room_id = tk.Entry(modify_window)
    entry_room_id.insert(0, reservation[1])
    entry_room_id.pack(padx=10, pady=5)

    tk.Label(modify_window, text="Date (YYYY-MM-DD):").pack(padx=10, pady=5)
    entry_date = tk.Entry(modify_window)
    entry_date.insert(0, reservation[2])
    entry_date.pack(padx=10, pady=5)

    tk.Label(modify_window, text="Time (HH:MM):").pack(padx=10, pady=5)
    entry_time = tk.Entry(modify_window)
    entry_time.insert(0, reservation[3])
    entry_time.pack(padx=10, pady=5)

    tk.Label(modify_window, text="Client Name:").pack(padx=10, pady=5)
    entry_name = tk.Entry(modify_window)
    entry_name.insert(0, reservation[4])
    entry_name.pack(padx=10, pady=5)

    tk.Label(modify_window, text="Client Phone:").pack(padx=10, pady=5)
    entry_phone = tk.Entry(modify_window)
    entry_phone.insert(0, reservation[5])
    entry_phone.pack(padx=10, pady=5)

    tk.Button(modify_window, text="Save Changes", command=lambda: save_modified_reservation(reservation[0], entry_room_id, entry_date, entry_time, entry_name, entry_phone)).pack(pady=10)

def save_modified_reservation(reservation_id, entry_room_id, entry_date, entry_time, entry_name, entry_phone):
    room_id = entry_room_id.get()
    date = entry_date.get()
    time = entry_time.get()
    name = entry_name.get()
    phone = entry_phone.get()

    if not validate_date(date):
        messagebox.showwarning("Invalid Date", "Please enter a valid date (YYYY-MM-DD).")
        return
    
    if not validate_time(time):
        messagebox.showwarning("Invalid Time", "Please enter a valid time (HH:MM).")
        return
    
    if room_id and date and time and name and phone:
        conn = sqlite3.connect("rooms.db")
        cursor = conn.cursor()
        cursor.execute("""UPDATE reservations SET room_id = ?, date = ?, time = ?, client_name = ?, client_phone = ?
                          WHERE id = ?""",
                       (room_id, date, time, name, phone, reservation_id))
        conn.commit()
        conn.close()

        messagebox.showinfo("Success", "Reservation updated successfully!")
    else:
        messagebox.showwarning("Input Error", "Please fill in all fields.")

# بدء التطبيق
init_db()

# نافذة تسجيل الدخول
login_window = tk.Tk()
login_window.title("Login")
login_window.geometry("300x200")

tk.Label(login_window, text="Username:").pack(pady=5)
entry_username = tk.Entry(login_window)
entry_username.pack(pady=5)

tk.Label(login_window, text="Password:").pack(pady=5)
entry_password = tk.Entry(login_window, show="*")
entry_password.pack(pady=5)

tk.Button(login_window, text="Login", command=login).pack(pady=10)
tk.Button(login_window, text="Register", command=register_user).pack(pady=5)

login_window.mainloop()
