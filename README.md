# Toralize: Tor Proxy Connector

### Introduction

The Tor Proxy Connector is a C-based application designed to facilitate secure and anonymous network connections through the Tor network using the [SOCKS4](https://www.openssh.com/txt/socks4.protocol) protocol. This project implements a custom connect function that intercepts socket connection calls and routes them through a Tor proxy, allowing applications to benefit from Tor's privacy features without requiring extensive modifications to existing code.

### Features

- `SOCKS4 Proxy Connection` : Automatically connects to a specified Tor proxy (default: 127.0.0.1:9050) using the SOCKS4 protocol.
- `Seamless Integration` : Intercepts the standard connect function, allowing existing applications to use the Tor network transparently.
- `Error Handling` : Provides error messages and logging to assist with troubleshooting connection issues.
- `Memory Management` : Ensures proper allocation and deallocation of memory for requests and responses.

### Project Structure
The project includes the following key components:

- Main Functionality: The core connection logic is implemented in a custom connect function.
- Request/Response Handling: Functions to create and handle requests and responses to and from the Tor proxy.
- Socket Management: Uses standard socket APIs to establish connections and communicate with the proxy.

### Getting Started
#### Prerequisites
Install the Tor service.

```
supo apt install tor
```

Installation
Clone the Repository:
```
git clone git@github.com:Fateskink/toralize.git

cd toralize
```

Build program
```
make
```

Locate the Shared Library:
Use the following command to get the current location of toralize.so:
```
pwd
```

Set Up the Bash Script:
Create a bash script file named toralize with the following contents to set the LD_PRELOAD environment variable:
```
#!/bin/bash
export LD_PRELOAD="/path/to/toralize.so"
${@}
unset LD_PRELOAD
```
Move the Script to a System Path:
Move the toralize script to `/usr/bin` to make it accessible from anywhere:

```
sudo mv toralize /usr/bin/
sudo chmod +x /usr/bin/toralize
```

PROXY: The IP address of the Tor proxy (default is 127.0.0.1).
PROXYPORT: The port number of the Tor proxy (default is 9050).
Usage
Once the application is set up and running, it will intercept socket connection calls and route them through the specified Tor proxy. You can integrate this functionality into existing applications that utilize network sockets.

### Acknowledgments

The Tor Project for its commitment to privacy and anonymity online.
The open-source community for their valuable resources and tools.
