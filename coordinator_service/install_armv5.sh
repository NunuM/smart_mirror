#/bin/bash

cp coordinator_armv5 /usr/local/bin/
cp coordinator_armv5.service /etc/systemd/system/
systemctl daemon-reload
systemctl start coordinator_armv5.service
systemctl enable coordinator_armv5.service
