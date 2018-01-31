import mysql.connector
from mysql.connector import errorcode

try:
  cnx = mysql.connector.connect(user='root',
                                database='motionsensor')
except mysql.connector.Error as err:
  if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
    print("Something is wrong with your user name or password")
  elif err.errno == errorcode.ER_BAD_DB_ERROR:
    print("Database does not exist")
  else:
    print(err)
else:
    cursorr=cnx.cursor()
    cursorr.execute("UPDATE valori SET value=1 WHERE id=1")
    cnx.commit()
    cursorr.execute("SELECT * from valori")
    for row in cursorr:
        print("ID = ",row[0])
        print("VALUE = ",row[1])        
        
cnx.close()
