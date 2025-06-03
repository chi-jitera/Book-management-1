const mongoose = require('mongoose');

const readerSchema = new mongoose.Schema({
    name: {
        type: String,
        required: true,
    },
    email: {
        type: String,
        required: true,
        unique: true,
    },
    dateOfBirth: {
        type: Date,
    },
    registeredDate: {
        type: Date,
        default: Date.now,
    },
});

module.exports = mongoose.model('Reader', readerSchema);
