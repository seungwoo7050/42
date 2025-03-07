import React, {
  useState,
  useEffect,
  useRef,
  useMemo,
  useCallback,
} from "react";
import { Canvas, useFrame, useThree } from "@react-three/fiber";
import {
  OrbitControls,
  useTexture,
  Effects,
  Trail,
  Text3D,
  MeshReflectorMaterial,
} from "@react-three/drei";
import {
  EffectComposer,
  Bloom,
  ChromaticAberration,
} from "@react-three/postprocessing";
import * as THREE from "three";

// Enhanced colors with neon feel
const COLORS = {
  green: new THREE.Color("#00ff88"),
  yellow: new THREE.Color("#ffff00"),
  blue: new THREE.Color("#0088ff"),
  purple: new THREE.Color("#ff00ff"),
  background: new THREE.Color("#000000"),
};

// Style constants for UI
const GREEN = "rgb(60, 120, 60)";
const YELLOW = "rgb(180, 150, 50)";
const YELLOW_BOLD = "rgb(240, 200, 80)";
const YELLOW_DIM = "rgba(180, 150, 50, 0.8)";
const RED = "rgb(120, 40, 40)";

// Memoized geometries
const ballGeometry = new THREE.SphereGeometry(0.4);
const paddleGeometry = new THREE.BoxGeometry(0.8, 3, 2.0);
const fieldGeometry = new THREE.PlaneGeometry(30, 15);

// Optimized materials with emissive properties
const createMaterial = (color, emissiveIntensity = 1) => {
  return new THREE.MeshStandardMaterial({
    color: color,
    emissive: color,
    emissiveIntensity: emissiveIntensity,
    metalness: 0.8,
    roughness: 0.2,
  });
};

// Optimized Ball component with trail effect
const Ball = React.memo(({ position, ballRef }) => {
  const material = useMemo(() => createMaterial(COLORS.green.getHex()), []);

  return (
    <Trail
      width={1}
      length={8}
      color={new THREE.Color(0x88ff88)}
      attenuation={(t) => t * t}
    >
      <mesh
        ref={ballRef}
        position={position}
        geometry={ballGeometry}
        material={material}
      >
        <pointLight distance={3} intensity={2} color={COLORS.green} />
      </mesh>
    </Trail>
  );
});

// Optimized Paddle component with glow effect
const Paddle = React.memo(({ position, paddleRef, color }) => {
  const material = useMemo(() => createMaterial(color, 1.5), [color]);

  return (
    <mesh
      ref={paddleRef}
      position={position}
      geometry={paddleGeometry}
      material={material}
    >
      <pointLight distance={4} intensity={1} color={color} />
    </mesh>
  );
});

// Center line component
const CenterLine = React.memo(() => {
  return (
    <mesh rotation={[-Math.PI / 2, 0, 0]} position={[0, -0.45, 0]}>
      <planeGeometry args={[0.1, 15]} />
      <meshBasicMaterial color={COLORS.yellow} transparent opacity={0.3} />
    </mesh>
  );
});

// Enhanced Field component with reflective surface
const Field = React.memo(() => {
  return (
    <>
      <mesh rotation={[-Math.PI / 2, 0, 0]} position={[0, -0.5, 0]}>
        <planeGeometry args={[30, 15]} />
        <MeshReflectorMaterial
          blur={[400, 100]}
          resolution={1024}
          mixBlur={1}
          mixStrength={15}
          depthScale={1}
          minDepthThreshold={0.85}
          color="#050505"
          metalness={0.6}
          roughness={1}
        />
      </mesh>
      <mesh rotation={[-Math.PI / 2, 0, 0]} position={[0, -0.48, 0]}>
        <planeGeometry args={[30, 15]} />
        <meshBasicMaterial
          color={COLORS.blue}
          opacity={0.1}
          transparent
          wireframe
        />
      </mesh>
      <CenterLine />
    </>
  );
});

// ScoreBoard component
const ScoreBoard = React.memo(({ player1, player2, max_score }) => {
  return (
    <>
      <div
        className="d-flex justify-content-center align-items-center"
        style={{
          position: "absolute",
          bottom: "0%",
          width: "100%",
          padding: "0rem",
          gap: "5rem",
          zIndex: 10,
        }}
      >
        <p
          style={{
            color: player1.score + 1 === max_score ? YELLOW_BOLD : YELLOW_DIM,
            fontSize: "3rem",
          }}
        >
          {player1.score}
        </p>
        <p
          style={{
            color: player2.score + 1 === max_score ? YELLOW_BOLD : YELLOW_DIM,
            fontSize: "3rem",
          }}
        >
          {player2.score}
        </p>
      </div>
      <p
        className="fs-3 position-absolute py-3 ps-5 bottom-0 start-5"
        style={{ color: GREEN, zIndex: 10 }}
      >
        {player1.id}
      </p>
      <p
        className="fs-3 position-absolute py-3 pe-5 bottom-0 end-0"
        style={{ color: GREEN, zIndex: 10 }}
      >
        {player2.id}
      </p>
    </>
  );
});

