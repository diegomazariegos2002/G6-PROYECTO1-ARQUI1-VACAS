"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = require("express");
const indexController_1 = require("../Controllers/indexController");
class IndexRouter {
    ;
    constructor() {
        this.router = (0, express_1.Router)();
        this.config();
    }
    config() {
        this.router.get("/", indexController_1.indexController.prueba);
        this.router.get("/verParqueo", indexController_1.indexController.verParqueo);
        this.router.post("/setParqueo", indexController_1.indexController.setParqueo);
        this.router.get("/estado", indexController_1.indexController.estadoParqueo);
        this.router.get("/existencia", indexController_1.indexController.hayExistencias);
        this.router.post("/reservar", indexController_1.indexController.reservarParqueo);
        this.router.post("/desahbilitarAlarmaReserva", indexController_1.indexController.DeshabilitarAlarmaReserva);
        this.router.post("/sonidoAlarmaReserva", indexController_1.indexController.SonidoAlarmaReserva);
        this.router.post("/habilitarAlarmaAntiRobo", indexController_1.indexController.HabilitarAlarmaAntiRobo);
        this.router.post("/deshabilitarAlarmaAntiRobo", indexController_1.indexController.DeshabilitarAlarmaAntiRobo);
        this.router.post("/sonidoAlarmaAntirobo", indexController_1.indexController.SonidoalarmaRobo);
        this.router.post("/login", indexController_1.indexController.login);
        this.router.post("/ajusteTiempo", indexController_1.indexController.ajusteTiempo);
        this.router.get("/getAlarmaAntiRobo", indexController_1.indexController.getAlarmaAntiRobo);
        this.router.get("/getactivacionAntiRobo", indexController_1.indexController.getActivacionAntiRobo);
        this.router.get("/getactivacionReserva", indexController_1.indexController.getActivacionReserva);
        this.router.get("/getAlarmaReserva", indexController_1.indexController.getAlarmaReserva);
    }
}
const indexRouter = new IndexRouter();
exports.default = indexRouter.router;
