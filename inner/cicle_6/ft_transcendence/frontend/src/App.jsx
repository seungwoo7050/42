import React, { useState, useEffect, useRef } from "react";
import { useNavigate } from "react-router";
import { Routes, Route, useLocation, Navigate } from "react-router-dom";

import NotFound from "./NotFound.jsx";
import Bouncer from "./Bouncer.jsx";
import { AuthCodeInput } from "./TwoFA.jsx";
import Home from "./Home/Home.jsx";
// import Game from "./Game.jsx";
import GameAI from "./Game/GameAI";
import GamePvP from "./Game/GamePvP";
import GameTournament from "./Game/GameTournament";
// import Tournament from "./Tournament.jsx"
import { sendHeartbeat } from "./utils.js";

import "./App.css";
// import PongGame from "./PongGame.jsx";
// import { setup } from "./game.js";

/**
 * @authState {0} status 200 (authorized)
 * @authState {1} status 401 (unauthorized; no access token)
 * @authState {2} status 403 (forbidden; 2fa required)
 */
function RequireAuth({ children }) {
  const location = useLocation();
  const navigate = useNavigate();
  const [isLoading, setIsLoading] = useState(true);
  const isAuthed = location?.state?.isAuthed ? true : false;

  const [authState, setAuthState] = useState(isAuthed ? 0 : 1);

  useEffect(() => {
    if (isAuthed) {
      setIsLoading(false);
      return;
    }

    const checkAuth = async () => {
      const state = await sendHeartbeat();
      setAuthState(state);
      setIsLoading(false);
    };

    checkAuth();
  }, []);

  if (isLoading === true) {
    return (
      <div className="position-absolute top-50 start-50 translate-middle">
        <div
          className="spinner-border text-light"
          style={{ width: "3rem", height: "3em" }}
          role="status"
        ></div>
      </div>
    );
  }

  // console.log(`requireauth: authstate ${authState}`);

  if (authState === 2) {
    // alert("requireAuth authState 2 detected... redirecting to login");
    navigate("/login", { replace: true, state: { initAuthState: authState } });
  }

  return authState == 0 ? (
    children
  ) : (
    <Navigate
      to="/login"
      replace
      state={{ redirect: location.pathname, upstream: true }}
    />
  );
}

// async function sendHeartbeat() {
//   try {
//     const response = await fetch("api/v1/auth/42/status");
//     if (!response.ok) {
//       console.error(`sendHeartbeat: http status ${response.status}`);
//       return false;
//     }
//     const payload = await response.json();
//     return payload.ack || false;
//   } catch (err) {
//     console.error(`sendHeartbeat: ${err}`);
//     return false;
//   }
// }

function Banner() {
  const navigate = useNavigate();

  const redirectToHome = () => {
    // window.location.href = window.location.origin;
    // const event = new Event("unload"); // Create a custom 'beforeunload' event
    // event.preventDefault();
    // event.returnValue = "";
    // window.dispatchEvent(event);
    navigate("/");
  };

  return (
    <div
      className="fs-4 text-light position-absolute py-3 px-4 top-0 start-0"
      onClick={redirectToHome}
      style={{
        cursor: "pointer",
        display: "inline-block", // Ensures the width matches the text
      }}
    >
      <p className="banner-hover">ft-transcendence</p>
    </div>
  );
}

export function App() {
  // const [isSignedIn, setIsSignedIn] = useState(null); // Start with null to show loading state
  const location = useLocation();
  const navigate = useNavigate();

  // Initial check for JWT cookie
  // useEffect(() => {
  //   const checkAuthorization = async () => {
  //     // const checkIsSignedIn = async () => {
  //     //   const ack = await sendHeartbeat();
  //     //   setIsSignedIn(ack);
  //     //   return ack;
  //     // };

  //     // Replace the temporary oauth callback URL with the root URL
  //     // const currentPath = window.location.pathname;
  //     const currentPath = location.pathname;
  //     const callbackPathPattern = /^\/auth\/callback\/42/;

  //     if (callbackPathPattern.test(currentPath)) {
  //       const errorMessageElement = document.getElementById("error-message");

  //       if (errorMessageElement) {
  //         const msg = errorMessageElement.dataset.msg; // server message

  //         if (msg) {
  //           alert(msg);
  //         }
  //       }

  //       navigate("/", { replace: true });
  //       // window.history.replaceState(null, "", "/");
  //     }

  //     // if (checkIsSignedIn()) return;
  //   };

  //   checkAuthorization();
  // }, []);

  // if (isSignedIn === null) {
  //   return <Bouncer isLoading={true} />;
  // }

  return (
    <div className="container-fluid p-0">
      <div>
        <Banner />
      </div>
      <Routes>
        <Route
          path="/"
          element={
            <RequireAuth>
              <Home />
            </RequireAuth>
          }
        />
        <Route path="*" element={<NotFound />} />
        <Route path="/login" element={<Bouncer />} />
        <Route path="/2fa" element={<AuthCodeInput />} />
        <Route path="/auth/callback/*" element={<Bouncer />} />
        <Route
          path="/game/ai"
          element={
            <RequireAuth>
              <GameAI />
            </RequireAuth>
          }
        />
        <Route
          path="/game/pvp"
          element={
            <RequireAuth>
              <GamePvP />
            </RequireAuth>
          }
        />
        <Route
          path="/game/tournament"
          element={
            <RequireAuth>
              <GameTournament />
            </RequireAuth>
          }
        />
        <Route
          path="/tournament"
          element={<RequireAuth>{/* <Tournament /> */}</RequireAuth>}
        />
      </Routes>
      {/* {isSignedIn ? (
        <Home isSignedIn={isSignedIn} setIsSignedIn={setIsSignedIn} />
      ) : (
        <Bouncer isLoading={false} />
      )} */}
    </div>
  );
}

export default App;
