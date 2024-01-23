import { createBrowserRouter } from "react-router-dom";
import Homepage from "../pages/Homepage";
import AtivoPage from "../pages/Ativo";
import AtivosTablePage from "../pages/Ativos";
import Leitor from "../pages/Leitor";
import QrCode from "../pages/GerarQrCode";
import LoginPage from "../pages/Login";

const { innerWidth: width } = window;
const homepage = width > 600 ? <Homepage /> : <Leitor />;

const AppRoutes = createBrowserRouter([
  {
    path: "/",
    element: <LoginPage />,
  },
  {
    path: "/home",
    element: homepage,
  },
  {
    path: "/ativo/:sn",
    element: <AtivoPage />,
  },
  {
    path: "/ativos",
    element: <AtivosTablePage />,
  },
  {
    path: "/gps-qr-code",
    element: <QrCode />,
  }
]);

export default AppRoutes;
