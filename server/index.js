const express = require("express");
const app = express();
const http = require("http");
const { Server } = require("socket.io");
const cors = require("cors");

const mqtt = require("mqtt");
const fs = require("fs");
var caFile = fs.readFileSync("ca.crt");
var KEY = fs.readFileSync("client.key");
var CERT = fs.readFileSync("client.crt");

var options = {
  //clientId:"mqttjs01",
  //port:8883,
  //host:'192.168.1.71',
  //protocol:'mqtts',
  rejectUnauthorized: false,
  ca: caFile,
  key: KEY,
  cert: CERT,
};
const client = mqtt.connect(
  "mqtts://ec2-54-64-144-36.ap-northeast-1.compute.amazonaws.com:8883",
  options
);
console.log("connected flag  " + client.connected);
client.on("connect", function () {
  console.log("connected  " + client.connected);
});

var Socket;

app.use(cors());

const server = http.createServer(app);

const io = new Server(server, {
  cors: {
    origin: "http://localhost:3000",
    methods: ["GET", "POST"],
  },
});

io.on("connection", (socket) => {
  console.log(`User Connected: ${socket.id}`);
  Socket = socket;
});

client.on("connect", function (data) {
  client.subscribe("carpark/slots", function (err) {
    if (!err) {
      //client.publish("presence", "Hello mqtt");
    }
  });
  client.subscribe("carpark/airQuality", function (err) {
    if (!err) {
      //client.publish("presence", "Hello mqtt");
    }
  });
});

client.on("message", function (topic, message) {
  // message is Buffer
  // console.log(message.toString());
  if (topic === "carpark/slots") {
    Socket.emit("availability", message.toString());
  } else if (topic === "carpark/airQuality") {
    Socket.emit("air", message.toString());
  }
});

server.listen(3001, () => {
  console.log("SERVER IS RUNNING");
});
