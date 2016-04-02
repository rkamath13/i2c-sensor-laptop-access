# i2c-sensor-laptop-access

##STEPS:

###Step 1:
  git clone this repository using the following command on your terminal:
  ```
  $git clone https://github.com/rkamath13/i2c-sensor-laptop-access.git
  ```
  
###Step 2:
  Install the following packages:
  ```
  $sudo apt-get install lm-sensors
  $sudo apt-get install i2c-tools
  ```
  lm-sensors and i2c-tools package is to gain the access of sm-bus of the laptop and detect the connected i2c-devices 
  
###Step 3:
  **Check the graphics driver your system is using.** 
  My laptop has Radeon graphics card.
  enable the kernel modules for your specific graphics driver
  ```
  $sudo modprobe i2c-dev
  $sudo modprobe radeonfb
  ```
  The above is for an ATI Radeon. You might need a different module specific to your system. 
  Use the command “sudo modprobe -l” or "lsmod" for a full list of kernel modules
  and try to locate one that matches your graphics chip vendor.

###Step 4:
  check the i2c-adapter your VGA/DVI/HDMI port uses using a
  ```
  $sudo i2cdetect -l
  ```
  you will get something like this in your terminal
  ```
  rkamath@rkamath:~$ sudo i2cdetect -l
  i2c-0	i2c       	i915 gmbus ssc                  	I2C adapter
  i2c-1	i2c       	i915 gmbus vga                  	I2C adapter
  i2c-2	i2c       	i915 gmbus panel                	I2C adapter
```
Since I am connecting the sensor to my VGA port in the laptop, My I2C adapter number is 2.

*If the output of i2cdetect does not mention any video ports (VGA, DVI, or HDMI), 
then it’s probable that the driver does not support I2C and this hack will not work, 
or a different video card module may simply need to be loaded.*

###Step 5:
  Change the parameters you need in the code:
  ```
  1. In the i2c-linux.c file change the adapter number to point it to the right file descriptor
  const static char device[] = "/dev/i2c-2";
  
  2. In the sensor-template.c file, give the device address of your sensor and the register address of the sensor from where 
  you want to read the data
 ```
 *If you are changing the file name of your program, make sure to update the Makefile*
 
 ###Step 6: 
 
  Connect the sensor to the Port using the follwing images:
  
  ![connection](https://raw.githubusercontent.com/rkamath13/i2c-sensor-laptop-access/blob/master/connection.jpg)
  ![connection](https://raw.githubusercontent.com/rkamath13/i2c-sensor-laptop-access/blob/master/setup.JPG)
  
  

  
