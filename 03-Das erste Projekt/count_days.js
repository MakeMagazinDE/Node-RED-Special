const dates = msg.payload.split("\n");
const today = new Date();
const seen = new Set();
let count = 0;
for (let i = 0; i < dates.length; i++) {
  if (dates[i] !== "" && !seen.has(dates[i])) {
    seen.add(dates[i]);
    const diffTime = Math.abs(today - new Date(dates[i]));
    const diffDays = Math.ceil(diffTime / (1000 * 60 * 60 * 24));
    if (diffDays <= 7)
      count += 1;
  }
}
msg.payload = count;
return msg;