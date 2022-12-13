from serial import Serial
import requests, time

#Comunicación serial con Arduino
arduino = Serial(port='COM2', baudrate=9600, timeout=.1)

while True:
    # Informacion que manda arduino
    data = arduino.readline().decode("utf-8")

    if data != "": # Para que no imprima basura
        print(data)

        # Request a la API
        # x = requests.get('https://w3schools.com/python/demopage.htm')
        # print(x.text)

        # Informacion que se manda al arduino
        arduino.write(bytes("a", 'utf-8'))
        # arduino.write(bytes("1,1,2,1,0,1,1,0,1,1,1,1,1,1,1,0", 'utf-8'))


