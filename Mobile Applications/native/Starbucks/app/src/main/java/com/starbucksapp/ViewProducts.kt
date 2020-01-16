package com.starbucksapp

import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import android.os.Bundle
import android.os.Handler
import android.view.View
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.mikepenz.materialdrawer.Drawer
import com.mikepenz.materialdrawer.DrawerBuilder
import com.mikepenz.materialdrawer.model.DividerDrawerItem
import com.mikepenz.materialdrawer.model.PrimaryDrawerItem
import com.mikepenz.materialdrawer.model.SecondaryDrawerItem
import com.mikepenz.materialdrawer.model.interfaces.IDrawerItem
import kotlinx.android.synthetic.main.activity_main.*


class ViewProducts : AppCompatActivity() {
    val serverHelper = ServerHelper()
    var listItems = ArrayList<Product>()
    lateinit var adapter: ArrayAdapter<Product>
    lateinit var swipeLayout: SwipeRefreshLayout
    lateinit var databaseProducts: DatabaseReference


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_view_products)
        swipeLayout = findViewById(R.id.swiperefresh)

        databaseProducts = FirebaseDatabase.getInstance().getReference("products")

        swipeLayout.setOnRefreshListener {
            // Your code here
            Toast.makeText(applicationContext, "Works!", Toast.LENGTH_LONG).show()
            // To keep animation for 4 seconds
            if (verifyAvailableNetwork(this)) addOffline()
            Handler().postDelayed(Runnable {
                // Stop animation (This will be after 3 seconds)
                swipeLayout.isRefreshing = false
            }, 4000) // Delay in millis
        }

        swipeLayout.setColorSchemeColors(
            getResources().getColor(android.R.color.holo_blue_bright),
            getResources().getColor(android.R.color.holo_green_light),
            getResources().getColor(android.R.color.holo_orange_light),
            getResources().getColor(android.R.color.holo_red_light)
        );

        val item1 = PrimaryDrawerItem().withIdentifier(1).withName(R.string.drawer_item_add)
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
                        onBackPressed()
                    }
                    if (position == 2) {
                        if (verifyAvailableNetwork(this@ViewProducts)){
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

        adapter = ArrayAdapter(
            this,
            android.R.layout.simple_list_item_1,
            listItems
        )
        showProducts()
    }

    fun verifyAvailableNetwork(activity:AppCompatActivity):Boolean{
        val connectivityManager=activity.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        val networkInfo=connectivityManager.activeNetworkInfo
        return  networkInfo!=null && networkInfo.isConnected
    }

    fun showToast(text: String) {
        Toast.makeText(this@ViewProducts, text, Toast.LENGTH_LONG).show()
    }

    fun onRefreshGet() {
        val dbHelper = DatabaseHelper(this)
        listItems = serverHelper.getAll()
        dbHelper.deleteProducts()
        for (product in listItems) {
            dbHelper.addProduct(product.remoteId, product.name, product.price, product.weight, product.description)
        }
        listItems = ArrayList()
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

    fun showProducts() {
        if (verifyAvailableNetwork(this)){
            addOffline()
        }

        val listView: ListView = this.findViewById(R.id.products_list)
        listView.adapter = adapter
        val dbHelper = DatabaseHelper(this)
        val res = dbHelper.getProducts
        while (res.moveToNext()) {
            val id = res.getInt(0)
            val remoteId = res.getString(1)
            val name = res.getString(2)
            val price = res.getDouble(3)
            val weight = res.getInt(4)
            val description = res.getString(5)
            listItems.add(Product(id, remoteId, name, price, weight, description))
        }
        adapter.notifyDataSetChanged()
        res.close()

        listView.setOnItemClickListener { _, _, position, _ ->
            val nr = listItems[position].id
            val intent = Intent(this, UpdateProducts::class.java)
            intent.putExtra(("id"), nr)
            intent.putExtra(("position"), position)
            startActivityForResult(intent, 1)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        val index = data?.getIntExtra("position", 0)
        val id = data?.getIntExtra("pid", 0)
        if (resultCode == 1) {
            Toast.makeText(this, "Product successfully updated!", Toast.LENGTH_LONG).show()
            val dbHelper = DatabaseHelper(this)
            val product =  dbHelper.getProductById(id!!)
            listItems[index!!] = product
        }
        else if (resultCode == 2) {
            Toast.makeText(this, "Product successfully deleted!", Toast.LENGTH_LONG).show()
            listItems.removeAt(index!!)
        }
        adapter.notifyDataSetChanged()
    }
}
