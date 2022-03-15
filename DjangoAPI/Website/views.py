from django.shortcuts import render
from django.http import HttpResponse


def index(request):
    return HttpResponse('home/')


def chad(request):
    return HttpResponse('home/chad')