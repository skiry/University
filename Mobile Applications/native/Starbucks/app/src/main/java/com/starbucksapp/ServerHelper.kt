package com.starbucksapp

import com.beust.klaxon.Klaxon
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.net.HttpURLConnection
import java.net.URL
import java.net.URLEncoder

class ServerHelper {

    fun getAll(): ArrayList<Product> {
        val mURL = URL("http://10.0.2.2:8000/products/all/")

        val products = ArrayList<Product>()
        with(mURL.openConnection() as HttpURLConnection) {
            // optional default is GET
            requestMethod = "GET"

            println("URL : $url")
            println("Response Code : $responseCode")

            BufferedReader(InputStreamReader(inputStream)).use {
                var inputLine = it.readLine()
                var c = 0
                var prevLine = ""
                while (inputLine != null) {
                    print(prevLine)
                    if (c > 1) {
                        val result = Klaxon()
                            .parse<RemoteProduct>(prevLine)
                        products.add(Product(c - 1, result!!.id, result.name, result.price, result.weight, result.description))
                    }
                    prevLine = inputLine
                    inputLine = it.readLine()
                    c += 1
                }
                it.close()
            }
        }
        for (x in products){
            println(x)
        }
        return products
    }

    fun get(id: Int): Product? {
        val mURL = URL("http://10.0.2.2:8000/products/$id/")
        try {
            with(mURL.openConnection() as HttpURLConnection) {
                // optional default is GET
                requestMethod = "GET"

                println("URL : $url")
                println("Response Code : $responseCode")

                BufferedReader(InputStreamReader(inputStream)).use {
                    return Klaxon()
                        .parse<Product>(it.readLine())!!
                }
            }
        }
        catch (e: Exception) {
            println("That element does not exist")
            return null
        }
    }


    fun add(name: String, price: Double, weight: Int, description: String): Int {
        var reqParam = URLEncoder.encode("name", "UTF-8") + "=" + URLEncoder.encode(name, "UTF-8")
        reqParam += "&" + URLEncoder.encode("price", "UTF-8") + "=" + URLEncoder.encode(price.toString(), "UTF-8")
        reqParam += "&" + URLEncoder.encode("weight", "UTF-8") + "=" + URLEncoder.encode(weight.toString(), "UTF-8")
        reqParam += "&" + URLEncoder.encode("description", "UTF-8") + "=" + URLEncoder.encode(description, "UTF-8")
        val mURL = URL("http://10.0.2.2:8000/products/add/")
        var added: Int = 0

        with(mURL.openConnection() as HttpURLConnection) {
            // optional default is GET
            requestMethod = "POST"

            val wr = OutputStreamWriter(outputStream)
            wr.write(reqParam)
            wr.flush()

            println("URL : $url")
            println("Response Code : $responseCode")

            BufferedReader(InputStreamReader(inputStream)).use {
                val response = StringBuffer()

                var inputLine = it.readLine()
                while (inputLine != null) {
                    response.append(inputLine)
                    println("ADDED PRODUCT WITH REMOTE ID $inputLine")
                    added = inputLine.toInt()
                    inputLine = it.readLine()
                }
                it.close()
                println("Response : $response")
            }
        }
        return added
    }

    fun update(id: String, name: String, price: Double, weight: Int, description: String): Int {
        var reqParam = URLEncoder.encode("name", "UTF-8") + "=" + URLEncoder.encode(name, "UTF-8")
        reqParam += "&" + URLEncoder.encode("price", "UTF-8") + "=" + URLEncoder.encode(price.toString(), "UTF-8")
        reqParam += "&" + URLEncoder.encode("weight", "UTF-8") + "=" + URLEncoder.encode(weight.toString(), "UTF-8")
        reqParam += "&" + URLEncoder.encode("description", "UTF-8") + "=" + URLEncoder.encode(description, "UTF-8")
        val mURL = URL("http://10.0.2.2:8000/products/update/$id/")
        var updated: Int = 0

        try {
            with(mURL.openConnection() as HttpURLConnection) {
                // optional default is GET
                requestMethod = "POST"

                val wr = OutputStreamWriter(outputStream)
                wr.write(reqParam)
                wr.flush()

                println("URL : $url")
                println("Response Code : $responseCode")

                BufferedReader(InputStreamReader(inputStream)).use {
                    val response = StringBuffer()

                    var inputLine = it.readLine()
                    while (inputLine != null) {
                        response.append(inputLine)
                        println("UDATED PRODUCT WITH REMODE ID $inputLine")
                        updated = inputLine.toInt()
                        inputLine = it.readLine()
                    }
                    it.close()
                    println("Response : $response")
                }
            }
            return updated
        }
        catch (e: Exception) {
            println("THE ELEMENT YOU ARE TRYING TO UPDATE DOES NOT EXIST")
            return -1
        }
    }

    fun delete(id: String): Int {
        val mURL = URL("http://10.0.2.2:8000/products/delete/$id/")
        var deleted: Int = 0
        try {


            with(mURL.openConnection() as HttpURLConnection) {
                // optional default is GET
                requestMethod = "POST"

                val wr = OutputStreamWriter(outputStream)
                wr.flush()

                println("URL : $url")
                println("Response Code : $responseCode")

                BufferedReader(InputStreamReader(inputStream)).use {
                    val response = StringBuffer()

                    var inputLine = it.readLine()
                    while (inputLine != null) {
                        response.append(inputLine)
                        println("DELETED ID $inputLine")
                        deleted = inputLine.toInt()
                        inputLine = it.readLine()
                    }
                    it.close()
                    println("Response : $response")
                }
            }
            return deleted
        }
        catch (e: Exception) {
            print("That element does not exist!")
            return -1
        }
    }
}