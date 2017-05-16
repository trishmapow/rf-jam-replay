# CC1101-FSK
**NOTE:** I am not uploading the final code because it's actually functional and thus I'm probably not allowed to release a vulnerability like this (even if it is well known). Also, there is no jamming code here. 

Attempt at RollJam, jam and replay keyless entry systems. Thank you to [Samy Kamkar](http://samy.pl/), [Github](https://github.com/samyk), who first provided me with the inspiration to perform software defined radio research, check out his more polished RollJam device [here](https://www.wired.com/2015/08/hackers-tiny-device-unlocks-cars-opens-garages/) (also for helping me out with some technical questions). 

Ended up using GNURadio to record IQ data from an RTL-SDR then decoded it with a custom protocol made on wave-converter (another Github library) and then parsed the output to return the hex value of the transmission. 

**[Latest version uses the amazing Yard Stick One RF Transceiver with RFCat firmware,](https://greatscottgadgets.com/yardstickone/) approx $100USD**. Thanks to [RyscCorp](https://ryscc.com/) for giving me a much needed student discount.

Will try to transfer register settings when testing is complete to a cheaper CC1101 chip/$1 433MHz chip and Arduino.

Refer to https://github.com/paulgclark/waveconverter and [GNURadio](http://gnuradio.org/)

## Screenshots
**Inspectrum view of the IQ taken from GNURadio**
![Screenshot 1](https://github.com/trishmapow/CC1101-FSK/blob/master/Inspectrum_CORRECT2MHz_Initial.png "Inspectrum")
**Wave Converter demod settings**
![Screenshot 2](https://github.com/trishmapow/CC1101-FSK/blob/master/WaveConverterBeginningTransmissionDemod.png "Wave Converter")
