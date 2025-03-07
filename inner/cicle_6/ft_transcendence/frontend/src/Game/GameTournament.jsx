import React, { useState, useEffect } from 'react';
import { useNavigate, useLocation } from 'react-router-dom';
import Pong from "./Pong";
import { SignOut, SideBar } from "./GameComponents";
import { getRobustEndpoint } from "../utils.js";

const TOURNAMENT_STATE_KEY = 'tournament_state';
const TOURNAMENT_ROUNDS = {
  0: '4강전 1',
  1: '4강전 2',
  2: '결승전'
};

export function GameTournament() {
  const navigate = useNavigate();
  const location = useLocation();
  const [keysPressed, setKeysPressed] = useState(new Map());
  const [matchInitialized, setMatchInitialized] = useState(false);
  const [opponent, setOpponent] = useState(null);
  const [tournamentState, setTournamentState] = useState(() => {
    const saved = localStorage.getItem(TOURNAMENT_STATE_KEY);
    return saved ? JSON.parse(saved) : {
      round: 0,
      player1Won: false,
      opponentWon: false,
      humanOpponentId: null
    };
  });

  // 토너먼트 상태 저장
  useEffect(() => {
    localStorage.setItem(TOURNAMENT_STATE_KEY, JSON.stringify(tournamentState));
  }, [tournamentState]);

  // cleanup effect
  useEffect(() => {
    return async () => {
      try {
        await fetch('/api/v1/game/matchmaking', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          credentials: 'include',
          body: JSON.stringify({ action: 'leave' })
        });
        localStorage.removeItem(TOURNAMENT_STATE_KEY);
      } catch (error) {
        console.error('Cleanup error:', error);
      }
    };
  }, []);

  // 게임 초기화
  useEffect(() => {
    const initializeGame = async () => {
      if (matchInitialized) return;

      // 첫 라운드에서 상대방 ID 저장
      if (tournamentState.round === 0) {
        const params = new URLSearchParams(location.search);
        const humanOpponentId = params.get('opponent');
        if (!humanOpponentId) {
          alert('상대방 정보가 없습니다.');
          navigate('/');
          return;
        }
        setTournamentState(prev => ({...prev, humanOpponentId}));
      }

      // 현재 라운드에 따른 상대 설정
      const currentOpponent = tournamentState.round < 2 ? 'AI' : tournamentState.humanOpponentId;
      setOpponent(currentOpponent);

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
            opponent_id: currentOpponent
          })
        });

        if (!response.ok) {
          const error = await response.json();
          throw new Error(error.error?.message || 'Failed to start match');
        }

        setMatchInitialized(true);
      } catch (error) {
        console.error('Matchmaking error:', error);
        alert(error.message);
        navigate('/');
      }
    };

    initializeGame();
  }, [tournamentState.round, matchInitialized, navigate, location.search]);

  // 토너먼트 종료
  const endTournament = async () => {
    try {
      await fetch('/api/v1/game/matchmaking', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'include',
        body: JSON.stringify({ action: 'leave' })
      });
      localStorage.removeItem(TOURNAMENT_STATE_KEY);
      location.href = getRobustEndpoint("/");
    } catch (error) {
      console.error('Tournament end error:', error);
      location.href = getRobustEndpoint("/");
    }
  };

  // 토너먼트 매치 결과 처리
  const handleTournamentMatch = async (result) => {
    try {
      // 매치 결과 저장
      // await fetch('/api/v1/game/matches', {
      //   method: 'POST',
      //   headers: { 'Content-Type': 'application/json' },
      //   credentials: 'include',
      //   body: JSON.stringify({
      //     opponent_id: opponent,
      //     score_player1: result.score1,
      //     score_player2: result.score2,
      //     winner: result.winner,
      //     is_tournament: true
      //   })
      // });

      // 현재 매치 종료 처리
      await fetch('/api/v1/game/matchmaking', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'include',
        body: JSON.stringify({ action: 'leave' })
      });

      // 라운드별 처리
      if (tournamentState.round === 0) {
        // 첫 번째 4강전 (플레이어 vs AI)
        setTournamentState(prev => ({
          ...prev,
          round: 1,
          player1Won: result.winner === 'player1'
        }));
        setMatchInitialized(false);
      } 
      else if (tournamentState.round === 1) {
        // 두 번째 4강전 (상대방 vs AI)
        const opponentWon = result.winner === 'player1';
        if (!tournamentState.player1Won && !opponentWon) {
          // 둘 다 AI에게 졌으면 토너먼트 종료
          await endTournament();
        } else if (tournamentState.player1Won && opponentWon) {
          // 둘 다 이겼으면 결승전 진행
          setTournamentState(prev => ({
            ...prev,
            round: 2,
            opponentWon
          }));
          setMatchInitialized(false);
        } else {
          // 한 명만 이겼으면 토너먼트 종료
          await endTournament();
        }
      } 
      else {
        // 결승전 종료
        await endTournament();
      }
    } catch (error) {
      console.error('Tournament match error:', error);
      location.href = getRobustEndpoint("/");
    }
  };

  return (
    <>
      <SignOut />
      <div className="d-flex" style={{ marginTop: "3rem" }}>
        <SideBar mode="tournament" keysPressed={keysPressed} />
        <div className="position-relative main-panel">
          <h2 className="text-center text-light mb-4">
            {TOURNAMENT_ROUNDS[tournamentState.round]}
          </h2>
          <Pong
            keysPressed={keysPressed}
            setKeysPressed={setKeysPressed}
            player1ID="me"
            player2ID={opponent || "opponent"}
            onGameEnd={handleTournamentMatch}
            isAI={opponent === 'AI'}
          />
        </div>
      </div>
    </>
  );
}

export default GameTournament;