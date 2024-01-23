import styled from "styled-components";

export const FormQrCode = styled.form`
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    gap: 1rem;
    margin: 1rem;
    padding: 1rem;
    border: 1px solid #ccc;
    border-radius: 0.5rem;
    background-color: #fff;
    box-shadow: 0 0 1rem #ccc;
    width: 100%;
    max-width: 500px;
    height: 60%;
    max-height: 500px;
    overflow: auto;
    font-size: 1rem;
    font-weight: 400;
    color: #333;
    text-align: center;
    @media (max-width: 600px) {
        width: 100%;
        max-width: 100%;
        height: 100%;
        max-height: 100%;
    }
    `;
