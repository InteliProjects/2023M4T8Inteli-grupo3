import React from 'react';
import { RouterProvider } from 'react-router-dom';
import axios from 'axios';
import AppRoutes from './routes/routes';

// Configuração global do Axios
axios.defaults.withCredentials = true;

function App() {
  return <RouterProvider router={AppRoutes} />;
}

export default App;
