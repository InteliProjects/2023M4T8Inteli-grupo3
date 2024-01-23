import styled from "styled-components";

export const ContainerFilter = styled.div`
  width: 100%;
  display: flex;
  align-items: center;
`;

export const Filters = styled.div`
  width: 60%;
  display: flex;
  justify-content: space-between;
  align-items: center;
  color: #e6e6fa;
`;

export const Filter = styled.button`
  background-color: rgba(0, 0, 0, 0);
  font-weight: 600;
  border: 0;
  cursor: pointer;
  margin-right: 10px;
  color: #e6e6fa;

  ${(props) => (props.selected ? "border-bottom: 1px solid #e6e6fa;" : null)}
`;

export const SearchBar = styled.div`
  margin-top: 20px;
  width: 40%;
  display: flex;
  border: 1px solid #f8f8ff;
`;

export const SearchInput = styled.input`
  display: flex;
  height: 30px;
  width: 90%;
  color: #f8f8ff;
  border: none;
  background-color: transparent;
  padding-left: 10px;

  &:focus {
    outline: none;
  }

  &::placeholder {
    color: #f8f8ff;
  }
`;

export const SearchButton = styled.button`
  width: 10%;
  border-radius: 0;
  border: none;
  cursor: pointer;

  &:hover {
    background-color: #4d007e;
  }
`;

export const SearchLabel = styled.p`
  color: #f8f8ff;
`;
