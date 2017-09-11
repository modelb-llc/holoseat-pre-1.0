This is a demo of converting a web application to a windowed application using
pywebview (https://github.com/r0x0r/pywebview).  It renders the Holoseat App
mockup, so it is dependent on running the mockup in a separate process.  The demo
steps are:

1. Open console one
  a. cd to tech-demos\
  b. activate virtualenv
  c. cd mockup\
  d. start mockup server with: python -m http.server
2. Open console two
  a. cd to tech-demos\
  b. activate virtualenv
  c. cd pywebview\
  d. start app demo with: python.exe .\app-window.py
