sudo su - <<EOF
cd /home/pico/hello8/waiting
nohup python waiting.py  # keep running when close the ssh connection
EOF
