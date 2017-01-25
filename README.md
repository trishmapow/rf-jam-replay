# CC1101-FSK
Attempt at RollJam, jam and replay keyless entry systems.

Ended up using GNURadio to record IQ data from an RTL-SDR then decoded it with a custom protocol made on wave-converter (another Github library) and then parsed the output to return the hex value of the transmission. 

Refer to https://github.com/paulgclark/waveconverter and [GNURadio](http://gnuradio.org/)
