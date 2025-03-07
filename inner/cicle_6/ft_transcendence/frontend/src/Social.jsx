"use strict";

import React, { useState, useEffect } from "react";
import { useNavigate } from "react-router";

import { fetchAuthorizationEndpoint, openOAuthPopup } from "./oauth.js";

import { remToPx, openPopup } from "./utils.js";

import "./Social.css";

function Logo({ isDiabled }) {
  return isDiabled ? (
    <div
      className="spinner-border spinner-border-sm text-muted"
      role="status"
    ></div>
  ) : (
    // <svg
    //   xmlns="http://www.w3.org/2000/svg"
    //   width="20"
    //   height="20"
    //   fill="grey"
    //   className="bi bi-arrow-clockwise rotating-icon"
    //   viewBox="0 0 16 16"
    //   opacity="0.7"
    // >
    //   <path
    //     fill-rule="evenodd"
    //     d="M8 3a5 5 0 1 0 4.546 2.914.5.5 0 0 1 .908-.417A6 6 0 1 1 8 2z"
    //   />
    //   <path d="M8 4.466V.534a.25.25 0 0 1 .41-.192l2.36 1.966c.12.1.12.284 0 .384L8.41 4.658A.25.25 0 0 1 8 4.466" />
    // </svg>
    <img
      className="social-logo"
      src="/static/assets/42-logo.svg"
      width="20"
      height="20"
    ></img>
  );
}

export function Social({ isLoading, setIsLoading }) {
  // const [isDisabled, setIsDisabled] = useState(isLoading);
  const navigate = useNavigate();

  const handleClick = async () => {
    // setIsDisabled(true);
    setIsLoading(true);

    const protocol = window.location.protocol;
    const host = window.location.hostname;
    const port = window.location.port ? ":" + window.location.port : "";
    const url = new URL("api/v1/auth/42/login", protocol + "//" + host + port);

    fetch(url)
      .then((response) => {
        if (response.ok) {
          return response.json();
        } else {
          alert("Something is wrong.");
          navigate("/");
        }
      })
      .then((payload) => {
        window.location.href = payload["authorize_url"]; // remote OAuth interactioin page
      })
      .catch((err) => {
        console.error("Social:", err.message);
      });
  };

  return (
    <button
      className="btn btn-light"
      onClick={() => handleClick("42")}
      disabled={isLoading}
    >
      <span className="social-logo-wrapper">
        <Logo isDiabled={isLoading} />
      </span>
      <span
        className={isLoading ? "social-text text-muted" : "social-text text"}
      >
        Continue with 42
      </span>
    </button>
  );
}

export default Social;
