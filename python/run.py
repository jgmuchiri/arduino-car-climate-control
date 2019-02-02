import serial
from sqlite3 import dbapi2 as sqlite3
from flask import Flask, render_template, request, flash, _app_ctx_stack

# configuration
DATABASE = '/tmp/flaskr.db'
DEBUG = True
SECRET_KEY = '1235655'
USERNAME = 'admin'
PASSWORD = 'default'

app = Flask(__name__)
app.config.from_object(__name__)
app.config.from_envvar('config.default', silent=True)

SERIAL_PORT = 'COM3'  # COM3 , /dev/ttyACM0
BAUDRATE = 9600
SERIAL_TIMEOUT = 0


def init_db():
    """Creates the database tables."""
    with app.app_context():
        db = get_db()
        with app.open_resource('schema.sql', mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()

def get_db():
    """Opens a new database connection if there is none yet for the
    current application context.
    """
    top = _app_ctx_stack.top
    if not hasattr(top, 'sqlite_db'):
        sqlite_db = sqlite3.connect(app.config['DATABASE'])
        sqlite_db.row_factory = sqlite3.Row
        top.sqlite_db = sqlite_db

    return top.sqlite_db


@app.teardown_appcontext
def close_db_connection(exception):
    """Closes the database again at the end of the request."""
    top = _app_ctx_stack.top
    if hasattr(top, 'sqlite_db'):
        top.sqlite_db.close()


# initialize serial and deliver payload
def connect_serial(a):
    try:
        ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=SERIAL_TIMEOUT)
        ser.write(a.encode())
        ser.close()
    except:
        return 'error'

# update db status
def update_db():
    db = get_db()
    db.execute('UPDATE settings (value) VALUES(?) WHERE option=servo_pos', a)
    db.commit()


# dashboard
@app.route('/', methods=['GET'])
def index():
    db = get_db()
    cur = db.execute('select * from settings')
    settings = cur.fetchall()
    return render_template('dashboard.html', settings=settings)


# send controls commands to serial - controls ac and fans
@app.route('/controls', methods=['GET', 'POST'])
def controls():
    if request.method == 'POST':
        a = request.form['value']  # get value sent
        connect_serial(a)  # send data to serial

        update_db(a)
    return 'error'


# send switch commands to serial - controls vents
@app.route('/switches', methods=['GET', 'POST'])
def switches():
    if request.method == 'POST':
        a = request.form['switcher']  # get value sent
        connect_serial(a)
    return ''


if __name__ == '__main__':
    init_db()
    app.run()
