from ubuntu:latest
from python:3

RUN apt-get -y update
RUN apt-get -y install python3 clang cmake libgtest-dev libsfml-dev libginac-dev

COPY cmake ./cmake
COPY Architecture ./Architecture
COPY include ./include
COPY source ./source
COPY tests ./tests
COPY Textures ./Textures
COPY uml_photo ./uml_photo
COPY README.md .
COPY CMakeLists.txt .
COPY run.sh .
COPY copy.py .

ENV DISPLAY = :0

ENTRYPOINT ["./run.sh"]
