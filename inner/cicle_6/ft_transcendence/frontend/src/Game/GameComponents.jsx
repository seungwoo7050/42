import React from "react";
import { useNavigate } from "react-router-dom";

// 게임 모드별 컨트롤 설명
const CONTROLS = {
  ai: {
    title: "vs. AI",
    controls: [
      { key: "Q", description: "패들 위로 이동" },
      { key: "A", description: "패들 아래로 이동" },
    ],
  },
  pvp: {
    title: "PvP Match",
    controls: [
      { key: "Q", description: "Player 1 패들 위로 이동" },
      { key: "A", description: "Player 1 패들 아래로 이동" },
      { key: "O", description: "Player 2 패들 위로 이동" },
      { key: "L", description: "Player 2 패들 아래로 이동" },
    ],
  },
  tournament: {
    title: "Tournament",
    controls: [
      { key: "Q", description: "패들 위로 이동" },
      { key: "A", description: "패들 아래로 이동" },
    ],
  },
};

// 게임 나가기 버튼 컴포넌트
export function SignOut() {
  const navigate = useNavigate();

  const handleSignOut = async () => {
    try {
      // 게임 상태 해제
      await fetch('/api/v1/game/matchmaking', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'include',
        body: JSON.stringify({ action: 'leave' })
      });

      navigate('/');
    } catch (error) {
      console.error('Error leaving game:', error);
      navigate('/');
    }
  };

  return (
    <div
      className="position-absolute top-0 end-0 m-4"
      style={{ cursor: "pointer", zIndex: 100 }}
      onClick={handleSignOut}
    >
      <p className="text-light fs-4">Exit</p>
    </div>
  );
}

// 사이드바 컨트롤 설명 컴포넌트
export function SideBar({ mode, keysPressed }) {
  const controls = CONTROLS[mode] || CONTROLS.ai;

  return (
    <div
      className="d-flex flex-column text-light px-5"
      style={{
        width: "20rem",
        minWidth: "20rem",
        backgroundColor: "#1a1a1a",
      }}
    >
      <h2 className="text-center my-4">{controls.title}</h2>
      <div className="mt-4">
        <h3 className="mb-4">Controls</h3>
        <div className="d-flex flex-column gap-3">
          {controls.controls.map(({ key, description }) => (
            <div key={key} className="d-flex align-items-center gap-3">
              <div
                className={`border border-light rounded px-3 py-2 ${
                  keysPressed?.get(key?.toLowerCase())
                    ? "bg-light text-dark"
                    : "text-light"
                }`}
                style={{ minWidth: "3rem", textAlign: "center" }}
              >
                {key}
              </div>
              <span>{description}</span>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}