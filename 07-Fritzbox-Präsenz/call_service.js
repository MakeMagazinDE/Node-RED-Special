const Fritzbox = require('fritzbox');

const options = {
  host: 'fritz.box',
  port: 49443,
  ssl: true,
  user: '',
  password: '<Hier das Fritzbox-Passwort eintragen>'
};

// Hier die MAC-Adresse des Geräts eintragen:
const MacAddress = 'DE:AD:BE:EF:08:15';

const fritzbox = new Fritzbox.Fritzbox(options);

fritzbox.initTR064Device()
  .then(function(){
    console.log('Verbunden mit der Fritzbox.');
    const hostsService = fritzbox.services['urn:dslforum-org:service:Hosts:1'];
    return hostsService.actions.GetSpecificHostEntry({
		'NewMACAddress': MacAddress });
  }).then(function(result) {
    console.log(result);
  }).catch(function(error) {
    console.log(error);
  });
