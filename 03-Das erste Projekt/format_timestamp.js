const timestamp = new Date(msg.payload);
const year = timestamp.getFullYear();
let month = timestamp.getMonth();
month = (month < 9 ? '0' : '') + (month + 1)
let day = timestamp.getDate();
day = (day < 10 ? '0' : '') + day

let timeString = year + '-' + month + '-' + day + ' ';
timeString += timestamp.toLocaleTimeString();
msg.payload = timeString;
return msg;
