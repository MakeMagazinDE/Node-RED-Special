const timestamp = new Date(msg.payload);
const year = timestamp.getFullYear();
let month = timestamp.getMonth();
month = (month < 9 ? '0' : '') + (month + 1)
let day = timestamp.getDate();
day = (day < 10 ? '0' : '') + day
msg.payload = month + '/' + day + '/' + year;
return msg;
