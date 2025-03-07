import React, { useState, useEffect, useRef } from "react";

// import { getCookie } from "./utils.js";

// import Cookies from "js-cookie";

export function Dashboard({ isSignedIn, setIsSignedIn }) {
  return (
    <div id="userDashboard">
      <h1>Welcome to your dashboard!</h1>
      <button
        onClick={() => {
          const protocol = window.location.protocol;
          const host = window.location.hostname;
          const port = window.location.port ? ":" + window.location.port : "";
          const url = new URL("/auth/logout", protocol + "//" + host + port);

          fetch(url, {
            method: "POST",
            headers: {
              "Content-Type": "application/json",
            },
            mode: "same-origin",
            credentials: "include",
          })
            .then((response) => {
              if (response.ok) {
                setIsSignedIn(false);
              } else {
                alert(`Error logging out:, ${response.statusText}`);
              }
            })
            .catch((error) => {
              console.error("Error:", error);
            });
        }}
      >
        Logout
      </button>
    </div>
  );
}

export default Dashboard;
