import React, { useState, useEffect } from "react";
import { IoIosSearch } from "react-icons/io";
import { GetAtivos } from "../../services/get/ativos";
import {
  ContainerFilter,
  SearchBar,
  Filters,
  Filter,
  SearchInput,
  SearchButton,
  SearchLabel,
} from "./style";

function FilterOptions({ ativos, setAtivos }) {
  const [tipoPesquisa, setTipoPesquisa] = useState(0);
  const [conteudoSearchBar, setConteudoSearchBar] = useState("todas");
  const [conteudoPesquisa, setConteudoPesquisa] = useState({});

  useEffect(() => {
    (async () => {
      setAtivos(null);
      await GetAtivos(conteudoPesquisa).then((response) => {
        setAtivos(response);
      });
    })();
  }, [conteudoPesquisa]);

  function handleSearch(value, type, index) {
    setTipoPesquisa(index);
    setConteudoPesquisa({ type: type, value: value });
  }

  const filters = [
    {
      name: "Nome do ativo",
      apiName: "Description",
    },
    {
      name: "Serial number",
      apiName: "search",
    },
    {
      name: "Localização",
      apiName: "localizacao",
    },
    {
      name: "Tipo",
      apiName: "neType",
    },
    {
      name: "Status",
      apiName: "status",
    },
  ];

  return (
    <ContainerFilter>
      <SearchLabel>Pesquisar por</SearchLabel>
      <Filters>
        {filters.map((item, index) => {
          return (
            <Filter
              onClick={() => setTipoPesquisa(index)}
              selected={index == tipoPesquisa}
              key={index}
            >
              {item.name}
            </Filter>
          );
        })}
      </Filters>
      <SearchBar>
        <SearchInput
          onChange={(event) => setConteudoSearchBar(event.target.value)}
          placeholder="Pesquisar"
        />
        <SearchButton
          onClick={() =>
            handleSearch(
              conteudoSearchBar,
              filters[tipoPesquisa].apiName,
              tipoPesquisa
            )
          }
        >
          <IoIosSearch />
        </SearchButton>
      </SearchBar>
    </ContainerFilter>
  );
}

export default FilterOptions;
