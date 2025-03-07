import React, { useState, useEffect, useRef } from "react";

import "./App.css";

function Icon({ isFriend }) {
  return <img src="/static/assets/person-add.svg" width="28" height="28"></img>;
}

function UserListItem({ nickName }) {
  return (
    <div className="py-3">
      <button
        type="button"
        className="btn btn-dark user-list-item-wrapper text-white"
      >
        <span className="my-user-icon">
          <Icon />
        </span>
        <span className="py-1 my-user-text">{nickName}dfdsdfsdf</span>
      </button>
    </div>
  );
}

// export function UserListItem({ nick, photo }) {
//   return (
//     <li
//       className="fs-4 text-light py-2 px-3 user-list-item-hover"
//       onClick={() => {
//         window.location.href = window.location.origin;
//       }}
//       style={{
//         cursor: "pointer",
//         display: "inline-block", // Makes the element only as wide as the text
//       }}
//     >
//       asdf
//     </li>
//   );
// }

export default UserListItem;
