"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.indexController = void 0;
let parqueo = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
/*
    disponible = 0
    ocupado = 1
    reservado = 2
*/
let propietarios = [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1];
//si esta activa o no 
let activacionAntiRobo = [false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false];
let activacionReserva = [false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false];
// si esta sonando o no
let alarmaAntiRobo = false;
let alarmaReserva = [false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false];
let tiempo = 300000;
let pos = -1;
let usuarios = [
    {
        "usuario": "diegomaza",
        "pass": "1234"
    },
    {
        "usuario": "estuardoson",
        "pass": "1234"
    },
    {
        "usuario": "angelmarro",
        "pass": "1234"
    },
    {
        "usuario": "pikaguty",
        "pass": "1234"
    }
];
class IndexController {
    prueba(req, res) {
        res.json({ "funciona": "la api" });
    }
    /*
        retorna el arreglo del parqueo, no recibe nada
    */
    verParqueo(req, res) {
        res.json({ "parqueo": parqueo });
    }
    /*
        setter de parqueos
        recibe
        {"parqueos":[]}
    */
    setParqueo(req, res) {
        parqueo = req.body.parqueos;
        res.json({ "mensaje": "OK" });
    }
    /*
       retonrna el estado del parqueo en nummeros, no recibe nada
       {
           "disponibles": number,
           "ocupados": number,
           "reservados": number
       }
   */
    estadoParqueo(req, res) {
        let disponible = 0;
        let ocupado = 0;
        let reservado = 0;
        for (let i = 0; i < 32; i++) {
            if (parqueo[i] == 0) {
                disponible += 1;
            }
            else if (parqueo[i] == 1) {
                ocupado += 1;
            }
            else {
                reservado += 1;
            }
        }
        res.json({ "disponibles": disponible, "ocupados": ocupado, "reservados": reservado });
    }
    /*
        verifica si existen espacios disponibles en el arreglo, no recibe nada
        {"existencia": boolean}
    */
    hayExistencias(req, res) {
        res.json({ "existencia": parqueo.includes(0) });
    }
    /*
        reserva el parqueo solicitado por el tiempo establecido por el admin
        {
            "index":number,   -> debe ser el index del parqueo, un numero de 0 a 15
            "propietario":string o id
        }
    */
    reservarParqueo(req, res) {
        let i = req.body.index;
        let p = req.body.propietario;
        if (parqueo[i] == 0) {
            let bandera = true;
            for (let j = 0; j < 32; j++) {
                if (parqueo[j] == 2 && propietarios[j] == p) {
                    bandera = false;
                }
            }
            if (bandera) {
                pos = i;
                parqueo[i] = 2;
                propietarios[i] = p;
                activacionReserva[i] = true;
                res.json({ "res": "OK" });
                let retardo = setTimeout((po = i) => {
                    if (parqueo[po] != 1) {
                        console.log("po " + po + " t " + tiempo);
                        parqueo[po] = 0;
                        propietarios[po] = -1;
                        activacionReserva[po] = false;
                    }
                }, tiempo);
            }
            else {
                res.json({ "res": "Ya cuenta con una reserva" });
            }
        }
        else {
            res.json({ "res": "Parqueo no disponible para reserva" });
        }
    }
    /*
        desactiva la alarma
        recibe
        {
            "posicion":int,
            "propietario":string o id
        }
    */
    DeshabilitarAlarmaReserva(req, res) {
        let posicion = req.body.posicion;
        let propietario = req.body.propietario;
        if (propietario == propietarios[posicion] && activacionReserva[posicion]) {
            activacionReserva[posicion] = false;
            alarmaReserva[posicion] = false;
            propietarios[posicion] = -1;
            parqueo[posicion] = 0;
            res.json({ "mensaje": "Alarma de reservacion ajustada con exito" });
        }
        else {
            res.json({ "mensaje": "Solo el propietario puede ajustar su alarma de reservacion" });
        }
    }
    /*
        desactiva la alarma
        recibe
        {
            "posicion":int,
            "propietario":string o id
        }
    */
    SonidoAlarmaReserva(req, res) {
        let posicion = req.body.posicion;
        let propietario = req.body.propietario;
        if (propietario == propietarios[posicion] && alarmaReserva[posicion]) {
            alarmaReserva[posicion] = false;
            res.json({ "mensaje": "Alarma de reservacion apagada" });
        }
        else {
            res.json({ "mensaje": "Solo el propietario puede apagar su alarma de reservacion" });
        }
    }
    /*
        desactiva la alarma
        recibe
        {
            "posicion":int,
            "propietario":string o id
        }
    */
    HabilitarAlarmaAntiRobo(req, res) {
        let posicion = req.body.posicion;
        let propietario = req.body.propietario;
        if (-1 == propietarios[posicion] && !activacionAntiRobo[posicion]) {
            activacionAntiRobo[posicion] = true;
            propietarios[posicion] = propietario;
            res.json({ "mensaje": "Alarma de antirobo ajustada con exito" });
        }
        else {
            res.json({ "mensaje": "El lugar ya tiene registrado un propietario" });
        }
    }
    /*
        desactiva la alarma
        recibe
        {
            "posicion":int,
            "propietario":string o id
        }
    */
    DeshabilitarAlarmaAntiRobo(req, res) {
        let posicion = req.body.posicion;
        let propietario = req.body.propietario;
        if (propietario == propietarios[posicion] && activacionAntiRobo[posicion]) {
            activacionAntiRobo[posicion] = false;
            alarmaAntiRobo = false;
            propietarios[posicion] = -1;
            res.json({ "mensaje": "Alarma de antirobo ajustada con exito" });
        }
        else {
            res.json({ "mensaje": "Solo el propietario puede ajustar su alarma de robo" });
        }
    }
    /*
       desactiva la alarma
       recibe
       {
           "posicion":int,
           "propietario":string o id
       }
   */
    SonidoalarmaRobo(req, res) {
        let posicion = req.body.posicion;
        let propietario = req.body.propietario;
        if (propietario == propietarios[posicion]) {
            alarmaAntiRobo = false;
            res.json({ "mensaje": "Alarma antirobo ajustada con exito" });
        }
        else {
            res.json({ "mensaje": "Solo el propietario puede ajustar su alarma antirobo" });
        }
    }
    /*
       recibe
       {
           "usuario":string,
           "pass":string
       }
       retorna
       {
           "correcto":boolean,
           "admin":boolean
       }
       */
    login(req, res) {
        let u = req.body.usuario;
        let p = req.body.pass;
        let flag = false;
        let admin = false;
        for (let i = 0; i < usuarios.length; i++) {
            if (usuarios[i].usuario == u && usuarios[i].pass == p) {
                flag = true;
                admin = true;
                break;
            }
        }
        res.json({ "correcto": flag, "admin": admin });
    }
    /*
        ajusta el tiempo de reservacion
        recibe
        {"tiempo":int}
    */
    ajusteTiempo(req, res) {
        tiempo = req.body.tiempo;
        res.json({ "mensaje": "OK" });
    }
    /* retorna arreglo actual alarma anti robo */
    getAlarmaAntiRobo(req, res) {
        res.json({ "alarma": alarmaAntiRobo });
    }
    /*retorna arreglo arreglo antiRobo*/
    getAlarmaReserva(req, res) {
        res.json({ "alarmaReserva": alarmaReserva });
    }
    /*get activacionAntiRobo*/
    getActivacionAntiRobo(req, res) {
        res.json({ "activacionAntiRobo": activacionAntiRobo });
    }
    // get activacionReserva
    getActivacionReserva(req, res) {
        res.json({ "activacionReserva": activacionReserva });
    }
}
exports.indexController = new IndexController();
/*
        cambia el estado de un parqueo de disponible a ocupado
        recibe
            {"index":number}   index-> debe ser el index del parqueo, un numero de 0 a 31
        retorna
            {"mensaje":string}
   
            public ocuparParqueo(req: Request, res: Response) {
                let i = req.body.index
                //ocupado
                if (parqueo[i] == 1) {
                    res.json({ "mensaje": "El parqueo se encuentra ocupado", "alarma": false })
                }
                // disponible
                else if (parqueo[i] == 0) {
                    parqueo[i] = 1
                    res.json({ "mensaje": "El parqueo se ocupo satisfactoriamente", "alarma": false })
                }
                // reservado
                else {
                    if (activacionReserva[i]) {
                        alarmaReserva[i] = true
                        res.json({ "mensaje": "TENEMOS UN 33-12", "alarma": true })
                    } else {
        
                        res.json({ "mensaje": "OK", "alarma": false })
                    }
                }
            } */ 
