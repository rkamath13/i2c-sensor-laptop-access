/****************************************************************************
 File        : i2c.h
 Description : Header file for use with i2c library.  Not much here at the
               moment, just the beginnings of an error code list, and a
               handful of function prototypes.
 History     : 4/1/2008  P. Burgess  Initial implementation
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

#ifndef __I2C_H__
#define __I2C_H__

typedef enum {
	I2C_ERR_NONE = 0,
	I2C_ERR_OPEN,
} ErrorCode;

extern int
	I2Copen(void),
	I2Cmsg(short,unsigned char *,int,unsigned char *,int);
extern void
	I2Cclose();

#endif /* __I2C_H__ */
