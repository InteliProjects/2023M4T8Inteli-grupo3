import React, { useState, useEffect } from "react";
import { MapContainer, TileLayer, Marker, Popup } from "react-leaflet";
import { renderToString } from "react-dom/server";
import L from "leaflet";
import "leaflet/dist/leaflet.css";
import { ContainerCaption, ContainerMapa } from "./style";
import { FaHouse, FaTruck } from "react-icons/fa6";
import { FaMapMarkerAlt } from "react-icons/fa";
function Mapa({ width, caption, coordenadas }) {
  const [screenHeight, setScreenHeight] = useState(window.innerHeight);
  const [key, setKey] = useState(0);
  const position = [-14.235, -51.925];
  const mapCaption = [
    {
      icon: <FaHouse />,
      name: "Armazém",
    },
    {
      icon: <FaTruck />,
      name: "Transporte",
    },
  ];
  useEffect(() => {
    const handleResize = () => {
      setScreenHeight(window.innerHeight);
      setKey(key + 1);
    };
    window.addEventListener("resize", handleResize);
    return () => {
      window.removeEventListener("resize", handleResize);
    };
  }, [key]);

  const customIcon = new L.divIcon({
    html: renderToString(<FaMapMarkerAlt color="red" size={32} />),
    iconSize: [0, 0],
    iconAnchor: [16, 32],
  });

  const markers = coordenadas
    ? coordenadas.map((coordenada, index) => (
        <Marker key={index} position={coordenada.position} icon={customIcon}>
          <Popup>{coordenada.name}</Popup>
        </Marker>
      ))
    : [];

  return (
    <ContainerMapa style={{ width: width }}>
      {caption ? (
        <ContainerCaption>
          {mapCaption.map((item, index) => (
            <span key={index}>
              {item.icon} <p>{item.name}</p>
            </span>
          ))}
        </ContainerCaption>
      ) : null}
      <MapContainer
        key={key}
        center={position}
        zoom={4}
        style={{ height: `${screenHeight - 190}px`, width: "100%" }}
      >
        <TileLayer
          style={{ backgroundColor: "red" }}
          url="https://{s}.basemaps.cartocdn.com/light_all/{z}/{x}/{y}{r}.png"
          attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors &copy; <a href="https://carto.com/attributions">CARTO</a>'
        />
        {markers}
      </MapContainer>
    </ContainerMapa>
  );
}
export default Mapa;
