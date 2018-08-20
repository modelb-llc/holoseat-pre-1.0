This is the root directory of the Holoseat configuration app (or App for short).  All of 
the code under this directory is intended to run inside a common virtualenv.  After installing 
and activating the virtualenv, you can install the required packages by running:

pip install -r requirements.txt

The sub-directories contain the following content:

- holoseat: source code/module for the Holoseat app
- {holoseat_env}: assumed name for the shared virtualenv
- tech-demos: contains a series of test scripts to demo key technologies for the app
- visual-design: contains customized Bootstrap for the app 

You can run the Holoseat app with the following command:
	python -m holoseat

Use the '-d' option to run the app in debug mode.  This will enable debugging in the 
Flask UI and Tornado API.  It will also enable the Serial Monitor in the app.