# This is where you define the image for
# the server B which processes the orders.

# You should then use Noje image from Docker Hub as the basis,
# and then follow the instructions linked to in assignment document.
# You should be able to produce a working installation by just
# following the instructions.

#FROM node:version...

FROM node:latest

WORKDIR /server-b

COPY package*.json ./

RUN npm install

COPY . .

ENV PORT=3000

# Expose the default port
EXPOSE 3000

CMD [ "npm", "start" ]