from rest_framework import serializers
from TCS.models import *


class PTIidSerializer(serializers.ModelSerializer):
    class Meta:
        model = PTIid
        fields = [
            'registration',
            'affiliation',
            'role',
            'user_id',
        ]
        depth = 1


class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = [
            'first_name',
            'last_name',
            'email'
        ]
