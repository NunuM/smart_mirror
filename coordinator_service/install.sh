#/bin/bash

cp coordinatorARM64 /usr/local/bin/
cp coordinator.service /etc/systemd/system/
systemctl daemon-reload
systemctl start coordinator.service
systemctl enable coordinator.service
