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
        this.router.get("/estado", indexController_1.indexController.estadoParqueo);
        this.router.get("/existencia", indexController_1.indexController.hayExistencias);
        this.router.post("/reservar", indexController_1.indexController.reservarParqueo);
        this.router.post("/alarmaReserva", indexController_1.indexController.alarmaReserva);
        this.router.post("/ocuparParqueo", indexController_1.indexController.ocuparParqueo);
        this.router.post("/liberarParqueo", indexController_1.indexController.liberarParqueo);
        this.router.post("/login", indexController_1.indexController.login);
    }
}
const indexRouter = new IndexRouter();
exports.default = indexRouter.router;
