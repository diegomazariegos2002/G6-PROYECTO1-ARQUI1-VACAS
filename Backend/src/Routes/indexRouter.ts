import { Router } from "express";
import { indexController } from "../Controllers/indexController";


class IndexRouter {
    public router: Router = Router();;
    constructor() {
        this.config();
    }

    config(): void {
        this.router.get("/", indexController.prueba)
        this.router.get("/verParqueo", indexController.verParqueo)
        this.router.post("/setParqueo", indexController.setParqueo)
        this.router.get("/estado", indexController.estadoParqueo)
        this.router.get("/existencia", indexController.hayExistencias)
        this.router.post("/reservar", indexController.reservarParqueo)
        this.router.post("/desahbilitarAlarmaReserva", indexController.DeshabilitarAlarmaReserva)
        this.router.post("/sonidoAlarmaReserva", indexController.SonidoAlarmaReserva)
        this.router.post("/habilitarAlarmaAntiRobo", indexController.HabilitarAlarmaAntiRobo)
        this.router.post("/deshabilitarAlarmaAntiRobo", indexController.DeshabilitarAlarmaAntiRobo)
        this.router.post("/sonidoAlarmaAntirobo", indexController.SonidoalarmaRobo)
        this.router.post("/login", indexController.login)
        this.router.post("/ajusteTiempo", indexController.ajusteTiempo)
        this.router.get("/getAlarmaAntiRobo", indexController.getAlarmaAntiRobo)
        this.router.get("/getactivacionAntiRobo", indexController.getActivacionAntiRobo)
        this.router.get("/getactivacionReserva", indexController.getActivacionReserva)
    }
}

const indexRouter = new IndexRouter();
export default indexRouter.router;