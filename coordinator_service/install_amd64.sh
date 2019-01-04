#/bin/bash

cp coordinator_amd64 /usr/local/bin/
cp coordinator_amd64.service /etc/systemd/system/
systemctl daemon-reload
systemctl start coordinator_amd64.service
systemctl enable coordinator_amd64.service
