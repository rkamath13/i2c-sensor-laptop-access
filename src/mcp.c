#include <stdio.h>
#include <unistd.h>
#include "i2c.h"

static const short
	i2cAddress = 0x18,  /* Device I2C address as per datasheet */
	taReg      = 0x05,  /* Ambient temperature register   */
	configReg  = 0x01;  /* Configuration register         */

int main(int argc,char *argv[])
{
	int status;

	if(I2C_ERR_NONE == (status = I2Copen()))
	{
		unsigned char msg[2];

		/* Issue configuration command (2 bytes) */
		msg[0] = configReg;
		msg[1] = 0x00;      /* Default value */
		if(I2C_ERR_NONE == (status = I2Cmsg(i2cAddress,msg,2,NULL,0)))
		{
			unsigned char reply[2];

			/* Issue a series of temperature-reading commands
			   (1 byte each w/2-byte replies) */
			msg[0] = taReg;
			while(I2C_ERR_NONE == (status =
			  I2Cmsg(i2cAddress,msg,1,reply,2)))
			{
				float temp;
				int c;

				c = (reply[0]<<8) + reply[1];
				temp = c&0x0FFF;
				temp = temp/16;

				if(c&0x1000)
					temp = temp-256;

				(void)printf("Temperature: %.2f°C\n",
				  temp);

				sleep(1);
			}
		}

		I2Cclose();
	}

	/* Technically the clean exit case here will never happen (program
	   runs indefinitely until interrupted or I2Cmsg() fails), but it's
	   left here in case you want to change the program to perform a
	   single reading or some other variation. */
	if(status) (void)printf("Exiting with error status %d\n",status);
	else       (void)puts("Exiting cleanly");

	return status;
}
