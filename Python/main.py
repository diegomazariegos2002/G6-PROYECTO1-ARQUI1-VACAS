from serial import Serial
import requests, time, json

#Comunicación serial con Arduino
arduino = Serial(port='COM2', baudrate=9600, timeout=.1)

print("Funciona")
while True:
    try:
        
        # Informacion que manda arduino
        data = arduino.readline().decode("utf-8")

        if data != "": # Para que no imprima basura
            li = list(data.split(","))
            print(li)
            c = 0
            for i in li:
                li[c] = int(i)
                c = c + 1

            
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

            # Obtener el estado de la alarma
            y = requests.get("http://54.161.172.138:4000/getActivacionAntiRobo")
            y = json.loads(y.text).get("activacionAntiRobo")
            print(y)

            # Se manda el estado de los parqueos detectado por el circuito
            estado = {'parqueos': li}
            x = requests.post("http://54.161.172.138:4000/setParqueo", json = estado)
            if (json.loads(x.text).get("mensaje")) == "OK":
                print("Se envió")
                print(li)

            

            # Informacion que se manda al arduino
            cadena = ""
            for i in li:
                cadena = cadena + str(i) + ","

            c = 0
            for i in y:
                if c < 15:
                    if i:
                        cadena = cadena + str(1) + ","
                    else:
                        cadena = cadena + str(0) + ","
                else:
                    if i:
                        cadena = cadena + str(1)
                    else:
                        cadena = cadena + str(0)
                c = c + 1
                
            arduino.write(bytes(cadena, 'utf-8'))

    except Exception as e:
        print(
        type(e).__name__,          # TypeError
        __file__,                  # /tmp/example.py
        e.__traceback__.tb_lineno  # 2
        )
        continue