from socket import *
# Client need to know the server’s host name or IP address and port number
serverName = "10.249.40.44"
serverPort = 12000
# Create a UDP client socket
clientSocket = socket(AF_INET, SOCK_DGRAM)
# Client send user’s input to server
message = input("Input lowercase sentence:")
clientSocket.sendto(message.encode(), (serverName, serverPort))
# Client receive server’s message back and print it out
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
print("From server: " + modifiedMessage.decode())
# Client close socket connection
clientSocket.close()