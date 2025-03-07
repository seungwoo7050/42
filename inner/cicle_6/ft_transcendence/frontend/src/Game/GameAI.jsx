import React, { useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import Pong from "./Pong";
import { SignOut, SideBar } from "./GameComponents";
import { getRobustEndpoint } from "../utils.js";

export function GameAI() {
  const navigate = useNavigate();
  const [keysPressed, setKeysPressed] = useState(new Map());
  const [matchInitialized, setMatchInitialized] = useState(false);

  // // 페이지 이탈 방지
  // useEffect(() => {
  //   const handleUnload = (e) => {
  //     e.preventDefault();
  //     e.returnValue = "";
  //   };

  //   window.addEventListener("unload", handleUnload);
  //   window.addEventListener("beforeunload", handleUnload);
  //   return () => {
  //     window.removeEventListener("unload", handleUnload);
  //     window.removeEventListener("beforeunload", handleUnload);
  //   };
  // }, []);

  // 게임 초기화
  useEffect(() => {
    const initializeGame = async () => {
      if (matchInitialized) return;

      try {
          // 플레이어만 게임 상태로 등록
          const response = await fetch('/api/v1/game/matchmaking', {
              method: 'POST',
              headers: { 
                  'Content-Type': 'application/json',
                  'Accept': 'application/json'
              },
              credentials: 'include',
              body: JSON.stringify({ 
                  action: 'join',
                  opponent_id: 'AI'  // AI는 실제로 매칭되지 않고 식별자로만 사용
              })
          });

          if (!response.ok) {
              const error = await response.json();
              throw new Error(error.error?.message || 'Failed to start match');
          }

          setMatchInitialized(true);
      } catch (error) {
          console.error('Game initialization error:', error);
          alert(error.message);
          navigate('/');
      }
    };

    initializeGame();
  }, [matchInitialized, navigate]);

  // GameAI.jsx에 cleanup 효과 추가
  useEffect(() => {
    return async () => {
        try {
            await fetch('/api/v1/game/matchmaking', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                credentials: 'include',
                body: JSON.stringify({ action: 'leave' })
            });
        } catch (error) {
            console.error('Cleanup error:', error);
        }
    };
  }, []);

  // 게임 종료 처리
  const handleGameEnd = async (result) => {
    try {
      // 매치 결과 저장
      await fetch('/api/v1/game/matches', {
        method: 'POST',
        headers: { 
          'Content-Type': 'application/json' 
        },
        credentials: 'include',
        body: JSON.stringify({
          opponent_id: 'AI',
          score_player1: result.score1,
          score_player2: result.score2,
          winner: result.winner
        })
      });

      // 게임 상태 해제
      await fetch('/api/v1/game/matchmaking', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'include',
        body: JSON.stringify({ action: 'leave' })
      });

      // navigate('/');
      location.href = getRobustEndpoint("/");
    } catch (error) {
      console.error('Game end error:', error);
      // navigate('/');
      location.href = getRobustEndpoint("/");
    }
  };

  // GameAI.jsx - return 부분 수정
  return (
    <>
        <SignOut />
        <div className="d-flex" style={{ marginTop: "3rem" }}>
            <SideBar mode="ai" keysPressed={keysPressed} />
            <div className="position-relative main-panel">
                <Pong
                    keysPressed={keysPressed}
                    setKeysPressed={setKeysPressed}
                    player1ID="me"
                    player2ID="AI"
                    onGameEnd={handleGameEnd}
                    isAI={true}  // isAI prop 추가
                />
            </div>
        </div>
    </>
  );
}

export default GameAI;