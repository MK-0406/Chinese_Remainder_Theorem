FROM gcc:latest
WORKDIR /app
COPY . .
RUN g++ main_api.cpp -o server -pthread -std=c++11
EXPOSE 8080
CMD ["./server"]
