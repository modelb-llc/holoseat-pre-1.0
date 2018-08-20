This is a demo of using Flask and Jinja2 to host the UI for the application.  It
includes demo macros for managing the navigation bar.

* nav_link - Create single entry in navbar that will be active when corresponding
page is loaded.
* nav_menu - Create a menu entry in the navbar that will be active when any of its
pages is loaded.

The code is a modified version of the example from
https://realpython.com/blog/python/primer-on-jinja-templating/

Note, one of the most important parts of this demo is the resolution to the slow
performance of the demo UI in pywebview by enabling threading in Flask with
    app.run(threaded=True)
Thanks to this post for the answer - https://stackoverflow.com/a/14823968

The demo steps are:

1. activate virtualenv (in the app-src directory)
2. cd to tech-demos\flask\
3. start app demo with: python.exe .\run.py

You can use step 2 of the pywebview demo or a web browser (http://localhost:8000)
to observe the web pages in the demo.
