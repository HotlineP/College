from django.urls import URLPattern


from django.urls import path, include
from . import views


urlpatterns = [
    path('', views.index),
    path('chad', views.chad)
]