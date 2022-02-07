sudo su - <<EOF
cd /home/pico/hello8/waiting
# nohup python waiting.py  # keep running when close the ssh connection,ssh method to upload code
nohup python3 flask_server_post.py  # keep running when close the ssh connection,flask method to upload code
EOF
