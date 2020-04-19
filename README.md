
# Object-Detection-System: Object detection, documentation and classification

## Installation

### Local Build
Software:
Visual Studio Code
Platformio

Hardware:
[ESP8266 NodeMCU Board](https://www.amazon.com/gp/product/B081CSJV2V/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1)
[Passive Infrared (PIR) sensor](https://www.amazon.com/gp/product/B012ZZ4LPM/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1)
[OV7670 Camera](https://www.amazon.com/gp/product/B07S66Y3ZQ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)

Schematics:
[Schematics](/schematics/KiCad.pdf)


### Remote Build
Travis CI

## Dependencies Setup (Connection)

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
`platformio.exe run --environment nodemcuv2 <`
=================================================================================== [SUCCESS] Took 2.15 seconds ===================================================================================

Environment    Status    Duration
-------------  --------  ------------
nodemcuv2      SUCCESS   00:00:02.146
embeddedtest   IGNORED
=================================================================================== 1 succeeded in 00:00:02.146 =================================================================================== 

## Test

`platformio.exe test --environment embeddedtest <`
3 Tests 0 Failures 0 Ignored
=================================================================================== [PASSED] Took 33.23 seconds =================================================================================== 

Test    Environment    Status    Duration
------  -------------  --------  ------------
*       nodemcuv2      IGNORED
*       embeddedtest   PASSED    00:00:33.234
=================================================================================== 1 succeeded in 00:00:33.234 =================================================================================== 


# Upload and Monitor
`platformio.exe run --target upload --target monitor --environment nodemcuv2 <`
=================================================================================== [SUCCESS] Took 22.55 seconds ===================================================================================

Environment    Status    Duration
-------------  --------  ------------
nodemcuv2      SUCCESS   00:00:22.547
embeddedtest   IGNORED
=================================================================================== 1 succeeded in 00:00:22.547 ===================================================================================
