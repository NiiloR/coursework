# This is where you define the image for
# the server A, which implements the Swagger API.

# Start by copying the server stub to this directory.

# You should then use Noje image from Docker Hub as the basis,
# and then follow the instructions linked to in assignment document.
# You should be able to produce a working installation by just
# following the instructions.


FROM node:latest

WORKDIR /server-a

COPY package*.json ./

RUN npm install

COPY . .

ENV PORT=8080

# Expose the default port
EXPOSE 8080

CMD [ "npm", "start" ]