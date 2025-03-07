import React, { useState, useEffect } from "react";
import { useLocation } from "react-router-dom";
import { useNavigate } from "react-router";
import { QRCodeSVG } from "qrcode.react";

export function Qr() {
  const [qrData, setQrData] = useState({
    secret: null,
    provisioning_uri: null,
  });

  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const setupTOTP = async () => {
      try {
        const response = await fetch("/api/v1/auth/2fa/setup", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          credentials: "include",
        });

        if (!response.ok) {
          throw new Error(response.statusText);
        }

        const data = await response.json();
        setQrData({
          secret: data.secret,
          provisioning_uri: data.provisioning_uri,
        });
      } catch (error) {
        console.error("Error setting up 2FA:", error);
        setError(error.message);
      } finally {
        setLoading(false);
      }
    };

    setupTOTP();
  }, []);

  if (loading) {
    return (
      <div className="d-flex justify-content-center align-items-center">
        <div className="spinner-border text-primary" role="status">
          <span className="visually-hidden">Loading...</span>
        </div>
      </div>
    );
  }

  if (error || !qrData.provisioning_uri) {
    return (
      <div className="alert alert-danger" role="alert">
        Failed to setup 2FA: {error}
      </div>
    );
  }

  return (
    <div className="card p-4">
      <h3 className="card-title mb-4">Scan QR Code with Authenticator App</h3>

      {qrData.provisioning_uri && (
        <div className="d-flex justify-content-center mb-3">
          <QRCodeSVG
            value={qrData.provisioning_uri}
            size={200}
            level="M"
            includeMargin={true}
          />
        </div>
      )}

      <div className="mt-3">
        <p className="fw-bold mb-1">Manual Setup Code:</p>
        <code className="user-select-all">{qrData.secret}</code>
      </div>
      {/* 설정 방법 안내 */}
      <small className="text-muted mt-3">
        1. 인증기 앱으로 QR 코드를 스캔하세요
        <br />
        2. 또는 위의 설정 코드를 수동으로 입력하세요
        <br />
        3. 생성된 6자리 코드를 입력하여 설정을 완료하세요
      </small>
    </div>
  );
}

export function AuthCodeInput({ onSuccess, onError }) {
  const [code, setCode] = useState("");
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [error, setError] = useState(null);
  const navigate = useNavigate();
  const location = useLocation();
  const user = location?.state?.user;

  // temp_token이 없거나 user 정보가 없으면 로그인 페이지로
  useEffect(() => {
    if (!user) {
      navigate("/login", { replace: true, state: { upstream: true } });
    }
  }, [user, navigate]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError(null);
    setIsSubmitting(true);

    try {
      const response = await fetch("/api/v1/auth/2fa/verify", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        credentials: "include",
        body: JSON.stringify({
          code: code.trim(),
        }),
      });

      let responseData;
      try {
        const responseText = await response.text();
        responseData = JSON.parse(responseText);
      } catch (error) {
        console.error("Failed to parse response:", error);
        throw new Error("서버 응답을 처리할 수 없습니다.");
      }

      if (!response.ok) {
        throw new Error(responseData.error?.message || "인증에 실패했습니다.");
      }

      // 2FA 성공시 홈으로 리다이렉트
      if (onSuccess) {
        onSuccess(responseData.message);
      }
    } catch (err) {
      console.error("2FA verification error:", err);
      setError(err.message);
      if (onError) {
        onError(err.message);
      }
    } finally {
      setIsSubmitting(false);
    }
  };

  const handleChange = (e) => {
    const value = e.target.value;
    const numericValue = value.replace(/[^0-9]/g, "");
    setCode(numericValue);
  };

  if (!user) {
    return null; // useEffect에서 리다이렉트 처리
  }

  return (
    <div className="position-absolute top-50 start-50 translate-middle">
      <div className="card p-4">
        <form onSubmit={handleSubmit} className="d-flex flex-column gap-3">
          {user && (
            <div className="mb-3">
              <h3 className="card-title">Enter 2FA Code</h3>
              <p className="text-muted">Welcome back, {user.displayname}!</p>
            </div>
          )}

          {error && (
            <div className="alert alert-danger" role="alert">
              {error}
            </div>
          )}
          {error && (
            <div className="alert alert-danger" role="alert">
              {error}
            </div>
          )}

          <div className="form-group">
            <input
              type="text"
              value={code}
              onChange={handleChange}
              placeholder="Enter 6-digit code"
              maxLength={6}
              className="form-control text-center fs-4 letter-spacing-2"
              style={{ letterSpacing: "0.5em" }}
              disabled={isSubmitting}
              autoComplete="one-time-code"
              inputMode="numeric"
              pattern="[0-9]*"
              required
            />
            <small className="form-text text-muted">
              Enter the 6-digit code from your authenticator app
            </small>
          </div>

          <button
            type="submit"
            className="btn btn-primary w-100"
            disabled={code.length !== 6 || isSubmitting}
          >
            {isSubmitting ? (
              <>
                <span
                  className="spinner-border spinner-border-sm me-2"
                  role="status"
                  aria-hidden="true"
                ></span>
                Verifying...
              </>
            ) : (
              "Verify Code"
            )}
          </button>
        </form>
      </div>
    </div>
  );
}
