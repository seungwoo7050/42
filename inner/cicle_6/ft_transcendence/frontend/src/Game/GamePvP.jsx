import React, { useState, useEffect } from "react";
import { useNavigate, useLocation } from "react-router-dom";
import Pong from "./Pong";
import { SignOut, SideBar } from "./GameComponents";
import { getRobustEndpoint } from "../utils.js";

export function GamePvP() {
  const navigate = useNavigate();
  const location = useLocation();
  const [keysPressed, setKeysPressed] = useState(new Map());
  const [matchInitialized, setMatchInitialized] = useState(false);
  const [opponent, setOpponent] = useState(null);

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

      const params = new URLSearchParams(location.search);
      const opponentId = params.get('opponent');

      if (!opponentId) {
        alert('상대방 정보가 없습니다.');
        navigate('/');
        return;
      }

      try {
        const response = await fetch('/api/v1/game/matchmaking', {
          method: 'POST',
          headers: { 
            'Content-Type': 'application/json',
            'Accept': 'application/json'
          },
          credentials: 'include',
          body: JSON.stringify({ 
            action: 'join',
            opponent_id: opponentId
          })
        });

        if (!response.ok) {
          const error = await response.json();
          throw new Error(error.error?.message || 'Failed to start match');
        }

        setOpponent(opponentId);
        setMatchInitialized(true);
      } catch (error) {
        console.error('Matchmaking error:', error);
        alert(error.message);
        navigate('/');
      }
    };

    initializeGame();
  }, [matchInitialized, location.search, navigate]);

  // 게임 종료 처리
  const handleGameEnd = async (result) => {
    try {
      // 매치 결과 저장
      await fetch('/api/v1/game/matches', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'include',
        body: JSON.stringify({
          opponent_id: opponent,
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
        body: JSON.stringify({ 
          action: 'leave',
          opponent_id: opponent
         })
      });

      // navigate('/');
      location.href = getRobustEndpoint("/");
    } catch (error) {
      console.error('Game end error:', error);
      // navigate('/');
      location.href = getRobustEndpoint("/");
    }
  };

  return (
    <>
      <SignOut />
      <div className="d-flex" style={{ marginTop: "3rem" }}>
        <SideBar mode="pvp" keysPressed={keysPressed} />
        <div className="position-relative main-panel">
          <Pong
            keysPressed={keysPressed}
            setKeysPressed={setKeysPressed}
            player1ID="me"
            player2ID={opponent || "opponent"}
            onGameEnd={handleGameEnd}
          />
        </div>
      </div>
    </>
  );
}

export default GamePvP;