from flask import Flask, jsonify, request, render_template

app = Flask(__name__)

# Temporary data variables.
current_distance_cm = None
current_distance_inches = None

# Homepage route
@app.route('/')
def index():
    return render_template('index.html')

# Route to receive data from Arduino
@app.route('/data')
def data():
    global current_distance_cm, current_distance_inches

    # Retrieve 'cm' and 'inches' values from GET parameters
    cm = request.args.get('cm')
    inches = request.args.get('inches')

    # Update values when data is received
    if cm and inches:
        current_distance_cm = cm
        current_distance_inches = inches

    # Return the response in JSON format
    return jsonify({'cm': current_distance_cm, 'inches': current_distance_inches})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
