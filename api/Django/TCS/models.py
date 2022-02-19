from django.db import models
from django.core.validators import RegexValidator


class User(models.Model):
    first_name = models.CharField(
        verbose_name='Primeiro Nome',
        max_length=250
    )

    last_name = models.CharField(
        verbose_name='Último Nome',
        max_length=250
    )

    email = models.EmailField()

    def __str__(self):
        return str(self.first_name + " " + self.last_name)

    class Meta:
        verbose_name = 'Usuário'


class PTIid(models.Model):
    AFFILIATIONS = (
        ('UNIOESTE', 'Unioeste Estadual do Oeste do Paraná'),
        ('UNILA', 'Universidade Federal da Integração Latino-Americana'),
        ('FPTI', 'Fundação Parque Tecnológico de Itaipu'),
        ('OTHER', 'Outro')
    )

    user_id = models.ForeignKey(
        User,
        on_delete=models.PROTECT
    )

    affiliation = models.CharField(
        verbose_name='Instituição',
        max_length=50,
        choices=AFFILIATIONS,
        help_text='Instituição ao qual o usuário é afiliado'
    )

    role = models.CharField(
        verbose_name='Cargo',
        blank=True,
        max_length=50,
        help_text='Qual o cargo do usuário no LabIoT'
    )

    registration = models.CharField(
        verbose_name='Matrícula',
        help_text='Número de matrícula do usuário no PTI',
        max_length=7,
        validators=[
            RegexValidator(
                regex='^[0-9]{7,7}$',
                message='A matrícula precisa ser exatamente como no crachá',
                code='Número Inválido'
            )
        ]
    )

    expire_date = models.DateField(
        verbose_name='Validade',
        help_text='Data de validade do crachá de identificação'
    )

    rfid_uid = models.CharField(
        verbose_name='UID do Crachá',
        help_text="Unique Identifier do chip RFID do crachá do usuário",
        max_length=11,
        blank=True,
        unique=True,
        validators=[
            RegexValidator(
                regex='^([0-9A-F]{2}):([0-9A-F]{2}):([0-9A-F]{2}):([0-9A-F]{2})$',
                message='Digite no formato com letras maiúsculas (0x:0x:0x:0x)',
                code='UID Inválido'
            )
        ]
    )

    def __str__(self):
        return str(self.registration + ' - ' + self.user_id.__str__() + ' (' + self.affiliation + ')')

    class Meta:
        verbose_name = 'Crachá'


class TimeCheck(models.Model):
    user_id = models.ForeignKey(
        User,
        on_delete=models.PROTECT
    )

    check_in = models.DateTimeField()

    check_out = models.DateTimeField()
