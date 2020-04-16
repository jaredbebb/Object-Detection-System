
This directory is intended for PIO Unit Testing and project tests.

Unit Testing is a software testing method by which individual units of
source code, sets of one or more MCU program modules together with associated
control data, usage procedures, and operating procedures, are tested to
determine whether they are fit for use. Unit testing finds problems early
in the development cycle.

More information about PIO Unit Testing:
- https://docs.platformio.org/page/plus/unit-testing.html

## Setup

## Need to have config file $PROJECT_ROOT/conf/config.json with schema. Maximum characters present in file is 512.


{
    "AdaFruit":{
        "AIO_FEED":"/feeds/FEEDNAME",
        "AIO_USERNAME":"ADAFRUIT_IO_USERNAME",
        "AIO_KEY":"ADAFRUIT_IO_KEY",
        "AIO_SERVERPORT":1883,
        "AIO_SERVER":"io.adafruit.com",
        "AIO_USERNAME_FEED":"ADAFRUIT_IO_USERNAME/AIO_FEED"
    },
    "Network":{
        "WLAN_SSID":"WLAN_SSID",
        "WLAN_PASS":"WLAN_PASSWORD"
    }
}

# Build and Test
## Build
.platformio\penv\Scripts\platformio.exe run --target upload