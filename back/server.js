'use strict'

const express = require("express");

const port = 12000;
const host = "0.0.0.0";
const front = __dirname + "/../front/";

const app = express();

const morgan = require('morgan');

const log_fmt = "[:date[web]] :remote-addr :method :url :status :response-time ms";

app.use(morgan(log_fmt, {
    skip: (req, res) => {
        return res.statusCode < 400
    },
    stream: process.stderr
}));

app.use(morgan(log_fmt, {
    skip: (req, res) => {
        return res.statusCode >= 400
    },
    stream: process.stdout
}));

app.use(express.static(front));

app.listen(port, host, () => {
    console.log(`Running on http://${host}:${port}`);
});

app.get('/', (req, res) => {
    res.sendFile(front + 'index.html');
});