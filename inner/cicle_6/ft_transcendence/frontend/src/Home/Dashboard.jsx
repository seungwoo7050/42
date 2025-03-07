import React, { useState, useEffect, useCallback } from "react";

import { MyProfile, OtherProfile } from "../Profiles.jsx";
import { useNavigate } from "react-router";

export default function Dashboard({
  profileData,
  setProfileData,
  error,
  setError,
  isEditableProfile,
  setIsEditableProfile,
  otherProfileData,
  setOtherProfileData,
}) {
  return (
    <div className="position-relative main-panel">
      <>
        {isEditableProfile ? (
          <MyProfile
            profileData={profileData}
            setProfileData={setProfileData}
            error={error}
            setError={setError}
          />
        ) : (
          <OtherProfile otherProfileData={otherProfileData} />
        )}
        <ModeMenu
          otherProfileData={otherProfileData}
          isEditableProfile={isEditableProfile}
        />
        {/* <div className="d-flex justify-content-evenly flex-row">
            <div className="p-2">
              <Mode />
            </div>
            <div className="p-2">
              <Mode />
            </div>
            <div className="p-2">
              <Mode />
            </div>
          </div> */}
      </>
      {/* Render the page based on the current path */}
      {/* {renderPage()} */}
    </div>
  );
}

function ModeMenu({ otherProfileData, isEditableProfile }) {
  const navigate = useNavigate();
  const requestVsAI = () => {
    navigate("/game/ai");
  };
  const requestPvP = (user_id) => {
    navigate(`/game/pvp?opponent=${user_id}`);
  };
  const requestTourney = (user_id) => {
    navigate(`/game/tournament?opponent=${user_id}`);
  };
  return (
    <div className="d-grid gap-5 col-6 mx-auto">
      {isEditableProfile ? (
        <button
          className="btn btn-lg btn-dark"
          type="button"
          onClick={requestVsAI}
        >
          vs. AI
        </button>
      ) : (
        <>
          <button
            className="btn btn-lg btn-dark"
            type="button"
            onClick={() => {
              requestPvP(otherProfileData.profile.user_id);
            }}
          >
            PvP
          </button>
          <button
            className="btn btn-lg btn-dark"
            type="button"
            onClick={() => {
              requestTourney(otherProfileData.profile.user_id);
            }}
          >
            Tournament
          </button>
        </>
      )}
    </div>
  );
}
