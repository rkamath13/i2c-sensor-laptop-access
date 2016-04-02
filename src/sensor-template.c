#include <stdio.h>
#include <unistd.h>
#include "i2c.h"

static const short
	i2cAddress = 0x00,  /* Device I2C address as per datasheet */
	regadd      = 0x00,  /* register address from where you need to take the readings   */
	configReg  = 0x00;  /* Configuration register         */

int main(int argc,char *argv[])
{
	int status;

	if(I2C_ERR_NONE == (status = I2Copen()))
	{
		unsigned char msg[2]; /* first byte will take the device address, second byte will take the device register address*/

		/* Issue configuration command (2 bytes) */
		msg[0] = configReg;
		msg[1] = 0x00;      /* Default value */
		if(I2C_ERR_NONE == (status = I2Cmsg(i2cAddress,msg,2,NULL,0)))
		{
			unsigned char reply[2]; /* My sensor gives data as 2 - 8 bit message, change accordingly */

			/* Issue a series of temperature-reading commands
			   (1 byte each w/2-byte replies) */
			msg[0] = regadd;
			while(I2C_ERR_NONE == (status = I2Cmsg(i2cAddress,msg,1,reply,2)))
			{
				/* Take the register data in an integer variable 
				int c;

				c = reply[0]+reply[1];  //if your register gives 1 byte data, use only an unsigned/signed char variable*/
		
				/*Now process the data according to your use or by referring the datasheet of your i2c device*/
				
				sleep(1);
			}
		}

		I2Cclose();      /* Close the file Descriptor*/
	}

	/* Technically the clean exit case here will never happen (program
	   runs indefinitely until interrupted or I2Cmsg() fails), but it's
	   left here in case you want to change the program to perform a
	   single reading or some other variation. */
	if(status) (void)printf("Exiting with error status %d\n",status);
	else       (void)puts("Exiting cleanly");

	return status;
}