// GameOverMenu component
const GameOverMenu = React.memo(
  ({ setPlayer1Score, setPlayer2Score, setIsGameOver }) => {
    const redirectToHome = () => {
      window.location.href = window.location.origin;
    };

    const requestReplay = () => {
      setIsGameOver(false);
      setPlayer1Score(0);
      setPlayer2Score(0);
    };

    return (
      <div className="d-flex flex-column align-items-center">
        <div
          className="fs-4 text-light"
          onClick={requestReplay}
          style={{
            cursor: "pointer",
            display: "inline-block",
          }}
        >
          <p className="banner-hover">Replay</p>
        </div>
        <div
          className="fs-4 text-light"
          onClick={redirectToHome}
          style={{
            cursor: "pointer",
            display: "inline-block",
          }}
        >
          <p className="banner-hover">Exit</p>
        </div>
      </div>
    );
  }
);

// GameOverScreen component
const GameOverScreen = React.memo(
  ({ player1, player2, setPlayer1Score, setPlayer2Score, setIsGameOver }) => {
    const [winner, loser] =
      player1.score > player2.score ? [player1, player2] : [player2, player1];

    const margin = winner.score - loser.score;

    return (
      <div
        className="d-flex flex-column align-items-center justify-content-center"
        style={{
          height: "calc(100vh - 10rem)",
          color: GREEN,
          zIndex: 20,
        }}
      >
        <div className="p-2">
          <p className="fs-1">Game Over!</p>
        </div>
        <div className="p-2 d-flex flex-row align-items-center">
          <p className="fs-3 m-0" style={{ color: YELLOW }}>
            {winner.id}
          </p>
          <p className="fs-3 m-0 px-2"> won by</p>
          <p className="fs-3 m-0" style={{ color: YELLOW }}>
            {margin}
          </p>
          <p className="fs-3 m-0 px-2">
            {margin === 1 ? "point" : "points"} against
          </p>
          <p className="fs-3 m-0" style={{ color: RED }}>
            {loser.id}
          </p>
        </div>
        <div style={{ marginTop: "3rem" }}>
          <GameOverMenu
            setPlayer1Score={setPlayer1Score}
            setPlayer2Score={setPlayer2Score}
            setIsGameOver={setIsGameOver}
          />
        </div>
      </div>
    );
  }
);

