# What's this?
Vulture browser is a fork of Falkon browser, that has KDE bloatware removed
## Why?
- Primary goal: Maemo Leste N900 Falkon port
- I don't want KDE installed on my system alongside with this nice browser
## So, what is done at this moment?
Smart people implement things that I remove

Removed gnome-keyring addon, Kf5 bloatware, updater

It now uses mobile user agent by default, it probably will alleviate Omap3430 suffering

You can scroll the webpage using swipes.

It ain't much but it's honest work

# What does not work
OCs addons installer. I'll replace KDE-related code soon. The only part where the KDE framework is needed is.. zip file reader. Great.
# TODO
- Small resolutions optimization
- Touch screen gestures support
- Code optimization
- Addons installer
- Is Qt WebEngine optimization possible?
- Yes
# SECURITY RISK
- Falkon uses QWebEngine, which has limited security support on Debian.

- That means that the only free and "secure" browser for Linux is Firefox.

- If it runs code, it runs code

- For the memory saving reasons, Vulture Browser has WebEngine sandboxing disabled

- Sandboxing does not mean your browser is secure anyway

- Built-in adblock is doing better job securing your browser(You still need to enable it manually)

- To sum up, don't use it to visit untrusted websites, mkay?

- Being in google search results does not make the website trusted

To run vulture browser with sandbox enabled:

```
falkon --private-browsing
```

Default command(sandbox disabled):

```
env QTWEBENGINE_DISABLE_SANDBOX=1 falkon --private-browsing
```


# SYSTEM REQUIREMENTS

Your device must have at least 1024 MBs of RAM+SWAP

To run it on Nokia N900 you'll need to enable SWAP for at least 768 MB

Don't expect smooth surfing

Cmake can't do without filling your directory with trash,so you better be doing out-of-source build

Also, right now it uses falkon paths, images, etc.

# Contributing
If you got something to implement, feel free to add Pull Requests, Issues, or even email me
I would appreciate your attention
## Contributing to parent project
At this moment, there's nothing I can offer them, but later maybe
# Licensing
As Falkon, this project is licensed under GNU GPL v3 license. See COPYING
# Changes
Are extremely transparent
```
git clone https://github.com/KDE/falkon
cd falkon
git checkout 039ac5b2ba859bbcadf2240ddeb308e2041ba4f5
cd ..
git clone <this repo>
diff -r falkon vulture-browser
```

# Building from source:

It seems possible to build it on N900 itself, but better don't.Use QEMU+debootstrap+chroot environment.

## Dependencies
```
apt install cmake build-essential qt5base-dev libqtwebengine5 qtdeclarative5-dev libqt5webchannel5-dev libqt5webengine5-dev qtwebengine5-dev libx11-xcb-dev libxcb-util-dev libqt5x11extras5-dev qttols5-dev extra-cmake-modules
```
## Building

```sh
mkdir build && cd build
cmake ..
make && make install
```