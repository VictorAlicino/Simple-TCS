from django.shortcuts import render
from django.http import HttpResponse
from rest_framework import viewsets, permissions, filters
from rest_framework.decorators import api_view

from TCS.serializers import *


# Create your views here.
def index(request):
    return HttpResponse("Hello, world")


class UserViewSet(viewsets.ModelViewSet):
    serializer_class = UserSerializer
    queryset = User.objects.all()


class PTIidViewSet(viewsets.ModelViewSet):
    serializer_class = PTIidSerializer
    queryset = PTIid.objects.all()
    filter_backends = [filters.SearchFilter]
    # TODO Trocar esse "search_field" porque ele não é nem um pouco seguro
    search_fields = ['rfid_uid']
