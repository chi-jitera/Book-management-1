const mongoose = require('../config/db');

const readerBookSchema = new mongoose.Schema({
    readerId: { type: mongoose.Schema.Types.ObjectId, ref: 'Reader', required: true },
    bookId: { type: mongoose.Schema.Types.ObjectId, ref: 'Book', required: true },
    dateRead: { type: Date, default: Date.now }
});

module.exports = mongoose.model('ReaderBook', readerBookSchema);
