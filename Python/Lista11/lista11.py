from tkinter import *
from PIL import ImageTk, Image
import sqlite3


root = Tk()
root.title("database")
root.geometry("400x400")


conn = sqlite3.connect('movies2.db')

c = conn.cursor()
'''
c.execute("""CREATE TABLE addresses (
     title text,
     year integer,
     director text,
     producer text
     )""")
'''
def submit():



    conn = sqlite3.connect('movies2.db')

    c = conn.cursor()

    c.execute("INSERT INTO addresses VALUES (:title, :year, :director, :producer)", {
                 'title': title.get(),
                 'year': year.get(),
                 'director': director.get(),
                 'producer': producer.get(), })


    conn.commit()

    conn.close()

    title.delete(0, END)
    year.delete(0, END)
    director.delete(0, END)
    producer.delete(0, END)

def query():


    conn = sqlite3.connect('movies2.db')

    c = conn.cursor()

    c.execute("SELECT *, oid FROM addresses")
    records = c.fetchall()
    print(records)

    print_records = ''
    for record in records:
        print_records += str(record) + "\n"


    query_label = Label(root, text=print_records)
    query_label.grid(row=8, column=0, columnspan=2)

    conn.commit()

    conn.close()





title = Entry(root, width=30)
title.grid(row=0, column=1, padx=20)

year = Entry(root, width=30)
year.grid(row=1, column=1)

director = Entry(root, width=30)
director.grid(row=2, column=1)

producer = Entry(root, width=30)
producer.grid(row=3, column=1)


title_label = Label(root, text="title")
title_label.grid(row=0, column=0)

year_label = Label(root, text="year")
year_label.grid(row=1, column=0)

director_label = Label(root, text="director")
director_label.grid(row=2, column=0)

producer_label = Label(root, text="producer")
producer_label.grid(row=3, column=0)



submit_btn = Button(root, text="add", command=submit)
submit_btn.grid(row=4,column=0, columnspan=2, pady=10, padx=10,ipadx=100)



query_btn = Button(root, text="show records", command=query)
query_btn.grid(row=5, column=0, columnspan=2, pady=10, padx=10, ipadx=137)





conn.commit()


conn.close()


root.mainloop()