package com.starbucksapp

import android.annotation.SuppressLint
import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper

class DatabaseHelper(context: Context):
    SQLiteOpenHelper(context, DATABASE_NAME, null, 1) {
    override fun onCreate(db: SQLiteDatabase?) {
        db!!.execSQL(
            "CREATE TABLE $PRODUCTS_TABLE" +
                "(ID INTEGER PRIMARY KEY AUTOINCREMENT," +
                    "REMOTEID TEXT, " +
                "NAME TEXT, PRICE REAL, WEIGHT INTEGER, " +
                "DESCRIPTION TEXT)"
        )
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
        db!!.execSQL("DROP TABLE IF EXISTS $PRODUCTS_TABLE")
        onCreate(db)
    }

    fun addProduct(remoteId: String, name: String, price: Double, weight: Int, description: String): Int {
        val db = this.writableDatabase
        val contentValues = ContentValues()
        contentValues.put(COL_2, remoteId)
        contentValues.put(COL_3, name)
        contentValues.put(COL_4, price)
        contentValues.put(COL_5, weight)
        contentValues.put(COL_6, description)
        val id = db.insert(PRODUCTS_TABLE, null, contentValues)
        db.close()
        return id.toInt()
    }

    val getProducts : Cursor
        get() {

            val db = this.writableDatabase
            return db.rawQuery("SELECT * FROM $PRODUCTS_TABLE", null)
        }

    @SuppressLint("Recycle")
    fun getProductById(id: Int): Product {
        val db = this.writableDatabase
        val res = db.rawQuery("SELECT * FROM $PRODUCTS_TABLE WHERE ID=$id", null)

        res.moveToFirst()
        val remoteId = res.getString(1)
        val name = res.getString(2)
        val price = res.getDouble(3)
        val weight = res.getInt(4)
        val description = res.getString(5)

        db.close()
        return Product(id, remoteId, name, price, weight, description)
    }

    fun updateProduct(id: Int, remoteId: String, name: String, price: Double, weight: Int, description: String) {
        val db = this.writableDatabase
        val contentValues = ContentValues()
        contentValues.put(COL_2, remoteId)
        contentValues.put(COL_3, name)
        contentValues.put(COL_4, price)
        contentValues.put(COL_5, weight)
        contentValues.put(COL_6, description)
        db.update(PRODUCTS_TABLE, contentValues, "ID=$id", null)
        db.close()
    }

    fun deleteProduct(id: Int) {
        val db = this.writableDatabase
        db.delete(PRODUCTS_TABLE, "ID=$id", null)
        db.close()
    }

    fun deleteProducts() {
        val db = this.writableDatabase
        db.delete(PRODUCTS_TABLE, null, null)
        db.close()
    }

    // common to all instances of a class
    companion object {
        const val DATABASE_NAME = "Starbucks.DB"
        const val PRODUCTS_TABLE = "products_table"
        const val COL_1 = "ID"
        const val COL_2 = "REMOTEID"
        const val COL_3 = "NAME"
        const val COL_4 = "PRICE"
        const val COL_5 = "WEIGHT"
        const val COL_6 = "DESCRIPTION"
    }
}