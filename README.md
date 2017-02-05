# CC1101-FSK
Attempt at RollJam, jam and replay keyless entry systems.

Ended up using GNURadio to record IQ data from an RTL-SDR then decoded it with a custom protocol made on wave-converter (another Github library) and then parsed the output to return the hex value of the transmission. 

Refer to https://github.com/paulgclark/waveconverter and [GNURadio](http://gnuradio.org/)

## Screenshots
**Inspectrum view of the IQ taken from GNURadio**
![Screenshot 1](https://github.com/trishmapow/CC1101-FSK/blob/master/Inspectrum_CORRECT2MHz_Initial.png "Inspectrum")
**Wave Converter demod settings**
![Screenshot 2](https://github.com/trishmapow/CC1101-FSK/blob/master/WaveConverterBeginningTransmissionDemod.png "Wave Converter")