// GameScene component with enhanced visuals and optimized game logic
function GameScene({
  isAI,
  isGameOver,
  keysPressed,
  setKeysPressed,
  setPlayer1Score,
  setPlayer2Score,
}) {
  const ballRef = useRef();
  const paddle1Ref = useRef();
  const paddle2Ref = useRef();

  // Optimized game constants
  const GAME_CONFIG = useMemo(
    () => ({
      BALL_SPEED: 0.2,
      PADDLE_SPEED: 0.2,
      FIELD_WIDTH: 30,
      FIELD_HEIGHT: 15,
      AI_DIFFICULTY: 0.85,
    }),
    []
  );

  const getRandomVelocity = (speed) => {
    const choose = Math.random() < 0.5 ? 0 : 1;
    const angle =
      choose * ((Math.random() * Math.PI) / 2 - Math.PI / 4) +
      // Choose an angle between -π/4 and π/4; or
      (1 - choose) * ((Math.random() * Math.PI) / 2 + (3 * Math.PI) / 4);
    // Choose an angle between 3π/4 and 5π/4

    const vx = Math.cos(angle) * speed;
    const vz = Math.sin(angle) * speed;

    return new THREE.Vector3(vx, 0, vz);
  };

  // Optimized game state
  const gameState = useRef({
    ballVelocity: getRandomVelocity(GAME_CONFIG.BALL_SPEED),
    keysPressed: new Set(),
    lastUpdateTime: 0,
  });

  // Optimized key handlers
  const handleKeyDown = useCallback((e) => {
    gameState.current.keysPressed.add(e.key.toLowerCase());
    setKeysPressed((prevKeysPressed) => {
      const newKeysPressed = new Map(prevKeysPressed);
      newKeysPressed.set(e.key, true);
      return newKeysPressed;
    });
  }, []);

  const handleKeyUp = useCallback((e) => {
    gameState.current.keysPressed.delete(e.key.toLowerCase());
    setKeysPressed((prevKeysPressed) => {
      const newKeysPressed = new Map(prevKeysPressed);
      newKeysPressed.delete(e.key);
      return newKeysPressed;
    });
  }, []);

  // Key event listeners
  useEffect(() => {
    window.addEventListener("keydown", handleKeyDown);
    window.addEventListener("keyup", handleKeyUp);
    return () => {
      window.removeEventListener("keydown", handleKeyDown);
      window.removeEventListener("keyup", handleKeyUp);
    };
  }, [handleKeyDown, handleKeyUp]);

  // Optimized game update logic
  const updateGame = useCallback(
    (delta) => {
      if (isGameOver) return;

      // Update ball position with delta time
      if (ballRef.current) {
        ballRef.current.position.add(
          gameState.current.ballVelocity.clone().multiplyScalar(delta * 60)
        );
      }

      // Update paddle positions
      if (paddle1Ref.current) {
        const paddle1Delta =
          (gameState.current.keysPressed.has("q") ? -1 : 0) +
          (gameState.current.keysPressed.has("a") ? 1 : 0);

        paddle1Ref.current.position.z +=
          paddle1Delta * GAME_CONFIG.PADDLE_SPEED * delta * 60;

        // Clamp paddle position
        paddle1Ref.current.position.z = THREE.MathUtils.clamp(
          paddle1Ref.current.position.z,
          -GAME_CONFIG.FIELD_HEIGHT / 2 + 1.5,
          GAME_CONFIG.FIELD_HEIGHT / 2 - 1.5
        );
      }

      // Enhanced AI logic
      // 위치: GameScene 컴포넌트 내부
      // 약 350-365줄 사이의 AI 로직을 아래 코드로 교체

      if (paddle2Ref.current && isAI) {
        if (ballRef.current.position.x > 0) {
          // Add reaction delay (20% chance to skip update)
          if (Math.random() > 0.2) {
            const errorMargin = 0.5; // AI targeting error range
            const targetZ =
              ballRef.current.position.z +
              (Math.random() * errorMargin - errorMargin / 2);
            const currentZ = paddle2Ref.current.position.z;
            const aiSpeed =
              GAME_CONFIG.PADDLE_SPEED * GAME_CONFIG.AI_DIFFICULTY;

            if (Math.abs(currentZ - targetZ) > 0.5) {
              paddle2Ref.current.position.z +=
                Math.sign(targetZ - currentZ) * aiSpeed * delta * 60;
            }
          }
        }
      } else if (paddle2Ref.current) {
        const paddle2Delta =
          (gameState.current.keysPressed.has("o") ? -1 : 0) +
          (gameState.current.keysPressed.has("l") ? 1 : 0);

        paddle2Ref.current.position.z +=
          paddle2Delta * GAME_CONFIG.PADDLE_SPEED * delta * 60;

        paddle2Ref.current.position.z = THREE.MathUtils.clamp(
          paddle2Ref.current.position.z,
          -GAME_CONFIG.FIELD_HEIGHT / 2 + 1.5,
          GAME_CONFIG.FIELD_HEIGHT / 2 - 1.5
        );
      }

      // Enhanced collision detection with paddle angles
      if (ballRef.current) {
        // Wall collisions
        if (
          Math.abs(ballRef.current.position.z) >=
          GAME_CONFIG.FIELD_HEIGHT / 2 - 0.4
        ) {
          gameState.current.ballVelocity.z *= -1.05; // Add slight speed increase
        }

        // Enhanced paddle collision
        [paddle1Ref, paddle2Ref].forEach((paddleRef) => {
          if (!paddleRef.current) return;

          const paddleBox = new THREE.Box3().setFromObject(paddleRef.current);
          const ballBox = new THREE.Box3().setFromObject(ballRef.current);

          if (paddleBox.intersectsBox(ballBox)) {
            // Reverse x direction
            gameState.current.ballVelocity.x *= -1.05;

            // Calculate angle based on hit position
            const relativeIntersectZ =
              (ballRef.current.position.z - paddleRef.current.position.z) / 2.5;

            // Add spin effect
            gameState.current.ballVelocity.z =
              GAME_CONFIG.BALL_SPEED * relativeIntersectZ * 1.2;

            // Add slight random variation
            gameState.current.ballVelocity.z += (Math.random() - 0.5) * 0.02;
          }
        });

        // Scoring logic with enhanced ball reset
        if (ballRef.current.position.x <= -GAME_CONFIG.FIELD_WIDTH / 2) {
          setPlayer2Score((prev) => prev + 1);
          respawnBall(1);
        } else if (ballRef.current.position.x >= GAME_CONFIG.FIELD_WIDTH / 2) {
          setPlayer1Score((prev) => prev + 1);
          respawnBall(-1);
        }
      }
    },
    [GAME_CONFIG, isAI, isGameOver, setPlayer1Score, setPlayer2Score]
  );

  // Optimized game loop
  useFrame((state, delta) => {
    updateGame(delta);
  });

  // Enhanced ball reset with random angle
  const respawnBall = useCallback(
    (direction) => {
      if (ballRef.current) {
        ballRef.current.position.set(0, 0, 0);
        gameState.current.ballVelocity.set(0, 0, 0);

        const resetBall = () => {
          const angle = (Math.random() - 0.5) * Math.PI * 0.5;
          gameState.current.ballVelocity.set(
            Math.cos(angle) * GAME_CONFIG.BALL_SPEED * direction,
            0,
            Math.sin(angle) * GAME_CONFIG.BALL_SPEED
          );
        };

        setTimeout(resetBall, 800);
      }
    },
    [GAME_CONFIG.BALL_SPEED]
  );

  // Camera setup
  const { camera } = useThree();
  useEffect(() => {
    camera.position.set(0, 20, 0);
    camera.lookAt(0, 0, 0);
  }, [camera]);

  return (
    <>
      <ambientLight intensity={0.4} />
      <spotLight position={[0, 15, 0]} intensity={0.3} />
      <Field />
      <Ball position={[0, 0, 0]} ballRef={ballRef} />
      <Paddle
        position={[-GAME_CONFIG.FIELD_WIDTH / 2 + 1, 1, 0]}
        paddleRef={paddle1Ref}
        color={COLORS.purple.getHex()}
      />
      <Paddle
        position={[GAME_CONFIG.FIELD_WIDTH / 2 - 1, 1, 0]}
        paddleRef={paddle2Ref}
        color={COLORS.blue.getHex()}
      />
      <EffectComposer>
        <Bloom
          intensity={1.5}
          luminanceThreshold={0.2}
          luminanceSmoothing={0.9}
        />
        <ChromaticAberration offset={[0.002, 0.002]} />
      </EffectComposer>
    </>
  );
}

