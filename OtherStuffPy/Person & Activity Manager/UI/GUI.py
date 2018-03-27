'''
Created on 5 dec. 2017

@author: Skiry
'''
from tkinter import *
from tkinter import messagebox

class GUI:
    """
      Implement the graphic user interface for add/list students
    """
    def __init__(self, PersonCtrl,ActivityCtrl,UndoCtrl):
        self.ctrl = PersonCtrl

    def menu(self):
        self.tk = Tk()
        self.tk.title("Persons and Activities")

        frame = Frame(self.tk)
        frame.pack()
        self.frame = frame

        lbl = Label(frame, text="Introduce:")
        lbl.pack(side=LEFT)

        self.idtf = Entry(frame, {})
        self.idtf.pack(side=LEFT)

        self.storeBtn = Button(frame, text="Add Person", command=self.__storePressed)
        self.storeBtn.pack(side=LEFT)

        self.listBtn = Button(frame, text="List Persons", command=self.__listStudents)
        self.listBtn.pack(side=LEFT)

        self.button = Button(frame, text="QUIT", fg="red", command=frame.quit)
        self.button.pack(side=LEFT)
        
        frame = Frame(self.tk)
        frame.pack()
        self.frame = frame

        lbl = Label(frame, text="ID:")
        lbl.pack(side=LEFT)

        self.idtf = Entry(frame, {})
        self.idtf.pack(side=LEFT)

        self.storeBtn = Button(frame, text="Delete Person", command=self.__deletePressed)
        self.storeBtn.pack(side=LEFT)

        frame = Frame(self.tk)
        frame.pack()
        self.frame = frame

        lbl = Label(frame, text="ID:")
        lbl.pack(side=LEFT)

        self.idtf = Entry(frame, {})
        self.idtf.pack(side=LEFT)

        lbl = Label(frame, text="Name:")
        lbl.pack(side=LEFT)

        self.nametf = Entry(frame, {})
        self.nametf.pack(side=LEFT)

        lbl = Label(frame, text="Number:")
        lbl.pack(side=LEFT)

        self.numbertf = Entry(frame, {})
        self.numbertf.pack(side=LEFT)

        lbl = Label(frame, text="Address.:")
        lbl.pack(side=LEFT)

        self.addresstf = Entry(frame, {})
        self.addresstf.pack(side=LEFT)

        self.storeBtn = Button(frame, text="Update Person", command=self.__updatePressed)
        self.storeBtn.pack(side=LEFT)
        
        
        
        self.tk.mainloop()

    def __storePressed(self):
        """
          Handler method for store button pressed
          Store the student
          Show error messages on exceptions
        """
        try:
            print((self.idtf.get(), self.nametf.get(), self.numbertf.get(), self.addresstf.get()))
            st = self.ctrl.add((self.idtf.get(), self.nametf.get(), self.numbertf.get(), self.addresstf.get()))
            messagebox.showinfo("Stored", "Person %s saved.." % st.getName())
            print
        except Exception as e:
            messagebox.showinfo("Error", "Error saving student - " + str(e))
     
    def __updatePressed(self):
        """
          Handler method for store button pressed
          Store the student
          Show error messages on exceptions
        """
        try:
            st = self.ctrl.update((self.idtf.get(), self.nametf.get(), self.numbertf.get(), self.addresstf.get()))
            messagebox.showinfo("Stored", "Person %s updated.." % st.getName())
            print
        except Exception as e:
            messagebox.showinfo("Error", "Error saving student - " + str(e))
                   
    def __deletePressed(self):
        """
          Handler method for store button pressed
          Store the student
          Show error messages on exceptions
        """
        try:
            st = self.ctrl.remove(self.idtf.get())
        except Exception as e:
            messagebox.showinfo("Error", "Error removing student - " + str(e))

    def __listStudents(self):
        """
          Handler method for list button
          Show all the students
        """
        sts = self.ctrl.getAll()
        txt = "ID".ljust(5) + "Name".ljust(15) + "Address\n"
        for st in sts:
            txt += self.ctrl.getAll()[st][0].ljust(5) + self.ctrl.getAll()[st][1].ljust(15) + str(self.ctrl.getAll()[st][2])
            txt += "\n"
        messagebox.showinfo("List students", txt)


