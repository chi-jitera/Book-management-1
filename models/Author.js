const mongoose = require('../config/db');

const authorSchema = new mongoose.Schema({
    name: { type: String, required: true },
    bio: { type: String },
    birthdate: { type: Date },
    nationality: { type: String }
});

module.exports = mongoose.model('Author', authorSchema);