const express = require('express');
const cors = require('cors');
const morgan = require('morgan');
const bookRoutes = require('./routes/bookRoutes');
const readerRoutes = require('./routes/readerRoutes');
const readerBookRoutes = require('./routes/readerBookRoutes');

const app = express();
app.use(express.json());
app.use(cors());
app.use(morgan('dev'));
app.use('/api', bookRoutes);
app.use('/api', readerRoutes);
app.use('/api', readerBookRoutes);

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});