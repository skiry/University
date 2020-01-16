package com.starbucksapp

import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.database.FirebaseDatabase
import kotlinx.android.synthetic.main.activity_update_products.*

class UpdateProducts : AppCompatActivity() {
    val serverHelper = ServerHelper()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_update_products)

        /*
        actionBar!!.title = "Actualizare produs"
        actionBar.setDisplayHomeAsUpEnabled(true)
        val actionBar = supportActionBar
         */

        val id = intent.getIntExtra("id", 0)
        val position = intent.getIntExtra("position", 0)
        setProductInputs(id)
        handleUpdate(id, position)
        handleDelete(id, position)
    }

    fun verifyAvailableNetwork(activity: AppCompatActivity): Boolean {
        val connectivityManager =
            activity.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        val networkInfo = connectivityManager.activeNetworkInfo
        return networkInfo != null && networkInfo.isConnected
    }

    override fun onSupportNavigateUp(): Boolean {
        onBackPressed()
        return true
    }

    fun showToast(text: String) {
        Toast.makeText(this@UpdateProducts, text, Toast.LENGTH_LONG).show()
    }

    fun setProductInputs(id: Int) {
        val dbHelper = DatabaseHelper(this)
        val product = dbHelper.getProductById(id)
        nameInputUpdate.setText(product.name)
        priceInputUpdate.setText(product.price.toString())
        weightInputUpdate.setText(product.weight.toString())
        editText5Update.setText(product.description)
    }

    fun handleUpdate(id: Int, position: Int) {
        updateProductBtn.setOnClickListener {
            if (verifyAvailableNetwork(this)) {
                try {
                    val dbHelper = DatabaseHelper(this)
                    val product = dbHelper.getProductById(id)
                    val databaseRefeference = FirebaseDatabase.getInstance().getReference("products").child(product.remoteId)
                    val newProduct = Product(
                        product.id,
                        product.remoteId,
                        nameInputUpdate.text.toString(),
                        priceInputUpdate.text.toString().toDouble(),
                        weightInputUpdate.text.toString().toInt(),
                        editText5Update.text.toString()
                    )
                    databaseRefeference.setValue(newProduct)

                    dbHelper.updateProduct(
                        id,
                        product.remoteId,
                        nameInputUpdate.text.toString(),
                        priceInputUpdate.text.toString().toDouble(),
                        weightInputUpdate.text.toString().toInt(),
                        editText5Update.text.toString()
                    )
                    showToast("Produs actualizat cu succes")

                    val intent = Intent()
                    intent.putExtra("pid", id)
                    intent.putExtra("position", position)
                    setResult(1, intent)
                    finish()
                } catch (e: Exception) {
                    e.printStackTrace()
                    showToast("Produsul nu a fost actualizat")
                }
            } else {
                showToast("Nu puteti modifica produsul fara acces la internet")
            }
        }
    }

    fun handleDelete(id: Int, position: Int) {
        deleteProductsBtn.setOnClickListener {
            if (verifyAvailableNetwork(this)) {
                try {
                    val dbHelper = DatabaseHelper(this)
                    val product = dbHelper.getProductById(id)

                    val databaseEntry = FirebaseDatabase.getInstance().getReference("products").child(product.remoteId)
                    databaseEntry.removeValue()

                    dbHelper.deleteProduct(id)
                    showToast("Produs sters cu succes")

                    val intent = Intent()
                    intent.putExtra("pid", id)
                    intent.putExtra("position", position)
                    setResult(2, intent)
                    finish()
                } catch (e: Exception) {
                    e.printStackTrace()
                    showToast("Produsul nu a fost sters")
                }
            } else {
                showToast("Nu puteti sterge produsul fara acces la internet")
            }
        }
    }
}
