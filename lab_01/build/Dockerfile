FROM ubuntu:latest
RUN apt-get update && apt-get install -y nano
COPY datetime.sh /datetime.sh
RUN chmod +x /datetime.sh
CMD ["/bin/bash"]