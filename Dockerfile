FROM alpine:latest

RUN	apk update && \
	apk add git g++ libgomp

WORKDIR .

RUN git clone https://github.com/Grealish17/parvpo1.git && \
	cd parvpo1 && \
	g++ -fopenmp lab1.cpp -o lab1

CMD ["./parvpo1/lab1"]

# docker build --no-cache -t my-alpine:latest .
