import React, { useState, useEffect, useCallback } from "react";
import { getRobustEndpoint } from "../utils";

export default function SideBar({
  profileData,
  setProfileData,
  error,
  setError,
  isEditableProfile,
  setIsEditableProfile,
  otherProfileData,
  setOtherProfileData,
}) {
  // const [myUserInfo, setMyUserInfo] = useState(null);
  const [activeUsers, setActiveUsers] = useState([]);
  // const [showProfile, setShowProfile] = useState(null);

  // 내 정보 가져오기
  // useEffect(() => {
  //   fetch("/api/v1/users/profile")
  //     .then((response) => {
  //       if (!response.ok) throw new Error("You've been logged out");
  //       return response.json();
  //     })
  //     .then((payload) => {
  //       setMyUserInfo(payload.user);
  //     })
  //     .catch((e) => setError(e.message));
  // }, []);

  // Active 유저 목록 가져오기
  let fetchActiveUsersIntervalID;
  useEffect(() => {
    const fetchActiveUsers = async () => {
      try {
        const response = await fetch(getRobustEndpoint("/api/v1/users/active"));
        if (!response.ok) {
          const payload = await response.json();
          throw new Error(payload?.error?.message);
        }
        const data = await response.json();
        setActiveUsers(data.users);
      } catch (e) {
        // console.error(`fetchActiveUsers`);
        setError(e.message);
      }
    };

    fetchActiveUsers();
    // 폴링은 Home.jsx에서 이미 처리중이므로 여기서는 주기적으로 목록만 새로고침
    fetchActiveUsersIntervalID = setInterval(fetchActiveUsers, 15000);
    return () => clearInterval(fetchActiveUsersIntervalID);
  }, []);

  const handleClickMyUser = async () => {
    try {
      const response = await fetch(getRobustEndpoint(`api/v1/users/profile`));
      if (!response.ok) {
        const payload = await response.json();
        throw new Error(payload?.error?.message);
      }
      const payload = await response.json();
      setProfileData(payload);
      setIsEditableProfile(true);
    } catch (e) {
      setError(e.message);
    }
  };

  const handleClickOtherUser = async (user_id) => {
    try {
      const response = await fetch(
        getRobustEndpoint(`api/v1/users/${user_id}/profile`)
      );
      if (!response.ok) {
        const payload = await response.json();
        throw new Error(payload?.error?.message);
      }
      const payload = await response.json();
      setOtherProfileData(payload);
      setIsEditableProfile(false);
    } catch (e) {
      setError(e.message);
    }
  };

  // 친구 추가 핸들러
  const handleAddFriend = async (userId) => {
    try {
      const response = await fetch(getRobustEndpoint("/api/v1/users/friends"), {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ user_id: userId }),
      });
      if (!response.ok) {
        const payload = await response.json();
        throw new Error(payload?.error?.message);
      }
      // 친구 추가 성공 시 유저 목록 새로고침
      const newActiveUsers = [...activeUsers];
      const userIndex = newActiveUsers.findIndex(
        (u) => u.displayname === userId
      );
      if (userIndex !== -1) {
        newActiveUsers[userIndex].is_friend = true;
        setActiveUsers(newActiveUsers);
      }
    } catch (e) {
      // console.error("handleAddFriend");
      setError(e.message);
    }
  };

  return (
    <div className="position-absolute col-3 d-flex flex-column align-items-center side-bar">
      {/* 내 프로필 */}
      <div className="py-3" onClick={handleClickMyUser}>
        <button
          type="button"
          className="btn btn-success my-user-wrapper"
          onClick={null}
        >
          <span className="my-user-icon">
            <img
              src="/static/assets/person-fill-gear.svg"
              width="28"
              height="28"
            />
          </span>
          <span className="py-1 my-user-text">
            {profileData?.user?.displayname}(me)
          </span>
        </button>
      </div>

      {/* 액티브 유저 리스트 */}
      <ul
        className="list-group list-group-flush w-100 align-items-center"
        style={{
          overflowY: "auto",
          maxHeight: "calc(100% - 5rem)",
          listStyleType: "none",
        }}
      >
        {activeUsers.map((user) => (
          <div key={user.displayname} className="py-2">
            <button
              // onClick={() => {
              //   handleClickOtherUser(user.user_id);
              //   // setIsEditableProfile(false);
              // }}
              onClick={() => {
                // alert(JSON.stringify(user));
                if (user.is_friend) {
                  handleClickOtherUser(user.user_id);
                } else {
                  handleAddFriend(user.user_id);
                }
              }}
              className={`btn ${
                user.is_friend ? "btn-primary" : "btn-dark"
              } user-list-item-wrapper`}
            >
              <span className="my-user-icon">
                <img
                  src={
                    user.is_friend
                      ? "/static/assets/person-fill-check.svg"
                      : "/static/assets/person-add.svg"
                  }
                  width="28"
                  height="28"
                />
              </span>
              <span className="py-1 my-user-text">{user.displayname}</span>
            </button>
          </div>
        ))}
      </ul>

      {/* 프로필 모달
      {showProfile && (
        <div
          className="position-fixed top-50 start-50 translate-middle"
          style={{ zIndex: 1000 }}
        >
          {showProfile.isSelf ? (
            <MyProfile onClose={() => setShowProfile(null)} />
          ) : (
            <UserProfile
              userId={showProfile.userId}
              onClose={() => setShowProfile(null)}
            />
          )}
        </div>
      )} */}
    </div>
  );
}
