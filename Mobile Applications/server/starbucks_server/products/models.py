from django.db import models
from django.forms.models import model_to_dict
from django.http import JsonResponse

class Product(models.Model):
    name = models.CharField(max_length=200)
    price = models.FloatField(default=0.)
    weight = models.IntegerField(default=0)
    description = models.CharField(max_length=1000)

    def __str__(self):
        return "{" + f' "id":{self.id}, "name":"{self.name}", "price":{self.price}, "weight":{self.weight}, "description":"{self.description}" ' + "}\n"