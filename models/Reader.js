const mongoose = require('../config/db');

const readerSchema = new mongoose.Schema({
    name: { type: String, required: true },
    email: { type: String, required: true, unique: true },
    phoneNumber: { type: String },
    address: { type: String }
});

module.exports = mongoose.model('Reader', readerSchema);
