from django.shortcuts import render
from django.http import HttpResponse

porra = 'templates/main/index.html'

def main(request):
    return render(request, 'templates/main/index.html')
    #return HttpResponse("<h1>seja bem vindo bruh</h1>")