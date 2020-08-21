const Fritzbox = require('fritzbox');

const options = {
  host: 'fritz.box',
  port: 49443,
  ssl: true,
  user: '',
  password: '<Hier das Fritzbox-Passwort eintragen>'
};

const box = new Fritzbox.Fritzbox(options);

Promise.all([box.initTR064Device(), box.initIGDDevice()])
  .then(function() {
    for (const serviceName in box.services) {
      console.log(`= ${serviceName}`);
      const service = box.services[serviceName];
      for (const actionName in service.actionsInfo) {
        console.log(`   - ${actionName}()`);
        const action = service.actionsInfo[actionName];
        action.inArgs.forEach(function(arg) {
          console.log(`     IN: ${arg}`);
        });
        action.outArgs.forEach(function(arg) {
          console.log(`     OUT: ${arg}`);
        });
      }
	  console.log('');
    }
    console.log(box.listServices());
  })
  .catch(function(err) {
    console.log(err);
  });
