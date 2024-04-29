# xwiimotelib - library to communicate with Nintendo Wii / Wii U remotes

The **xwiimotelib** is a communication I/O server for Nintendo Wii / Wii U remotes (for Linux OS only)

### Supported features
  * finds and communicates with Wii remotes using Linux kernel HID driver for Nintendo Wii / Wii U peripherals (`hid-wiimote`)
  * the particular paired Wii remote can be specified in Device attribute, either by order number (1-4) or by specifying Linux device path
  * supports different Wii and Nunchuk buttons, joystick and tilt events and exposes them as CDP (output) signals to be used in CDP applications
  * supports turning the Wii remote rumble motor on/off via Rumble (input) CDP signal

### Dependencies
  * Linux system with Nintendo Wii / Wii U remote HID driver support in kernel (since kernel versions 3.11)
  * **xwiimote** - https://github.com/xwiimote/xwiimote (minmally needed source code is included with the library)


### Cloning

The library includes [**xwiimote**](https://github.com/xwiimote/xwiimote) as a git submodule. Therefore you have to clone the library with submodules included. Using git command line this can be done by adding the `--recursive` option, like this:
```
git clone --recursive https://github.com/CDPTechnologies/xwiimotelib.git
```


### Usage

Before you can use the Wii Remote make sure it is paired with the Linux box and the corresponding kernel driver is loaded.

Optionally, you can install **xwiimote** binary (for example, in Debian systems using the command `sudo apt install xwiimote`). Then you can test the connection of the Wii remote by entering the command 

```
xwiimote list
```
That command output should list the connected Wii remote(s). If the list is empty then there is a problem with the connection and therefore also this library is not able to detect the Wii remote.

See more instructions and troubleshooting on the [xwiimote manual page](http://xwiimote.github.io/xwiimote/)