/****************************************************************************
 File        : i2c-linux.c
 Description : Linux-specific code for communicating with the DDC (I2C) bus
               on a video out port.
 History     : 5/7/2008  P. Burgess  Initial implementation
 Thanks to   : Benny Hsieh for donation of development hardware.  Authors of
               ddcci-tool (now ddccontrol) for Linux I2C programming insights.
 License     : Copyright 2008 Phillip Burgess

               This file is part of The 25 Cent I2C Adapter Project.

               The 25 Cent I2C Adapter Project is free software: you can
               redistribute it and/or modify it under the terms of the GNU
               General Public License as published by the Free Software
               Foundation, either version 3 of the License, or (at your
               option) any later version.

               The 25 Cent I2C Adapter Project is distributed in the hope that
               it will be useful, but WITHOUT ANY WARRANTY; without even the
               implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
               PURPOSE.  See the GNU General Public License for more details.

               You should have received a copy of the GNU General Public
               License along with The 25 Cent I2C Adapter Project.  If not,
               see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "i2c.h"

/* At the moment this is rigged for a single I2C bus.  If support for multiple
   buses is desired in the future, some manner of non-OS-specific per-bus
   reference handle should be passed back to the calling code. */
static int fd = -1;  /* File descriptor of open device */

/* Similarly kludgey - change this to the device file corresponding to the
   I2C bus of interest.  This was not made a parameter to I2Copen() as I
   wanted the calling code to be platform-independent.  Needless to say,
   this code is more just a starting point than a comprehensive package. */
const static char device[] = "/dev/i2c-1";

/****************************************************************************
 Function    : I2Copen()
 Description : Open connection to I2C bus.
 Parameters  : None.
 Returns     : I2C_ERR_NONE on success, I2C_ERR_OPEN on error.
 ****************************************************************************/
int I2Copen()
{
	if((fd = open(device,O_RDWR)) >= 0) return I2C_ERR_NONE;

	(void)puts("Could not open port (are you running as root?)");
	return I2C_ERR_OPEN;
}

/****************************************************************************
 Function    : I2Cmsg()
 Description : Issue I2C request and/or read response.
 Parameters  : short
               unsigned char *  Pointer to data to be sent (or NULL).
               int              Size of above data, in bytes (or 0).
               unsigned char *  Pointer to buffer to hold device response
                                data.  Pass NULL if no response is required
                                or anticipated.
               int              Size of response data, in bytes (0 if none).
 Returns     : 0 on success, else various OS-specific error codes.
 ****************************************************************************/
int I2Cmsg(
  short           const address,
  unsigned char * const sendBuf,
  int             const sendBytes,
  unsigned char * const replyBuf,
  int             const replyBytes)
{
	struct i2c_rdwr_ioctl_data rdwr;
	struct i2c_msg             msg;
	int                        i;

	/* I2C addresses are supposed to be 7 bits (and in fact the ioctl()
	   calls will fail if an address exceeding this range is passed).
	   But some devices (such as the Mindsensors servo controller) are
	   documented as having a default address outside this range (e.g.
	   0xb0).  It appears they're considering the read/write bit that
	   follows the 7-bit address as part of the address itself.  If
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

/****************************************************************************
 Function    : I2Cclose()
 Description : Closes the previously-opened I2C bus connection.
 Parameters  : None.
 Returns     : None (void).
 ****************************************************************************/
void I2Cclose()
{
	if(fd >= 0)
	{
		(void)close(fd);
		fd = -1;
	}
}
