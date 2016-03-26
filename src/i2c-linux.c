#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "i2c.h"

static int fd = -1;  /* File descriptor of open device */

/* Change this to the device file corresponding to the
   I2C bus of interest. Download i2c-tools and then do sudo i2cdetect -l to check 
   for all the i2c devices in the laptop, check the file created by the VGA port
   will be either i2c-1 or i2c-2 */

const static char device[] = "/dev/i2c-1";

int I2Copen()
{
	if((fd = open(device,O_RDWR)) >= 0) return I2C_ERR_NONE;

	(void)puts("Could not open port (are you running as root?)");
	return I2C_ERR_OPEN;
}

int I2Cmsg(
  short           const address,     // i2c address of the slave device
  unsigned char * const sendBuf,    // Pointer to data to be sent (or NULL)
  int             const sendBytes,  // Size of data in bytes (or 0).
  unsigned char * const replyBuf,   // Pointer to buffer to hold device response data.  Pass 0 if no response is anticipated.
  int             const replyBytes  //Size of response data, in bytes (0 if none).
)
{
	struct i2c_rdwr_ioctl_data rdwr;
	struct i2c_msg             msg;
	int                        i;

	/* I2C addresses are supposed to be 7 bits (and in fact the ioctl()
	   calls will fail if an address exceeding this range is passed). If 
	   the address passed exceeds the 7-bit limit, shift right by one
	   to strip the R/W bit and put the address within the valid range. */
	msg.addr   = (address & 0x80) ? (address >> 1) : address;
	rdwr.msgs  = &msg;
	rdwr.nmsgs = 1;

	if(sendBuf && (sendBytes > 0))
	{
		msg.flags = 0;
		msg.buf   = sendBuf;
		msg.len   = sendBytes;

		if((i = ioctl(fd,I2C_RDWR,&rdwr)) < 0) return i;
	}

	if(replyBuf && (replyBytes > 0))
	{
		msg.flags = I2C_M_RD;
		msg.buf   = replyBuf;
		msg.len   = replyBytes;

		if((i = ioctl(fd,I2C_RDWR,&rdwr)) < 0) return i;
	}

	return I2C_ERR_NONE;
}


void I2Cclose()
{
	if(fd >= 0)
	{
		(void)close(fd);
		fd = -1;
	}
}
