"""
sample Python 2 Flask server with mix of spaces and tabs

Python 3 does not allow for mixed space/tab use
Python 2 highly recommends conversion to only spaces
(Source: https://www.python.org/dev/peps/pep-0008/#tabs-or-spaces)

The normalize-spaces executable can be used for proper conversion for both
"""

from flask import Flask

app = Flask(__name__)

@app.route('/')
def home():
	return 'Started Flask server on port 5000!'

if __name__ == "__main__":
	 app.run(debug=True)

