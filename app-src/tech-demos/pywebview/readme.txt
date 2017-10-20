This is a demo of converting a web application to a windowed application using
pywebview (https://github.com/r0x0r/pywebview).  It renders the Holoseat App
mockup, so it is dependent on running the mockup in a separate process.  The demo
steps are:

1. Open console one
  a. activate virtualenv (in the app-src directory) 
  b. cd tech-demos\mockup\
  c. start mockup server with: python -m http.server
2. Open console two
  a. activate virtualenv (in the app-src directory)
  b. cd tech-demos\pywebview\
  c. start app demo with: python.exe .\app-window.py
