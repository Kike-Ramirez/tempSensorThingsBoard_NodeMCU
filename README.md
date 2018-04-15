# tempSensorThingsBoard_NodeMCU
![head](images/nodemcu_dht22.png)
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
