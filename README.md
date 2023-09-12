# **KNACKSAT 2 Program**

## **Objective Of Program**

This program controls a device that reads a RADFET. It measures the impact of radiation exposure on a 32 GB micro SD card and checks if the SD card experiences any bit flips.

  

## **Setup Before Programming**

### For Arduino IDE 
---
#### Install Board Manager
In the Arduino IDE go to **File** then **Preferences**

![Screenshot 2023-07-15 170731](https://github.com/KNACKSAT2-TGPS/KNACKSAT2-TGPS-Code/assets/77231097/32d6c89c-bec9-46f7-937a-3ace9f6cb1f4)

In **Additional Boards Manger URLs** place this link >> https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

![Screenshot 2023-07-15 170406](https://github.com/KNACKSAT2-TGPS/KNACKSAT2-TGPS-Code/assets/77231097/a1ed457a-18ea-4641-b70a-83d408fecdcd)

Then click **OK**  button.

In **Tools** click **Board** and find **Boards Manager**. 

![Screenshot 2023-07-15 170455](https://github.com/KNACKSAT2-TGPS/KNACKSAT2-TGPS-Code/assets/77231097/86db3cff-5713-40c8-ad49-26be0671d6a8)

Now search **pico** and **install**. Version that using with program >> **Version 2.7.0**

![Screenshot 2023-07-15 170650](https://github.com/KNACKSAT2-TGPS/KNACKSAT2-TGPS-Code/assets/77231097/ff91986d-26b8-495c-90e8-dbf2aa1a0a28)

**Original Github link** >> https://github.com/earlephilhower/arduino-pico#features.

#### Install Library
Download library from this link >> https://github.com/khoih-prog/RP2040_SD

To install the file go to the **Preferences** and copy pathfile
![Screenshot 2023-09-12 143327](https://github.com/KNACKSAT2-TGPS/KNACKSAT2-TGPS-Code/assets/77231097/9d546fa0-c269-4d80-bccd-6c88fe962ffa)

## **Description**
