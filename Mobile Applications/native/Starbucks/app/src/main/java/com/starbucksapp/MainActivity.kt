package com.starbucksapp

import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import android.os.Bundle
import android.os.StrictMode
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.mikepenz.materialdrawer.Drawer
import com.mikepenz.materialdrawer.DrawerBuilder
import com.mikepenz.materialdrawer.model.DividerDrawerItem
import com.mikepenz.materialdrawer.model.PrimaryDrawerItem
import com.mikepenz.materialdrawer.model.SecondaryDrawerItem
import com.mikepenz.materialdrawer.model.interfaces.IDrawerItem
import kotlinx.android.synthetic.main.activity_main.*


class MainActivity : AppCompatActivity() {
    val serverHelper = ServerHelper()
    lateinit var databaseProducts: DatabaseReference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        databaseProducts = FirebaseDatabase.getInstance().getReference("products")

        val policy =
            StrictMode.ThreadPolicy.Builder().permitAll().build()

        StrictMode.setThreadPolicy(policy)

        val item1 = PrimaryDrawerItem().withIdentifier(1).withName(R.string.drawer_item_products)
        val item2 = SecondaryDrawerItem().withIdentifier(2).withName(R.string.drawer_item_about)

        //create the drawer and remember the `Drawer` result object
        val result = DrawerBuilder()
            .withActivity(this)
            .withToolbar(toolbar)
            .addDrawerItems(
                item1,
                DividerDrawerItem(),
                item2
            )
            .withOnDrawerItemClickListener(object : Drawer.OnDrawerItemClickListener {
                override fun onItemClick(view: View?, position: Int, drawerItem: IDrawerItem<*>): Boolean {
                    if (position == 0) {
                        viewProductsBtn.performClick()
                    }
                    if (position == 2) {
                        if (verifyAvailableNetwork(this@MainActivity)){
                            showToast("Connected to internet")
                        }
                        else{
                            showToast("Not connected to internet")
                        }
                    }
                    return false
                }
            })
            .build()

        addOffline()
        handleInserts()
        handleView()
    }

    fun showToast(text: String) {
        Toast.makeText(this@MainActivity, text, Toast.LENGTH_LONG).show()
    }

    fun clearProductInputs() {
        nameInput.setText("")
        priceInput.setText("")
        weightInput.setText("")
        editText5.setText("")
    }

    fun verifyAvailableNetwork(activity:AppCompatActivity):Boolean{
        val connectivityManager=activity.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        val networkInfo=connectivityManager.activeNetworkInfo
        return  networkInfo!=null && networkInfo.isConnected
    }

    fun addOffline() {
        val dbHelper = DatabaseHelper(this)
        val res = dbHelper.getProducts
        while (res.moveToNext()) {
            val id = res.getInt(0)
            var remoteId = res.getString(1)
            val name = res.getString(2)
            val price = res.getDouble(3)
            val weight = res.getInt(4)
            val description = res.getString(5)
            if (remoteId == "") {
                remoteId = databaseProducts.push().key!!
                var product = Product(
                    id,
                    remoteId,
                    name,
                    price,
                    weight,
                    description)
                databaseProducts.child(remoteId).setValue(product)
                dbHelper.updateProduct(id, remoteId, name, price, weight, description)
            }
        }
    }

    fun handleInserts() {
        addProductBtn.setOnClickListener {
            try {
                val dbHelper = DatabaseHelper(this)
                val remoteId: String
                var product = Product(
                    0,
                    "",
                    nameInput.text.toString(),
                    priceInput.text.toString().toDouble(),
                    weightInput.text.toString().toInt(),
                    editText5.text.toString())

                if (verifyAvailableNetwork(this)) {
                    remoteId = databaseProducts.push().key!!
                    product.remoteId = remoteId
                }

                val id = dbHelper.addProduct(
                    product.remoteId,
                    nameInput.text.toString(),
                    priceInput.text.toString().toDouble(),
                    weightInput.text.toString().toInt(),
                    editText5.text.toString())

                product.id = id
                if (verifyAvailableNetwork(this)) {
                    databaseProducts.child(product.remoteId).setValue(product)
                }

                clearProductInputs()
                showToast("Produs adaugat cu succes")
            } catch(e: Exception) {
                e.printStackTrace()
                showToast("Produsul nu a fost adaugat")
            }
        }
    }

    fun handleView() {
        viewProductsBtn.setOnClickListener {
            val intent = Intent(this, ViewProducts::class.java)
            startActivity(intent)
        }
    }
}