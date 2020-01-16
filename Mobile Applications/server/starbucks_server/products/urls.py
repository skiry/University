from django.urls import path

from . import views

urlpatterns = [
    # ex: /products/
    path('', views.index, name='index'),
    # ex: /products/5/
    path('<int:product_id>/', views.detail, name='detail'),
    # ex: /products/all/
    path('all/', views.all, name='all'),
    # ex: /products/add/
    path('add/', views.add, name='add'),
    # ex: /products/update/5
    path('update/<int:product_id>/', views.update, name='update'),
    # ex: /products/delete/5
    path('delete/<int:product_id>/', views.delete, name='delete'),
]