// Optimized GameBoard component
const GameBoard = React.memo(
  ({
    isAI,
    isGameOver,
    keysPressed,
    setKeysPressed,
    setPlayer1Score,
    setPlayer2Score,
  }) => {
    return (
      <div style={{ width: "100%", height: "100%", position: "absolute" }}>
        <Canvas
          gl={{ antialias: true }}
          dpr={[1, 2]}
          performance={{ min: 0.5 }}
          style={{ background: "#000000" }}
        >
          <GameScene
            isAI={isAI}
            isGameOver={isGameOver}
            keysPressed={keysPressed}
            setKeysPressed={setKeysPressed}
            setPlayer1Score={setPlayer1Score}
            setPlayer2Score={setPlayer2Score}
          />
          <OrbitControls
            enablePan={false}
            enableZoom={false}
            maxPolarAngle={Math.PI / 2.5}
            minPolarAngle={Math.PI / 4}
          />
        </Canvas>
      </div>
    );
  }
);

// Main Pong component
export function Pong({ keysPressed, setKeysPressed, player1ID, player2ID, onGameEnd }) {
  const MAX_SCORE = 2;
  const [player1Score, setPlayer1Score] = useState(0);
  const [player2Score, setPlayer2Score] = useState(0);
  const [isGameOver, setIsGameOver] = useState(false);

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

  useEffect(() => {
    if (player1Score >= MAX_SCORE || player2Score >= MAX_SCORE) {
      setIsGameOver(true);
      setKeysPressed(new Map()); // 게임 종료시 키 입력 초기화

      // if (onGameEnd) {
      onGameEnd({
        score1: player1Score,
        score2: player2Score,
        winner: player1Score > player2Score ? 'player1' : 'player2'
      });
      // }
    }
  }, [player1Score, player2Score]);
  // }, [player1Score, player2Score, onGameEnd, setKeysPressed, MAX_SCORE]); // 의존성 배열 수정

  return (
    <>
      {!isGameOver ? (
        <>
          <ScoreBoard
            player1={{ id: player1ID, score: player1Score }}
            player2={{ id: player2ID, score: player2Score }}
            max_score={MAX_SCORE}
          />
          <GameBoard
            isAI={player2ID === "AI"}
            isGameOver={isGameOver}
            keysPressed={keysPressed}
            setKeysPressed={setKeysPressed}
            setPlayer1Score={setPlayer1Score}
            setPlayer2Score={setPlayer2Score}
          />
        </>
      ) : (
        <GameOverScreen
          player1={{ id: player1ID, score: player1Score }}
          player2={{ id: player2ID, score: player2Score }}
          setPlayer1Score={setPlayer1Score}
          setPlayer2Score={setPlayer2Score}
          setIsGameOver={setIsGameOver}
        />
      )}
    </>
  );
}

export default Pong;
