# From: https://github.com/lukstep/raspberry-pi-pico-docker-sdk/tree/main
#docker run -d -it --name pico-sdk --mount type=bind,source=${PWD},target=/home/dev lukstep/raspberry-pi-pico-sdk:latest
#docker exec -it pico-sdk /bin/bash -c "cd /home/dev/; /bin/bash"

docker run --rm --mount type=bind,source=${PWD},target=/home/dev lukstep/raspberry-pi-pico-sdk:latest /bin/bash /home/dev/build_payload.sh
