<changes><change><info>Ensure bookRoutes are included in Express app.</info><content>const express = require('express');
const mongoose = require('mongoose');
const bookRoutes = require('./routes/bookRoutes');

const app = express();

app.use(express.json());
app.use(bookRoutes);

// ... rest of app.js, e.g. mongoose connection and app.listen()</content></change>
          </changes>