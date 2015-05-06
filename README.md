# HttpClient

HttpClient is a library to make it easier to interact with web servers from MSP430 using Energia.
This library is a fork of the [Arduino Library](https://github.com/amcewen/HttpClient)

## Dependencies

- Requires the WiFi library found in Energia release 0101E0011 

## Installation

1. Download the latest version of the library from https://github.com/zlalanne/HttpClient/releases and save the file somewhere
1. In the Energia IDE, go to the Sketch -> Import Library -> Add Library... menu option
1. Find the zip file that you saved in the first step, and choose that
1. Check that it has been successfully added by opening the Sketch -> Import Library menu.  You should now see HttpClient listed among the available libraries.

## Usage

In normal usage, handles the outgoing request and Host header.  The returned status code is parsed for you, as is the Content-Length header (if present).

Because it expects an object of type Client, you can use it with any of the networking classes that derive from that.  Which means it will work with EthernetClient, WiFiClient and GSMClient.

See the examples for more detail on how the library is used.

