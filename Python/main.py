from serial import Serial
import requests, time, json

#Comunicación serial con Arduino
arduino = Serial(port='COM2', baudrate=9600, timeout=.1)

while True:
    try:
        # Informacion que manda arduino
        data = arduino.readline().decode("utf-8")

        if data != "": # Para que no imprima basura
            li = list(data.split(","))
            c = 0
            for i in li:
                li[c] = int(i)
                c = c + 1

            #print(li)
            # Request a la API
            # Se obtiene el contenido del parqueo para verificar si se apartó algo
            x = requests.get("http://54.161.172.138:4000/verParqueo")
            x = json.loads(x.text).get("parqueo")

            #print("Recibo de la app")
            #print(x)
            c = 0
            for i in x:
                if i == 2: #Verificamos si hay apartados del lado de la app
                    li[c] = 2

                #Se da en el caso que el tiempo de la reserva se termine
                if li[c] == 2 and i == 0:
                    li[c] = 0

                c = c + 1

            # Se manda el estado de los parqueos detectado por el circuito
            estado = {'parqueos': li}
            x = requests.post("http://54.161.172.138:4000/setParqueo", json = estado)
            if (json.loads(x.text).get("mensaje")) == "OK":
                print("Se envió")
                print(li)

            # Informacion que se manda al arduino
            cadena = ""
            c = 0
            for i in li:
                if c < 31:
                    cadena = cadena + str(li[c]) + ","
                else:
                    cadena = cadena + str(li[c])
                c += 1
            arduino.write(bytes(cadena, 'utf-8'))
    except:
        continue