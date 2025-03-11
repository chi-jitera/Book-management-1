const mongoose = require('../config/db');

const testSchema = new mongoose.Schema({
    id: { type: mongoose.Schema.Types.ObjectId, required: true, unique: true },
    created_at: { type: Date, default: Date.now },
    updated_at: { type: Date, default: Date.now }
});

module.exports = mongoose.model('Test', testSchema);