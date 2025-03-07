import React, { useState, useEffect, useRef } from "react";
import { useNavigate } from "react-router";
import { useLocation } from "react-router-dom";

import Social from "./Social.jsx";
import { getRobustEndpoint, sendHeartbeat } from "./utils.js";

/**
 * @authState {0} status 200 (authorized)
 * @authState {1} status 401 (unauthorized; no access token)
 * @authState {2} status 403 (forbidden; 2fa required)
 */
export function Bouncer() {
  const [isLoading, setIsLoading] = useState(true);
  const navigate = useNavigate();
  const location = useLocation();
  const initAuthState = location?.state?.initAuthState
    ? location?.state?.initAuthState
    : 1;
  const [authState, setAuthState] = useState(initAuthState);

  useEffect(() => {
    if (location?.state?.upstream) {
      // alert("bouncer upstream detected");
      setIsLoading(false);
      return;
    }

    const handleRemoteOAuthCallBack = async () => {
      const checkAuth = async () => {
        const state = await sendHeartbeat();
        setAuthState(state);
      };

      const bounceBack = () => {
        checkAuth();
        console.log(`bouncer authstate: ${authState}`);
        if (authState === 0) {
          const redirect = location?.state?.redirect || "/";
          navigate(redirect, { replace: true });
        } else if (authState === 1) {
          navigate("/login", { replace: true });
        } else if (authState === 2) {
          navigate("/login", { state: { upstream: true } });
        }
      };

      bounceBack();

      // Replace the temporary oauth callback URL with the root URL
      // const currentPath = window.location.pathname;
      const currentPath = location.pathname;
      const callbackPathPattern = /^\/auth\/callback\/42?/;

      if (callbackPathPattern.test(currentPath)) {
        setIsLoading(true);
        const getAccessToken = async () => {
          try {
            const params = new URLSearchParams(location.search);
            const code = params.get("code");
            const response = await fetch(
              getRobustEndpoint(`api/v1/auth/42/callback?code=${code}`),
              {
                method: "POST",
              }
            );
            if (!response.ok) {
              navigate("/login");
            }
            const payload = await response.json();
            if (payload?.requires_2fa) {
              navigate("/2fa", { state: { user: payload["user"] } });
            } else {
              navigate("/", { state: { isAuthed: true } });
            }
          } catch (err) {
            alert("Sorry, we were busy this time. Please try again later.");
            navigate("/login");
          }
        };

        const errorMessageElement = document.getElementById("error-message");

        if (errorMessageElement) {
          const msg = errorMessageElement.dataset.msg; // server message
          if (msg) {
            alert(msg);
          }
        }

        getAccessToken();
        bounceBack();

        // alert(callbackPathPattern);
        // if (checkAuth()) {
        //   const redirect = location?.state?.redirect || "/";
        //   navigate(redirect, { replace: true });
        // } else {
        //   navigate("/login", { replace: true });
        // }

        // window.history.replaceState(null, "", "/");
      }

      // if (checkIsSignedIn()) return;
    };

    handleRemoteOAuthCallBack();
  }, [location?.state?.upstream]);

  return (
    <div className="position-absolute top-50 start-50 translate-middle">
      <div className="position-relative">
        <h1 className="display-4">Hello, world! 😎🏓</h1>
        <p className="lead">퐁퐁퐁</p>
        <hr className="my-4" />
        <p className="text-center">ijo taeoh seungwok</p>
        <div id="social-section">
          <Social isLoading={isLoading} setIsLoading={setIsLoading} />
        </div>
      </div>
    </div>
  );
}

export default Bouncer;
