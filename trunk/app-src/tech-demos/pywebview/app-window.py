# open issue with demo - icon in taskbar.  See
# https://github.com/r0x0r/pywebview/issues/91 for fix

import webview

webview.create_window('Holoseat', 'http://localhost:8000', width=768,
    height=640, resizable=False)
