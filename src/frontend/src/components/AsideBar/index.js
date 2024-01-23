import React from "react";
import { ContainerAside, ContainerLogo, NavBar } from "./style";
import Logo from "./../../assets/images/NEMO.png";
import { PiHouse } from "react-icons/pi";
import { TbRouter, TbQrcode } from "react-icons/tb";
import { Link } from "react-router-dom";

function AsideBar() {
  const OptionsMenu = [
    {
      name: "Home",
      icon: <PiHouse />,
      path: "/home",
    },
    {
      name: "Ativos",
      icon: <TbRouter />,
      path: "/ativos",
    },
    {
      name: "GPS QR Code",
      icon: <TbQrcode />,
      path: "/gps-qr-code",
    },
  ];

  return (
    <>
      <ContainerAside>
        <ContainerLogo>
          <img src={Logo} alt={"Logo .Nemo"} />
        </ContainerLogo>
        <NavBar>
          <ul>
            {OptionsMenu.map((item, index) => {
              return (
                <Link to={item.path}>
                  <li key={index}>
                    {item.icon} <span>{item.name}</span>
                  </li>
                </Link>
              );
            })}
          </ul>
        </NavBar>
      </ContainerAside>
    </>
  );
}

export default AsideBar;
