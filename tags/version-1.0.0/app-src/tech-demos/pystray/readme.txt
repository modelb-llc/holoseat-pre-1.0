This demo began life as a basic demo of using pystray to create system tray icons.
It has since morphed to a complete demo of the mockup UI for the Holoseat
desktop app, combining:

* the mockup UI hosted in the Python SimpleHTTPServer running in its own thred
* a pywebview window running in its own thread to render the mockup UI
* pystray as the main application thread to provide the long lived system tray icon

Note, the demo is completely self bootstrapping.  Starting the pystray demo script
will start all three demos listed above.

The demo steps are:

1. activate virtualenv (in the app-src directory)
2. cd to tech-demos\pystray\
4. start app demo with: python.exe .\pystray-demo.py

Once started, the demo will add a Holoseat 'h' icon to the system tray.  You can
launch the mockup UI by clicking on the 'h' or right-clicking on the 'h' and
selecting Configure.  You can exit the demo by right-clicking on the 'h' and
selecting Exit.
