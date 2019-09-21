FROM node:latest
EXPOSE 12000
WORKDIR /home/node/
ADD . .
RUN npm init --y
RUN npm install
CMD ["node", "back/server.js"]