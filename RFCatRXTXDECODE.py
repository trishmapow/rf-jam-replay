from rflib import *
import sys
import bitstring
import time

def init(device):
    device.setFreq(433911000) #433.911MHz
    device.setMdmModulation(MOD_2FSK) #2FSK modulation
    device.setMdmDeviatn(37500) #39.5kHz deviation, now 37.5
    device.setMdmDRate(4111) #4k baud
    device.setMdmChanBW(125000) #125k channel bandwidth
    device.setMdmChanSpc(200000)
    #device.setPktPQT(0) #Disable preamble quality threshold

    device.setMdmNumPreamble(255) #Number of preamble symbols, 255 max, regularly 112

    """ENABLE THIS TO FILTER"""
    device.setMdmSyncMode(1) #What is this?
    #device.setMdmSyncMode(0)
    #device.setMdmSyncWord(0xaaaa)
    device.setMdmSyncWord(0xcccc) #Sync word

    #device.setMdmNumPreamble(0)
    device.setMaxPower()
    device.makePktFLEN(100) #400 binary symbols, ref. inspectrum
    #device.lowball(0) #More garbage

codes = []

def rx(device):
    print d.reprRadioConfig()

    while not keystop():
        try:
            pkt, ts = device.RFrecv()
            hxval = pkt.encode('hex')
            print "Received: %s" % hxval
            codes.append(hxval)
        except ChipconUsbTimeoutException:
            pass

    sys.stdin.read(1)

def replay(device):
    for code in codes:
        codeb = bitstring.BitArray(hex=code).tobytes()
        print str(codeb)
        device.RFxmit(codeb)
        time.sleep(1)

def mreplay(device, data):
    device.RFxmit(data)

"""CREDITS: http://labs.inguardians.com/radio-communication-analysis-using-rfcat/"""
def str2hex(data):
    tmp = ""
    for e in range(0,len(data),2):
        tmp += data[e:e+2].decode('hex_codec')
    print tmp
    return tmp

def cls():
    codes = []
