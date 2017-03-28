# CC1101-FSK
**NOTE:** I am not uploading the final code 1) because it's actually functional and 2) because I'm pretty sure you can't do this for a live system still in use. Also, there is no jamming code here. If you read into it, you can try it yourself, that's what I did.

**DISCLAIMER:** I am not a lawyer, use at your own risk, don't break into other people's things, don't blame me for what happens.

Attempt at RollJam, jam and replay keyless entry systems. Thank you to [Samy Kamkar](http://samy.pl/), [Github](https://github.com/samyk), who first provided me with the inspiration to perform software defined radio research, check out his more polished RollJam device [here](https://www.wired.com/2015/08/hackers-tiny-device-unlocks-cars-opens-garages/) (also for helping me out with some technical questions on Reddit). 

Ended up using GNURadio to record IQ data from an RTL-SDR then decoded it with a custom protocol made on wave-converter (another Github library) and then parsed the output to return the hex value of the transmission. 

**[LATEST VERSION USES A YARD STICK ONE WITH RFCAT FIRMWARE](https://greatscottgadgets.com/yardstickone/) approx $100USD**
Will try to transfer register settings when testing is complete to a cheaper CC1101 chip and Arduino.

Refer to https://github.com/paulgclark/waveconverter and [GNURadio](http://gnuradio.org/)

## Screenshots
**Inspectrum view of the IQ taken from GNURadio**
![Screenshot 1](https://github.com/trishmapow/CC1101-FSK/blob/master/Inspectrum_CORRECT2MHz_Initial.png "Inspectrum")
**Wave Converter demod settings**
![Screenshot 2](https://github.com/trishmapow/CC1101-FSK/blob/master/WaveConverterBeginningTransmissionDemod.png "Wave Converter")
