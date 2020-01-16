import SQLite from "react-native-sqlite-storage";

SQLite.DEBUG(true);
SQLite.enablePromise(true);

const database_name = "Starbucks.db";
const database_version = "1.0";
const database_displayname = "SQLite React Native Starbucks Database";
const database_size = 20000;

export default class Database {
	initDB() {
	  let db;
	  return new Promise((resolve) => {
	    console.log("Plugin integrity check ...");
	    SQLite.echoTest()
	      .then(() => {
	        console.log("Integrity check passed ...");
	        console.log("Opening database ...");
	        SQLite.openDatabase(
	          database_name,
	          database_version,
	          database_displayname,
	          database_size
	        )
	          .then(DB => {
	            db = DB;
	            console.log("Database OPEN");
	            db.executeSql('SELECT 1 FROM Product LIMIT 1').then(() => {
	                console.log("Database is ready ... executing query ...");
	            }).catch((error) =>{
	                console.log("Received error: ", error);
	                console.log("Database not yet ready ... populating data");
	                db.transaction((tx) => {
	                    tx.executeSql('CREATE TABLE IF NOT EXISTS Product (id INTEGER PRIMARY KEY AUTOINCREMENT, remoteid, name, price, weight, description)');
	                }).then(() => {
	                    console.log("Table created successfully");
	                }).catch(error => {
	                    console.log(error);
	                });
	            });
	            resolve(db);
	          })
	          .catch(error => {
	            console.log(error);
	          });
	      })
	      .catch(error => {
	        console.log("echoTest failed - plugin not functional");
	      });
	    });
	};

	closeDatabase(db) {
	  if (db) {
	    console.log("Closing DB");
	    db.close()
	      .then(status => {
	        console.log("Database CLOSED");
	      })
	      .catch(error => {
	        this.errorCB(error);
	      });
	  } else {
	    console.log("Database was not OPENED");
	  }
	};

	listProduct() {
	  return new Promise((resolve) => {
	    const products = [];
	    this.initDB().then((db) => {
	      db.transaction((tx) => {
	        tx.executeSql('SELECT * FROM Product', []).then(([tx,results]) => {
	          console.log("Query completed");
	          var len = results.rows.length;
	          for (let i = 0; i < len; i++) {
	            let row = results.rows.item(i);
	            console.log(`Product ID: ${row.id}, Prod Name: ${row.name}, Remote id: ${row.remoteid}`)
	            const { id, remoteid, name, price, weight, description } = row;
	            products.push({
	             id,
	             remoteid,
	             name,
	             price,
	             weight,
	             description
	            });
	          }
	          console.log(products);
	          resolve(products);
	        });
	      }).then((result) => {
	        this.closeDatabase(db);
	      }).catch((err) => {
	        console.log(err);
	      });
	    }).catch((err) => {
	      console.log(err);
	    });
	  });  
	}

	productById(id) {
	  console.log(id);
	  return new Promise((resolve) => {
	    this.initDB().then((db) => {
	      db.transaction((tx) => {
	        tx.executeSql('SELECT * FROM Product WHERE id = ?', [id]).then(([tx,results]) => {
	          console.log(results);
	          if(results.rows.length > 0) {
	            let row = results.rows.item(0);
	            resolve(row);
	          }
	        });
	      }).then((result) => {
	        this.closeDatabase(db);
	      }).catch((err) => {
	        console.log(err);
	      });
	    }).catch((err) => {
	      console.log(err);
	    });
	  });  
	}

	addProduct(prod) {
	  return new Promise((resolve) => {
	    this.initDB().then((db) => {
	      db.transaction((tx) => {
	        tx.executeSql('INSERT INTO Product(remoteid, name, price, weight, description) VALUES (?, ?, ?, ?, ?)', [prod.remoteid, prod.name, prod.price, prod.weight, prod.description]).then(([tx, results]) => {
	          resolve(results);
	        });
	      }).then((result) => {
	        this.closeDatabase(db);
	      }).catch((err) => {
	        console.log(err);
	      });
	    }).catch((err) => {
	      console.log(err);
	    });
	  });  
	}

	updateProduct(id, prod) {
	  return new Promise((resolve) => {
	    this.initDB().then((db) => {
	      db.transaction((tx) => {
	        tx.executeSql('UPDATE Product SET remoteid = ?, name = ?, price = ?, weight = ?, description = ? WHERE id = ?', [prod.remoteid, prod.name, prod.price, prod.weight, prod.description, id]).then(([tx, results]) => {
	          resolve(results);
	        });
	      }).then((result) => {
	        this.closeDatabase(db);
	      }).catch((err) => {
	        console.log(err);
	      });
	    }).catch((err) => {
	      console.log(err);
	    });
	  });  
	}

	deleteProduct(id) {
	  return new Promise((resolve) => {
	    this.initDB().then((db) => {
	      db.transaction((tx) => {
	        tx.executeSql('DELETE FROM Product WHERE id = ?', [id]).then(([tx, results]) => {
	          console.log(results);
	          resolve(results);
	        });
	      }).then((result) => {
	        this.closeDatabase(db);
	      }).catch((err) => {
	        console.log(err);
	      });
	    }).catch((err) => {
	      console.log(err);
	    });
	  });  
	}
}