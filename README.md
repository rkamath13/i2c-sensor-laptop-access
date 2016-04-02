# i2c-sensor-laptop-access

**This Project is purely done for understanding the i2c-protocol and the drivers and sm-bus used for it on a laptop.
I have used a MCP9808 Temperature register to access my laptop's VGA port.**

*Disclaimer: you are responsible for any hardware damage done to your sensor or your Laptop*

**This project is done on a x86 system with a 32-bit Ubuntu OS**

The code uses two structures from the i2c-dev.h file which can be found in the linux source namely
```
struct i2c_rdwr_ioctl_data 
struct i2c_msg            
	```
The code also uses **ioctl** calls for reading and writing to the device.

In the source directory, there is a **driver code i2c-linux.c** which has 3 main functions
1. I2Copen()
2. I2Cmsg()
3. I2Cclose()

The functionality of the above 3 functions is defined in the comments sections of the code.
I have written a I2C device specific code on top of it for MCP9808 sensor.
I have also Provided a template .c file with instrructions if you want to write a code for any other specific I2C device

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
  
 ![connection](https://cloud.githubusercontent.com/assets/11395702/14223946/37164886-f840-11e5-95e7-d4eabc442053.jpg)
 
 
 ![setup](https://cloud.githubusercontent.com/assets/11395702/14223948/3a030ebc-f840-11e5-81ec-fd02f69273b8.JPG)
  
###Step 7:
  After you have made changes in the sensor-template.c and Makefile according to your sensor preference or if you are using the MCP9808 sensor which I am using, do the following
  ```
  $ make all
  $ sudo ./sensor-template
  ```
  *Make sure you run the executable as root*
  
  You will get the readings you want from the device right on the Terminal!!!
  
   ![output](https://cloud.githubusercontent.com/assets/11395702/14223947/3830799e-f840-11e5-920d-aa1d59a6bc4b.png)
