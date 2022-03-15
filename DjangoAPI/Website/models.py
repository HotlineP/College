from django.db import models


class User(models.Model):
    UserID = models.AutoField(primary_key=True)
    UserName = models.CharField(max_length=50)
    DateOfJoining = models.DateField(max_length=10)