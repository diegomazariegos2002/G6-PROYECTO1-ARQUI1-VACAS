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
        this.router.get("/estado", indexController.estadoParqueo)
        this.router.get("/existencia", indexController.hayExistencias)
        this.router.post("/reservar", indexController.reservarParqueo)
        this.router.post("/alarmaReserva", indexController.alarmaReserva)
        this.router.post("/ocuparParqueo", indexController.ocuparParqueo)
        this.router.post("/liberarParqueo", indexController.liberarParqueo)
        this.router.post("/login", indexController.login)
    }
}

const indexRouter = new IndexRouter();
export default indexRouter.router;