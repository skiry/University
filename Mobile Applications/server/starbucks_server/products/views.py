import ast
from django.shortcuts import render
from django.http import HttpResponse

from .models import Product

SEPARATOR = "" # ", "
def index(request):
    return HttpResponse("Hello, world. You're at the products index.")

def all(request):
    prefix = '{ "products" : [\n'
    postfix = ']}'
    return HttpResponse(prefix + SEPARATOR.join(str(product) for product in Product.objects.all()) + postfix)

def detail(request, product_id):
    try:
        result = Product.objects.get(pk=product_id)
        return HttpResponse(result)
    except:
        return HttpResponse("nothing")

def add(request):
    body = request.body[:]
    body = body.decode("utf-8")
    body = ast.literal_eval(body)
    name = body['name']
    price = body['price']
    weight = body['weight']
    description = body['description']
    product = Product(name=name, price=price, weight=weight, description=description)
    product.save()
    return HttpResponse(str(product.id))

def update(request, product_id):
    try:
        print("AIDI" + str(product_id))
        result = Product.objects.get(pk=product_id)
        body = request.body[:]
        body = body.decode("utf-8")
        body = ast.literal_eval(body)
        print(body)
        name = body['name']
        price = body['price']
        weight = body['weight']
        description = body['description']
        result.name = name
        result.price = price
        result.weight = weight
        result.description = description
        result.save(update_fields=['name', 'price', 'weight', 'description'])
        return HttpResponse(str(result.id))
    except:
        return HttpResponse("nothing")

def delete(request, product_id):
    try:
        result = Product.objects.get(pk=product_id)
        deleted_id = result.id
        result.delete()
        return HttpResponse(str(deleted_id))
    except:
        return HttpResponse("nothing")
    
    