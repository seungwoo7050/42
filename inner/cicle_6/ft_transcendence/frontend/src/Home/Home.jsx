import React, { useState, useEffect, useCallback } from "react";
import { useNavigate } from "react-router";
import { useLocation } from "react-router-dom";

import SideBar from "./Sidebar.jsx";
import Dashboard from "./Dashboard.jsx";
import UserListItem from "../UserListItem.jsx";
import { getRobustEndpoint } from "../utils.js";

import "../App.css";

function SignOut() {
  const navigate = useNavigate();

  const handleClick = async () => {
    try {
      await fetch(getRobustEndpoint("api/v1/auth/logout"), {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        mode: "same-origin",
        credentials: "include",
      });
      navigate("/login", { state: { upstream: true } });
    } catch (e) {
      setError(e.message);
    }
  };

  return (
    <div className="position-absolute top-0 end-0 py-3 px-3">
      <button type="button" className="btn btn-dark" onClick={handleClick}>
        Sign out
      </button>
    </div>
  );
}

export function Home() {
  const [error, setError] = useState(null);
  const [profileData, setProfileData] = useState(null);
  const [otherProfileData, setOtherProfileData] = useState(null);
  const [isEditableProfile, setIsEditableProfile] = useState(true);
  const navigate = useNavigate();

  // const logOut = useCallback(() => {
  //   fetch(getRobustEndpoint("api/v1/auth/logout"), {
  //     method: "POST",
  //     headers: {
  //       "Content-Type": "application/json",
  //     },
  //     mode: "same-origin",
  //     credentials: "include",
  //   })
  //     .then((response) => {
  //       if (response.ok) {
  //         return;
  //       } else {
  //         throw new Error("Couldn't log out automatically.");
  //       }
  //     })
  //     .catch((e) => {
  //       console.error(`logOut error:\n\n${e.message}`);
  //     });
  // }, []);

  // useEffect(() => {
  //   if (error === null) return;

  //   alert(error);
  //   logOut();
  // }, [error]);

  // useEffect(() => {
  //   fetch(getRobustEndpoint("api/v1/users/profile"), {
  //     headers: {
  //       "Content-Type": "application/json",
  //     },
  //     mode: "same-origin",
  //     credentials: "include",
  //   })
  //     .then((response) => navigate("/login"))
  //     .catch((error) => {
  //       navigate("/login");
  //     });
  // }, []);

  let doPollingIntervalID;
  useEffect(() => {
    const doPolling = async () => {
      {
        try {
          const response = await fetch(
            getRobustEndpoint("api/v1/users/polling"),
            {
              method: "POST",
              headers: {
                "Content-Type": "application/json",
              },
              mode: "same-origin",
              credentials: "include",
            }
          );
          if (!response.ok) {
            const payload = await response.json();
            throw new Error(payload?.error?.message);
          }
        } catch (e) {
          // console.error(`doPolling: ${e.message}`);
          setError(e.message);
        }
      }
    };

    doPolling();
    doPollingIntervalID = setInterval(doPolling, 30000);
    return () => clearInterval(doPollingIntervalID);
  }, []);

  useEffect(() => {
    const initProfileData = async () => {
      try {
        const response = await fetch(getRobustEndpoint("api/v1/users/profile"));
        const payload = await response.json();
        if (!response.ok) {
          throw new Error(payload?.error?.message);
        }
        setProfileData(payload);
      } catch (e) {
        setError(e.message);
      }
    };

    initProfileData();
  }, []);

  return (
    <>
      <SignOut />
      <div className="d-flex" style={{ marginTop: "3rem" }}>
        <SideBar
          profileData={profileData}
          setProfileData={setProfileData}
          error={error}
          setError={setError}
          isEditableProfile={isEditableProfile}
          setIsEditableProfile={setIsEditableProfile}
          otherProfileData={otherProfileData}
          setOtherProfileData={setOtherProfileData}
        />
        <Dashboard
          profileData={profileData}
          setProfileData={setProfileData}
          error={error}
          setError={setError}
          isEditableProfile={isEditableProfile}
          setIsEditableProfile={setIsEditableProfile}
          otherProfileData={otherProfileData}
          setOtherProfileData={setOtherProfileData}
        />
      </div>
    </>
  );
}

export default Home;
