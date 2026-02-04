
const mongoose = require('../config/db');

const todoSchema = new mongoose.Schema({
    title: { type: String, required: true },
    description: { type: String },
    dueDate: { type: Date },
    completed: { type: Boolean, default: false }/*chi has changed one more time*/
});

module.exports = mongoose.model('ToDo', todoSchema);
