# tempSensorThingsBoard_NodeMCU
![head](images/NodeMCU_DHT22_Thingsboard_BREADBOARD.png)
A firmware for NodeMCU device connected to a thingsboard server (raspberry PI 3) both running in a local network.

## NodeMCU Firmware update

1. Install [Docker](https://www.docker.com/) by following steps detailed in [docker installation guide](https://docs.docker.com/install/linux/docker-ce/ubuntu/)
2. Download docker image for nodemcu:
```
sudo docker pull marcelstoer/nodemcu-build
```
3. Build the firmware:
```
sudo docker run --rm -ti -v ~/samples/nodemcu/nodemcu-firmware:/opt/nodemcu-firmware marcelstoer/nodemcu-build
```
4. Flash the firmware (change "XXXX" by your version number and include your **full** path):
```
sudo ./esptool.py -b 115200 write_flash --flash_mode dio --flash_size 4MB 0x0 ~/[PATH_TO_YOUR_PROJECT]/nodemcu-firmware/bin/nodemcu_integer_master_XXXX.bin --verify
```

## NodeMCU Application Files Flash

1. Copy all files to be uploaded to "luatool" folder.
```
cd lua
cp *.lua ../luatools/luatools
```
2. Flash every file (check your USB Port using dmesg and change "ttyUSBX" to the correct value):
```
sudo ./luatool.py --port /dev/ttyUSBX -b 115200 --src config.lua --dest config.lua -v
sudo ./luatool.py --port /dev/ttyUSBX -b 115200 --src dht11.lua --dest dht11.lua -v
sudo ./luatool.py --port /dev/ttyUSBX -b 115200 --src init.lua --dest init.lua -v
```

## Thingsboard.io platform configuratioin

You can check details of a demo **dashboard** using 2 nodeMCU devices measuring temperature and humidity in two different rooms of a house **[HERE](http://demo.thingsboard.io/dashboards/6e997810-3f82-11e8-82d4-c3b186e30863?publicId=d51d55a0-ff9c-11e7-abe9-1d8d2edf4f93)**.

![Thingsboard.io dashboard](/images/dashboard.png)


## Hardware

### NodeMCU
![NodeMCU Pinout](/images/nodemcu-pinout.jpg)

### DHT22 (Temperature - Humidity Sensor)
![DHT22 Pinout](/images/DHT22.png)

### Schematics
![NodeMCU+DHT22 Schematics](/images/NodeMCU_DHT22_Thingsboard_BREADBOARD.png)

### 3D Printing
You can download all files in **[Thingiverse]**(https://www.thingiverse.com/thing:2330811).

![Box closure](/images/box1.jpg)
![Box closure](/images/box2.jpg)
