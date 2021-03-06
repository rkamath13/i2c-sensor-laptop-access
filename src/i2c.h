#ifndef __I2C_H__
#define __I2C_H__

typedef enum {
	I2C_ERR_NONE = 0,
	I2C_ERR_OPEN,
} ErrorCode;

extern int I2Copen(void), I2Cmsg(short,unsigned char *,int,unsigned char *,int);
extern void I2Cclose();

#endif /* __I2C_H__ */
