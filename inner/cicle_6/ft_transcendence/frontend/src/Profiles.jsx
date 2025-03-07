import React, { useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { getRobustEndpoint } from "./utils";

import { Qr, AuthCodeInput } from "./TwoFA.jsx";

function QrRegistration() {
  return (
    <div className="accordion accordion-flush" id="accordionFlushExample">
      <div className="accordion-item">
        <h2 className="accordion-header" id="flush-headingOne">
          <button
            className="accordion-button collapsed bg-secondary"
            type="button"
            data-bs-toggle="collapse"
            data-bs-target="#flush-collapseOne"
            aria-expanded="false"
            aria-controls="flush-collapseOne"
          >
            Show Qr
          </button>
        </h2>
        <div
          id="flush-collapseOne"
          className="accordion-collapse collapse"
          aria-labelledby="flush-headingOne"
          data-bs-parent="#accordionFlushExample"
        >
          <div
            className="accordion-body"
            style={{
              transform: "scale(0.8)",
              transformOrigin: "top center",
              width: "fit-content", // Prevents excessive space
            }}
          >
            <Qr />
          </div>
        </div>
      </div>
      {/* <div className="accordion-item">
        <h2 className="accordion-header" id="flush-headingTwo">
          <button
            className="accordion-button collapsed"
            type="button"
            data-bs-toggle="collapse"
            data-bs-target="#flush-collapseTwo"
            aria-expanded="false"
            aria-controls="flush-collapseTwo"
          >
            Register code
          </button>
        </h2>
        <div
          id="flush-collapseTwo"
          className="accordion-collapse collapse"
          aria-labelledby="flush-headingTwo"
          data-bs-parent="#accordionFlushExample"
        >
          <div className="accordion-body">{/* <AuthCodeInput /> </div> </div> </div>*/}
    </div>
  );
}

// Match History 컴포넌트
function MatchHistory({ matches, myuser_id }) {
  if (!matches?.length) {
    return (
      <div className="text-light text-center my-3">No matches played yet</div>
    );
  }

  return (
    <div className="match-history mt-4">
      <h6 className="border-bottom pb-2">Recent Matches</h6>
      {matches.map((match) => (
        <div
          key={match.id}
          className="d-flex justify-content-between align-items-center py-2 border-bottom"
        >
          <span className="text-light">
            {match.player1.user_id === myuser_id
              ? "You"
              : match.player1.displayname}
            {" vs "}
            {match.player2.user_id === myuser_id
              ? "You"
              : match.player2.displayname}
          </span>
          <span
            className={
              match.winner?.user_id === myuser_id
                ? "text-success"
                : "text-danger"
            }
          >
            {match.player1.score} - {match.player2.score}
          </span>
        </div>
      ))}
    </div>
  );
}

// 나의 프로필 컴포넌트
export function MyProfile({ profileData, setProfileData, error, setError }) {
  const [matches, setMatches] = useState([]);

  // 매치 히스토리 가져오기
  useEffect(() => {
    const fetchMatches = async () => {
      try {
        const response = await fetch(
          getRobustEndpoint("/api/v1/game/matches?limit=5")
        );
        const data = await response.json();
        console.log("Fetched matches:", data); // 추가

        if (!response.ok) {
          throw new Error(data?.error?.message);
        }
        setMatches(data.matches);
      } catch (e) {
        // console.error("fetchMatches");
        setError(e.message);
      }
    };

    fetchMatches();
  }, []);

  const [isEditing, setIsEditing] = useState(false);
  const [newDisplayName, setNewDisplayName] = useState(
    profileData?.user?.displayname
  );

  const fetchProfile = async () => {
    try {
      const response = await fetch(getRobustEndpoint("/api/v1/users/profile"), {
        credentials: "include",
      });

      const data = await response.json();
      if (!response.ok) {
        throw new Error(data?.error?.message);
      }

      // alert(JSON.stringify(data));
      setProfileData(data);
      setNewDisplayName(data?.user.displayname);
      // console.log(`profileData\n: ${JSON.stringify(data)}`); // Delete!
    } catch (e) {
      // console.error("fetchProfile");
      setError(e.message);
    }
  };

  // 닉네임 업데이트
  const handleDisplayNameSubmit = async () => {
    try {
      const response = await fetch("/api/v1/users/profile", {
        method: "PATCH",
        headers: {
          "Content-Type": "application/json",
        },
        credentials: "include",
        body: JSON.stringify({ displayname: newDisplayName }),
      });

      if (!response.ok) {
        const e = await response.json();
        throw new Error(e.error.message);
      }

      await fetchProfile();
      setIsEditing(false);
    } catch (e) {
      // console.error("handleDisplayNameSubmit: fetchProfile");
      setError(e.message);
    }
  };

  // 아바타 업로드
  const handleAvatarChange = async (event) => {
    const file = event.target.files[0];
    if (file) {
      if (file.size > 5 * 1024 * 1024) {
        // 5MB 제한
        alert("File size must be less than 5MB");
        return;
      }

      const reader = new FileReader();
      reader.onloadend = async () => {
        const base64data = reader.result.split(",")[1];

        try {
          const response = await fetch(
            getRobustEndpoint("/api/v1/users/profile"),
            {
              method: "PATCH",
              headers: {
                "Content-Type": "application/json",
              },
              credentials: "include",
              body: JSON.stringify({ avatar: base64data }),
            }
          );

          if (!response.ok) {
            const e = response.json();
            throw new Error(e.error.message);
          }

          await fetchProfile();
        } catch (e) {
          // console.error("handleAvatarChange");
          setError(e.message);
        }
      };
      reader.readAsDataURL(file);
    }
  };

  const [showQr, setShowQr] = useState(false);

  // 2FA Qr 등록 컴포넌트 보이기
  const handle2FASetup = async () => {
    setShowQr(true);
  };

  if (!profileData) {
    return (
      <div
        className="position-absolute spinner-border text-light top-50 start-50"
        role="status"
      />
    );
  }

  return (
    <>
      <div className="card bg-dark text-light">
        <div className="card-body">
          <div className="d-flex align-items-center mb-4">
            {/* Avatar */}
            <div className="position-relative me-3">
              <img
                src={
                  profileData.user.avatar
                    ? "media/" + profileData.user.avatar
                    : "/static/assets/camera-fill.svg"
                }
                alt="Avatar"
                className="rounded-circle"
                style={{ width: "100px", height: "100px", objectFit: "cover" }}
              />
              <label className="position-absolute bottom-0 end-0 btn btn-sm btn-primary rounded-circle p-1">
                <input
                  type="file"
                  className="d-none"
                  accept="image/jpeg,image/png"
                  onChange={handleAvatarChange}
                />
                <i className="bi bi-camera-fill"></i>
              </label>
            </div>

            {/* Profile Info */}
            <div>
              {isEditing ? (
                <div className="input-group mb-2">
                  <input
                    type="text"
                    className="form-control"
                    value={newDisplayName}
                    onChange={(e) => setNewDisplayName(e.target.value)}
                  />
                  <button
                    className="btn btn-success"
                    onClick={handleDisplayNameSubmit}
                  >
                    Save
                  </button>
                  <button
                    className="btn btn-secondary"
                    onClick={() => {
                      setIsEditing(false);
                      setNewDisplayName(profileData.displayname);
                    }}
                  >
                    Cancel
                  </button>
                </div>
              ) : (
                <h5
                  className="mb-1"
                  onClick={() => setIsEditing(true)}
                  style={{ cursor: "pointer" }}
                >
                  {profileData.user.displayname}{" "}
                  <i className="bi bi-pencil-fill small"></i>
                </h5>
              )}
              <p className="text-light mb-1">{profileData.user.email}</p>
            </div>
            <button
              type="button"
              className="btn btn-dark position-absolute top-0 end-0 mt-5 me-2"
              disabled={profileData.user.is_2fa_enabled}
              onClick={handle2FASetup}
            >
              {profileData.user.is_2fa_enabled ? "2FA enabled" : "enable 2FA"}
            </button>
          </div>
          {/* Stats - 실제 계산된 값 사용 */}
          <div className="row text-center">
            <div className="col">
              <h6>Win Rate</h6>
              <p className="mb-0">
                {matches.length > 0
                  ? Math.round(
                      (matches.filter(
                        (m) => m.winner?.user_id === profileData.user?.user_id
                      ).length /
                        matches.length) *
                        100
                    )
                  : 0}
                %
              </p>
            </div>
            <div className="col">
              <h6>Matches</h6>
              <p className="mb-0">{matches.length}</p>
            </div>
            <div className="col">
              <h6>Wins</h6>
              <p className="mb-0">
                {
                  matches.filter(
                    (m) => m.winner?.user_id === profileData.user?.user_id
                  ).length
                }
              </p>
            </div>
          </div>

          {/* Match History */}
          <MatchHistory matches={matches} myuser_id={profileData.user.user_id} />

          {error && (
            <div className="alert alert-danger mt-3" role="alert">
              {error}
            </div>
          )}

          {/* {showQr ? (
            <>
              <Qr /> <AuthCodeInput />{" "}
            </>
          ) : null} */}
          {/* <QrRegistration /> */}
        </div>
      </div>
      {showQr ? (
        <div className="d-grid gap-5 col-6 mx-auto">
          <QrRegistration />
        </div>
      ) : null}
    </>
  );
}

// // 타인의 프로필 컴포넌트
// 나의 프로필 컴포넌트
export function OtherProfile({ otherProfileData }) {
  // const [matches, setMatches] = useState([]);

  // 매치 히스토리 가져오기
  // useEffect(() => {
  //   const fetchMatches = async () => {
  //     try {
  //       const response = await fetch("/api/v1/game/matches?limit=5");

  //       if (!response.ok) throw new Error("Failed to fetch matches");

  //       const data = await response.json();
  //       setMatches(data.matches);
  //     } catch (e) {
  //       setError(e.message);
  //     }
  //   };

  //   fetchMatches();
  //   // console.log(`profileData\n: ${JSON.stringify(profileData)}`); // Delete!
  // }, []);

  // const [profile, setProfile] = useState(null);
  // const [selectedFile, setSelectedFile] = useState(profileData?.user?.avatar);
  const navigate = useNavigate();

  // // 프로필 정보 가져오기
  // useEffect(() => {
  //   fetchProfile();
  // }, []);

  // const fetchProfile = async () => {
  //   try {
  //     const response = await fetch("/api/v1/users/profile", {
  //       credentials: "include",
  //     });

  //     if (!response.ok) {
  //       throw new Error("You have been logged out");
  //     }

  //     const data = await response.json();
  //     // alert(JSON.stringify(data));
  //     setProfileData(data);
  //     setNewDisplayName(data?.user.displayname);
  //     // console.log(`profileData\n: ${JSON.stringify(data)}`); // Delete!
  //   } catch (e) {
  //     setError(e.message);
  //   }
  // };

  // 닉네임 업데이트
  // const handleDisplayNameSubmit = async () => {
  //   try {
  //     const response = await fetch("/api/v1/users/profile", {
  //       method: "PATCH",
  //       headers: {
  //         "Content-Type": "application/json",
  //       },
  //       credentials: "include",
  //       body: JSON.stringify({ displayname: newDisplayName }),
  //     });

  //     if (!response.ok) {
  //       const e = await response.json();
  //       throw new Error(e.error.message);
  //     }

  //     await fetchProfile();
  //     setIsEditing(false);
  //   } catch (e) {
  //     setError(e.message);
  //   }
  // };

  // // 아바타 업로드
  // const handleAvatarChange = async (event) => {
  //   const file = event.target.files[0];
  //   if (file) {
  //     if (file.size > 5 * 1024 * 1024) {
  //       // 5MB 제한
  //       alert("File size must be less than 5MB");
  //       return;
  //     }

  //     const reader = new FileReader();
  //     reader.onloadend = async () => {
  //       const base64data = reader.result.split(",")[1];

  //       try {
  //         const response = await fetch(
  //           getRobustEndpoint("/api/v1/users/profile"),
  //           {
  //             method: "PATCH",
  //             headers: {
  //               "Content-Type": "application/json",
  //             },
  //             credentials: "include",
  //             body: JSON.stringify({ avatar: base64data }),
  //           }
  //         );

  //         if (!response.ok) {
  //           throw new Error("Failed to update avatar");
  //         }

  //         await fetchProfile();
  //       } catch (e) {
  //         alert(e.message);
  //       }
  //     };
  //     reader.readAsDataURL(file);
  //   }
  // };

  if (!otherProfileData) {
    return (
      <div
        className="position-relative spinner-border text-light top-50 start-50"
        role="status"
      />
    );
  }

  return (
    <>
      <div
        className="card bg-dark text-light"
        style={{ backgroundColor: "black" }}
      >
        <div className="card-body">
          <div className="d-flex align-items-center mb-4">
            {/* Avatar */}
            <div className="position-relative me-3">
              <img
                src={
                  otherProfileData.profile.avatar
                    ? "media/" + otherProfileData.profile.avatar
                    : "/static/assets/camera-fill.svg"
                }
                alt="Avatar"
                className="rounded-circle"
                style={{ width: "100px", height: "100px", objectFit: "cover" }}
              />
            </div>

            {/* Profile Info */}
            <div>
              <h5
                className="mb-1"
                // onClick={() => setIsEditing(true)}
                // style={{ cursor: "pointer" }}
              >
                {otherProfileData.profile.displayname}{" "}
                <i className="bi bi-pencil-fill small"></i>
              </h5>
              <p className="text-light mb-1">
                {otherProfileData.profile.email}
              </p>
            </div>
          </div>

          {/* Stats - 실제 계산된 값 사용 */}
          <div className="row text-center">
            <div className="col">
              <h6>Win Rate</h6>
              <p className="mb-0">{otherProfileData.profile.stats.win_rate}%</p>
            </div>
            <div className="col">
              <h6>Matches</h6>
              <p className="mb-0">
                {otherProfileData.profile.stats.total_matches}
              </p>
            </div>
            <div className="col">
              <h6>Wins</h6>
              <p className="mb-0">{otherProfileData.profile.stats.wins}</p>
            </div>
          </div>

          {/* Match History */}
          {/* <MatchHistory matches={matches} /> */}
          {/* 
        {error && (
          <div className="alert alert-danger mt-3" role="alert">
            {error}
          </div>
        )} */}
        </div>
      </div>
    </>
  );
}

// export function UserProfile({ userId }) {
//   const [profile, setProfile] = useState(null);
//   const [error, setError] = useState(null);
//   const navigate = useNavigate();

//   useEffect(() => {
//     const fetchUserProfile = async () => {
//       try {
//         // Note: 이 엔드포인트는 백엔드에 추가 구현이 필요합니다
//         const response = await fetch(`/api/v1/users/${userId}/profile`, {
//           credentials: "include",
//         });

//         if (!response.ok) {
//           throw new Error("Failed to fetch user profile");
//         }

//         const data = await response.json();
//         setProfile(data);
//       } catch (error) {
//         setError("Failed to load user profile");
//         console.error("Profile fetch error:", error);
//       }
//     };

//     if (userId) {
//       fetchUserProfile();
//     }
//   }, [userId]);

//   if (!profile) {
//     return <div className="spinner-border text-light" role="status" />;
//   }

//   return (
//     <div className="card bg-dark text-light">
//       <div className="card-body">
//         <div className="d-flex align-items-center mb-4">
//           {/* Avatar */}
//           <img
//             src={profile.avatar || "/api/placeholder/100/100"}
//             alt="Avatar"
//             className="rounded-circle me-3"
//             style={{ width: "100px", height: "100px", objectFit: "cover" }}
//           />

//           {/* Profile Info */}
//           <div>
//             <h5 className="mb-1">{profile.displayname}</h5>
//             <p className="text-muted mb-1">{profile.email}</p>
//           </div>
//         </div>

//         {/* Stats */}
//         <div className="row text-center">
//           <div className="col">
//             <h6>Win Rate</h6>
//             <p className="mb-0">75%</p>
//           </div>
//           <div className="col">
//             <h6>Matches</h6>
//             <p className="mb-0">24</p>
//           </div>
//           <div className="col">
//             <h6>Wins</h6>
//             <p className="mb-0">18</p>
//           </div>
//         </div>

//         {error && (
//           <div className="alert alert-danger mt-3" role="alert">
//             {error}
//           </div>
//         )}
//       </div>
//     </div>
//   );
// }
