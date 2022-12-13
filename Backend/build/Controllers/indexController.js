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
let alarma = [false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false];
let alarmaReserva = [true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true];
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
                res.json({ "res": "OK" });
                let retardo = setTimeout(() => {
                    if (parqueo[pos] != 1) {
                        parqueo[pos] = 0;
                        propietarios[pos] = -1;
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
        activa o desactiva la alarma
        recibe
        {
            "posicion":int,
            "propietario":string o id
        }
    */
    alarmaReserva(req, res) {
        let posicion = req.body.posicion;
        let propietario = req.body.propietario;
        if (propietario == propietarios[posicion]) {
            alarmaReserva[posicion] = false;
            parqueo[posicion] = 0;
            res.json({ "mensaje": "Alarma de reservacion desactivada con exito" });
        }
        else {
            res.json({ "mensaje": "Solo el propietario puede desactivar su alarma de reservacion" });
        }
    }
    /*
        cambia el estado de un parqueo de disponible a ocupado
        recibe
        {
            "index":number,   -> debe ser el index del parqueo, un numero de 0 a 15
            "propietario":string o id
        }
        retorna
        {
            "mensaje":string,
            "alarma":boolean
        }
    */
    ocuparParqueo(req, res) {
        let i = req.body.index;
        let p = req.body.propietario;
        if (parqueo[i] == 1) {
            res.json({ "mensaje": "El parqueo se encuentra ocupado", "alarma": false });
        }
        else if (parqueo[i] == 0) {
            parqueo[i] = 1;
            propietarios[i] = p;
            res.json({ "mensaje": "El parqueo se ocupo satisfactoriamente", "alarma": false });
        }
        else {
            res.json({ "mensaje": "No puede ocupar dicho parqueo", "alarma": true });
        }
    }
    /*
    cambia estado de parqueo de ocupado a disponible
    recibe
    {
        posicion: int,
        propietario
    }
    retorna
    {
        "mensaje":string,
        "alarma":boolean
    }
    */
    liberarParqueo(req, res) {
        let i = req.body.posicion;
        let p = req.body.propietario;
        if (parqueo[i] == 1) {
            if (alarma[i]) {
                res.json({ "mensaje": "error", "alarma": true });
            }
            else {
                parqueo[i] = 0;
                propietarios[i] = -1;
                alarma[i] = true;
                alarmaReserva[i] = true;
                res.json({ "mensaje": "error", "alarma": false });
            }
        }
        else {
            res.json({ "mensaje": "error", "alarma": false });
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
            if (usuarios[i].usuario == p && usuarios[i].pass == p) {
                flag = true;
                if (p == "diegomaza") {
                    admin = true;
                }
                break;
            }
        }
        res.json({ "correcto": flag, "admin": admin });
    }
}
exports.indexController = new IndexController();
