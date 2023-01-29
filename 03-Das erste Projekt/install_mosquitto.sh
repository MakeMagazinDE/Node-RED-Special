#!/bin/bash

# Bestehende mosquitto-Installation löschen.
sudo apt remove mosquitto mosquitto-clients

# Repository-Key von mosquitto holen.
curl -LO http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
sudo apt-key add mosquitto-repo.gpg.key
rm mosquitto-repo.gpg.key

# apt-Liste für mosquitto auf Debian "buster" holen.
# Bei anderer Debian-Version "buster" ersetzen.
cd /etc/apt/sources.list.d/
sudo curl -LO http://repo.mosquitto.org/debian/mosquitto-buster.list

# apt-Datenbank aktualisieren und mosquitto mit Clients installieren.
sudo apt update
sudo apt install mosquitto mosquitto-clients
