# CC1101-FSK
**NOTE:** This is not the final code. Needs to be implemented for each model of vehicle.

Attempt at RollJam, jam and replay keyless entry systems. Thank you to [Samy Kamkar](http://samy.pl/), [Github](https://github.com/samyk), who first provided me with the inspiration to perform software defined radio research, check out his more polished RollJam device [here](https://www.wired.com/2015/08/hackers-tiny-device-unlocks-cars-opens-garages/). 

Used GNURadio to record IQ data from an RTL-SDR then decoded it with a custom protocol made on wave-converter and parsed the output to return the hex value of the transmission. 

[Latest version utilises a Yard Stick One RF Transceiver with RFCat firmware,](https://greatscottgadgets.com/yardstickone/) approx $100USD. Thanks to [RyscCorp](https://ryscc.com/) for sponsoring my purchase.

Will try to transfer register settings when testing is complete to a cheaper CC1101 chip/$1 433MHz chip and Arduino.

Refer to https://github.com/paulgclark/waveconverter and [GNURadio](http://gnuradio.org/)

Further documentation will be uploaded in a few months time, including a paper on implications and recommendations for manufacturers, end-users and third parties.

### Jamming
Attach an antenna to pin 12 of the GPIO header.
Note that output is unfiltered and creates nasty harmonics, so it may not be legal.
`sudo ./rpitx -m VFO -f [FREQ IN HZ]`

## Screenshots
**Inspectrum view of the IQ taken from GNURadio**
![Screenshot 1](https://github.com/trishmapow/CC1101-FSK/blob/master/Inspectrum_CORRECT2MHz_Initial.png "Inspectrum")
**Wave Converter demod settings**
![Screenshot 2](https://github.com/trishmapow/CC1101-FSK/blob/master/WaveConverterBeginningTransmissionDemod.png "Wave Converter")
