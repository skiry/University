package com.starbucksapp

import java.io.Serializable

class Product : Serializable{
    var id: Int
    var remoteId: String
    val name: String
    val price: Double
    val weight: Int
    val description: String

    constructor(id: Int, remote_id: String, name: String, price: Double, weight: Int, description: String) : super() {
        this.id = id
        this.remoteId = remote_id
        this.name = name
        this.price = price
        this.weight = weight
        this.description = description
    }

    override fun toString(): String {
        return "$name costa $price lei si are $weight g. $description"
    }
}

class RemoteProduct : Serializable{
    val id: String
    val name: String
    val price: Double
    val weight: Int
    val description: String

    constructor(id: String, name: String, price: Double, weight: Int, description: String) : super() {
        this.id = id
        this.name = name
        this.price = price
        this.weight = weight
        this.description = description
    }

    override fun toString(): String {
        return "$name costa $price lei si are $weight g. $description"
    }
}
