#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h> //for IOCTL defs
#include <fcntl.h>

#define I2C_FICHIER "/dev/i2c-1" // fichier Linux representant le BUS #2
#define I2C_ADRESSE 0x68		 // adresse du Device I2C MPU-9250 (motion tracking)
#define I2C_ADRESSE_VL6180x 0x29
#define VL6180X_NOMBRE 40

void vInitialisationVL6180();

int main()
{
	int fdPortI2C; // file descriptor I2C

	// Initialisation du port I2C,
	fdPortI2C = open(I2C_FICHIER, O_RDWR); // ouverture du 'fichier', création d'un 'file descriptor' vers le port I2C
	if (fdPortI2C == -1)
	{
		printf("erreur: I2C initialisation step 1\n");
		return -1;
	}
	if (ioctl(fdPortI2C, I2C_SLAVE_FORCE, I2C_ADRESSE_VL6180x) < 0) // I2C_SLAVE_FORCE if it is already in use by a driver (i2cdetect : UU)
	{
		printf("erreur: I2C initialisation step 2\n");
		close(fdPortI2C);
		return -1;
	}

	uint8_t message[3];
	message[0] = 0x02;
	message[1] = 0x07;
	message[2] = 0x01;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x02;
	message[1] = 0x08;
	message[2] = 0x01;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x01;
	message[1] = 0x33;
	message[2] = 0x01;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x01;
	message[1] = 0x33;
	message[2] = 0x01;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0x96;
	message[2] = 0x00;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0x97;
	message[2] = 0xFD;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xE3;
	message[2] = 0x00;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xE4;
	message[2] = 0x04;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xE5;
	message[2] = 0x02;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xE6;
	message[2] = 0x01;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xE7;
	message[2] = 0x03;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xF5;
	message[2] = 0x02;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xD9;
	message[2] = 0x05;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xDB;
	message[2] = 0xCE;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xDC;
	message[2] = 0x03;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xDD;
	message[2] = 0xF8;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0x9F;
	message[2] = 0x00;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xA3;
	message[2] = 0x3C;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xB7;
	message[2] = 0x00;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xBB;
	message[2] = 0x3C;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xB2;
	message[2] = 0x09;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x00;
	message[1] = 0xCA;
	message[2] = 0x09;
	write(fdPortI2C, &message[0], 3);
	message[0] = 0x01;
	message[1] = 0x98;
	message[2] = 0x01;
	write(fdPortI2C, &message[0], 3);

	// Écriture et Lecture sur le port I2C
	uint8_t Source[2];
	uint8_t Destination;
	uint8_t NombreDOctetsALire = 1;
	uint8_t NombreDOctetsAEcrire = 2;

	Source[0] = 0x00;
	Source[1] = 0x0;

	if (write(fdPortI2C, &Source[0], NombreDOctetsAEcrire) != NombreDOctetsAEcrire)
	{
		printf("erreur: Écriture I2C\n");
		close(fdPortI2C);
		return -1;
	}

	if (read(fdPortI2C, &Destination, NombreDOctetsALire) != NombreDOctetsALire)
	{
		printf("erreur: Lecture I2C\n");
		close(fdPortI2C);
		return -1;
	}
	printf("octets lus: %#04x\n", Destination);

	uint8_t Registres[4];
	Registres[0] = 0x18;
	Registres[1] = 0x4F;
	Registres[2] = 0x62;
	Registres[3] = 0x15;

	uint8_t Donnee[2];
	Donnee[0] = 0x01;
	Donnee[1] = 0x07;

	uint8_t valeur;

	if (write(fdPortI2C, &Registres[0], 1) < 0)
	{
		if (write(fdPortI2C, &Donnee[0], 1) < 0)
		{
			printf("erreur: interfaceVL6180x_litUneDistance 1\n");
			return -1;
		}
	}
	if (write(fdPortI2C, &Registres[1], 1) < 0)
	{
		if (read(fdPortI2C, &valeur, 1))
		{
			printf("erreur: interfaceVL6180x_litUneDistance 2\n");
			return -1;
		}
	}
	while ((valeur & 0x7) != 4)
	{
		if (write(fdPortI2C, &Registres[1], 1) < 0)
		{
			if (read(fdPortI2C, &valeur, 1))
			{
				printf("erreur: interfaceVL6180x_litUneDistance 3\n");
				return -1;
			}
		}
	}
	printf("3\n");
	if (write(fdPortI2C, &Registres[2], 1) < 0)
	{
		if (read(fdPortI2C, &valeur, 1))
		{
			printf("erreur: interfaceVL6180x_litUneDistance 4\n");
			return -1;
		}
	}
	printf("4\n");
	if (write(fdPortI2C, &Registres[3], 1) < 0)
	{
		if (write(fdPortI2C, &Donnee[2], 1) < 0)
		{
			printf("erreur: interfaceVL6180x_litUneDistance 5\n");
			return -1;
		}
	}
	printf("5\n");
	float Distance = (float)valeur / 10.0;

	printf("6\n");
	printf("Distance lue: %f\n", Distance);
	close(fdPortI2C); /// Fermeture du 'file descriptor'
	return 0;
}