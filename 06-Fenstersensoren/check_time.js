if (msg.payload === '0') {
  let now = new Date();
  let hours = now.getHours();
  if (hours >= 21) {
    msg.payload = 'ALARM!';
  } else {
    msg.payload = 'OK';
  }
} else {
  msg.payload = 'OK';
}
return msg;
